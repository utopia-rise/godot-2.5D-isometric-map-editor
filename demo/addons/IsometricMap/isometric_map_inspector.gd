tool
extends EditorInspectorPlugin

class_name IsometricMapInspector

var undo_redo: UndoRedo

func can_handle(object):
	return object.get_class() == "IsometricMap"

func parse_property(object, type, path, hint, hint_text, usage):
	if path == "size3d":
		add_property_editor(path, MapSizeEditor.new(undo_redo))
		return true
	return false

func _init(undoredo: UndoRedo):
	undo_redo = undoredo

class MapSizeEditor extends EditorProperty:
	var updating = false
	var terrain_types: Dictionary = Dictionary()
	var widget = load("res://addons/IsometricMap/widget/MapSizeWidget.tscn").instance()
	var undo_redo: UndoRedo

	func update_property():
		var new_value = get_edited_object()[ get_edited_property() ]
		updating=true
		for i in terrain_types.keys():
			var value = terrain_types[i]
			if value == new_value:
				#vbox.select(i)
				break
		updating=false

	func _init(undoredo: UndoRedo):
		undo_redo = undoredo
		add_child(widget)
		widget.get_node("xle").connect("text_entered", self, "change_map_width")
		widget.get_node("yle").connect("text_entered", self, "change_map_depth")
		widget.get_node("zle").connect("text_entered", self, "change_map_height")
	
	func _ready():
		var iso_map = get_edited_object()
		widget.get_node("xle").text = str(iso_map.size3d.x)
		widget.get_node("yle").text = str(iso_map.size3d.y)
		widget.get_node("zle").text = str(iso_map.size3d.z)
	
	func change_map_width(value: String) -> void:
		var iso_map = get_edited_object()
		var map_size: = Vector3(int(value), iso_map.size3d.y, iso_map.size3d.z)
		undo_redo.create_action("change_map_width")
		remove_out_of_range_placeholders(map_size)
		undo_redo.add_do_property(iso_map, "size3d", map_size)
		undo_redo.add_undo_property(iso_map, "size3d", iso_map.size3d)
		undo_redo.commit_action()
	
	func change_map_depth(value: String) -> void:
		var iso_map = get_edited_object()
		var map_size: = Vector3(iso_map.size3d.x, int(value), iso_map.size3d.z)
		undo_redo.create_action("change_map_depth")
		remove_out_of_range_placeholders(map_size)
		undo_redo.add_do_property(iso_map, "size3d", map_size)
		undo_redo.add_undo_property(iso_map, "size3d", iso_map.size3d)
		undo_redo.commit_action()
	
	func change_map_height(value: String) -> void:
		var iso_map = get_edited_object()
		var map_size: = Vector3(iso_map.size3d.x, iso_map.size3d.y, int(value))
		undo_redo.create_action("change_map_height")
		remove_out_of_range_placeholders(map_size)
		undo_redo.add_do_property(iso_map, "size3d", map_size)
		undo_redo.add_undo_property(iso_map, "size3d", iso_map.size3d)
		undo_redo.commit_action()
	
	func remove_out_of_range_placeholders(map_size: Vector3) -> void:
		var iso_map = get_edited_object()
		for pl in iso_map.get_children():
			if pl.get_class() == "IsometricPlaceholder":
				if pl.local_3D_position.x + pl.size3d.x > map_size.x or pl.local_3D_position.y + pl.size3d.y > map_size.y or pl.local_3D_position.z + pl.size3d.z > map_size.z:
					undo_redo.add_do_method(iso_map, "remove_iso_positionable", pl, pl.local_3D_position)
					undo_redo.add_undo_method(iso_map, "add_iso_placeholder", pl, pl.local_3D_position)
