tool
extends EditorPlugin

var handlers: Dictionary = Dictionary()
var current_handler: MapEditionHandler = null
var isometric_asset_selector: IsometricAssetSelector = load("res://addons/IsometricMap/widget/IsometricAssetsSelector.tscn").instance()
var editor_file_system: EditorFileSystem

func _enter_tree():
	add_autoload_singleton("MapSettings", "res://addons/IsometricMap/Scripts/map_setting.gd")
	add_inspector_plugin(PlaceholderInspector.new())
	add_inspector_plugin(IsometricMapInspector.new(get_undo_redo()))
	add_control_to_container(EditorPlugin.CONTAINER_CANVAS_EDITOR_SIDE_RIGHT, isometric_asset_selector)
	isometric_asset_selector.visible = false
	editor_file_system = get_editor_interface().get_resource_filesystem()
	self.connect("scene_changed", self, "on_scene_changed")
	editor_file_system.connect("filesystem_changed", self, "on_filesystem_changed")

func edit(object: Object) -> void:
	if object is IsoMap && !(object.get_parent() is IsoMap):
		if handlers.has(object):
			current_handler = handlers[object]
		else:
			var hdler: = MapEditionHandler.new(object, get_undo_redo(), self.get_editor_interface(), isometric_asset_selector)
			handlers[object] = hdler
			current_handler = hdler
	elif object is BasePlaceholder and current_handler != null:
		current_handler.edit_placeholder(object)

func handles(object: Object) -> bool:
	return (object is IsoPositionable)

func forward_canvas_gui_input(event: InputEvent) -> bool:
	if is_instance_valid(current_handler) and current_handler != null:
		return current_handler.forward_canvas_gui_input(event)
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
