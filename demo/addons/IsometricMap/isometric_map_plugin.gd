tool
extends EditorPlugin

var handlers: Dictionary = Dictionary()
var current_handler: EditionHandler = null
var isometric_asset_selector: IsometricAssetSelector = load("res://addons/IsometricMap/widget/IsometricAssetsSelector.tscn").instance()
var editor_file_system: EditorFileSystem

func _enter_tree():
	add_inspector_plugin(IsometricMapInspector.new(get_undo_redo()))
	add_control_to_container(EditorPlugin.CONTAINER_CANVAS_EDITOR_SIDE_RIGHT, isometric_asset_selector)
	isometric_asset_selector.visible = false
	editor_file_system = get_editor_interface().get_resource_filesystem()
	self.connect("scene_changed", self, "on_scene_changed")
	editor_file_system.connect("filesystem_changed", self, "on_filesystem_changed")

func edit(object: Object) -> void:
	if object.get_class() == "IsometricMap" && object.get_parent().get_class() != "IsometricMap":
		if handlers.has(object):
			current_handler = handlers[object]
		else:
			var hdler: = MapEditionHandler.new(object, get_undo_redo(), self.get_editor_interface(), isometric_asset_selector)
			handlers[object] = hdler
			current_handler = hdler
	elif object.get_class() == "IsometricPlaceholder" and current_handler != null and current_handler is MapEditionHandler:
		current_handler.edit_placeholder(object)
	elif object.get_class() == "IsometricTile" and object.get_parent().get_class() != "IsometricMap":
		var hdler = TileEditionHandler.new(object, get_undo_redo())
		handlers[object] = hdler
		current_handler = hdler

func handles(object: Object) -> bool:
	var object_class = object.get_class()
	return object_class == "IsometricMap" or object_class == "IsometricTile" or object_class == "IsometricPositionable" or object_class == "IsometricPlaceholder"

func forward_canvas_gui_input(event: InputEvent) -> bool:
	if is_instance_valid(current_handler) and current_handler != null:
		return current_handler._forward_canvas_gui_input(event)
	else:
		return false

func on_scene_changed(node: Node):
	if node != null and handlers.has(node.filename):
		current_handler = handlers[node.filename]
	for key in handlers.keys():
		if !is_instance_valid(key):
			handlers[key].queue_free()
			handlers.erase(key)

func on_filesystem_changed():
	isometric_asset_selector.regenerate_trees()

func make_visible(visible):
	isometric_asset_selector.visible = visible
