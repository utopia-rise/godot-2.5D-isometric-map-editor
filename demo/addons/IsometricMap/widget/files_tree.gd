tool
extends Tree

class_name FileTree

onready var preview_generator := IsoPreviewGenerator.new(get_tree().get_root())

var is_busy := false

var last_item: TreeItem

func _ready():
	preview_generator.connect("image_generated", self, "set_icon")

func generate_tree(path: String, extension: String, root_node: TreeItem = null, additional_elements: Array = []) -> void:
	var current_category: TreeItem
	if root_node != null:
		current_category = root_node
	else:
		current_category = self.create_item()
		for elmt in additional_elements:
			if elmt is String:
				var element_item: = self.create_item(current_category)
				element_item.set_text(0, elmt)
				element_item.set_metadata(0, elmt)
		self.set_hide_root(true)
	var dir = Directory.new()
	if dir.open(path) == OK:
		dir.list_dir_begin()
		var file_name = dir.get_next()
		while file_name != "":
			if !file_name.begins_with("."):
				var p = dir.get_current_dir() + "/" + file_name
				
				if dir.current_is_dir():
					var next_category: = self.create_item(current_category)
					next_category.set_text(0, file_name)
					generate_tree(p, extension, next_category)
				else:
					if file_name.ends_with(extension):
						var file: = self.create_item(current_category)
						var text = preview_generator.generate_from_path(p, Vector2(256, 256), file)
						last_item = file
						file.set_text(0, file_name)
						file.set_metadata(0, p)
			file_name = dir.get_next()

func set_icon(treeitem: TreeItem, text: Texture):
	treeitem.set_icon(0, text)
	if last_item == treeitem:
		is_busy = false
