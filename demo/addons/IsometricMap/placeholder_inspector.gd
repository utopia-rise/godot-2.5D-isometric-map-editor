tool
extends EditorInspectorPlugin

class_name PlaceholderInspector

func can_handle(object):
	return object is TilePlaceholder

func parse_property(object, type, path, hint, hint_text, usage):
	if path == "placeholder_type":
		add_property_editor(path, TerrainTypeEditor.new())
		return true
	return false

class TerrainTypeEditor extends EditorProperty:
	var updating = false
	
	var option_button = OptionButton.new()
	var terrain_types: Dictionary = Dictionary()

	func update_property():
		var new_value = get_edited_object()[ get_edited_property() ]
		updating=true
		for i in terrain_types.keys():
			var value = terrain_types[i] as PlaceholderType
			if value == new_value:
				option_button.select(i)
				break
		updating=false

	func _init():
		add_child(option_button)
		var array: Array = MapSettings.terrain_types.values
		for value in array:
			if value is PlaceholderType:
				value as PlaceholderType
				option_button.add_item(value.type_name)
				option_button.add_color_override(value.type_name, value.color)
				terrain_types[option_button.get_item_count() - 1] = value
		option_button.connect("item_selected", self, "change_placeholder_type")
	
	func change_placeholder_type(id: int) -> void:
		var property: String = get_edited_property()
		var object: Object = get_edited_object()
		if property == "placeholder_type" and object is TilePlaceholder:
			object as TilePlaceholder
			object.placeholder_type = terrain_types[id]
			object.update()
