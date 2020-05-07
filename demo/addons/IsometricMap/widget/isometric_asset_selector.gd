tool
extends Panel

class_name IsometricAssetSelector

var is_view_generated: = false

var maps_path: String
var tiles_path: String

onready var maps_tree: FileTree = get_node("TabContainer/Maps/ScrollContainer/MapsTree")
onready var tiles_tree: FileTree = get_node("TabContainer/Tiles/ScrollContainer/TilesTree")

func _ready():
	$TabContainer/Tiles/ScrollContainer/TilesTree.connect("cell_selected", self, "on_item_selected_from_tiles_tree")
	$TabContainer/Maps/ScrollContainer/MapsTree.connect("cell_selected", self, "on_item_selected_from_maps_tree")
	var file: = File.new()
	file.open("res://addons/IsometricMap/Config/path.json", File.READ)
	var json: Dictionary = JSON.parse(file.get_as_text()).result
	maps_path = json["maps_path"]
	tiles_path = json["tiles_path"]
	if !$TabContainer/Maps/ScrollContainer/MapsTree.is_busy and !$TabContainer/Tiles/ScrollContainer/TilesTree.is_busy:
		generate_trees()
	is_view_generated = true

func generate_trees() -> void:
	$TabContainer/Maps/ScrollContainer/MapsTree.is_busy = true
	$TabContainer/Tiles/ScrollContainer/TilesTree.is_busy = true
	$TabContainer/Maps/ScrollContainer/MapsTree.generate_tree(maps_path, ".tscn")
	$TabContainer/Tiles/ScrollContainer/TilesTree.generate_tree(tiles_path, ".tscn", null, ["placeholder"])

func regenerate_trees() -> void:
	if !$TabContainer/Maps/ScrollContainer/MapsTree.is_busy and !$TabContainer/Tiles/ScrollContainer/TilesTree.is_busy:
		$TabContainer/Maps/ScrollContainer/MapsTree.is_busy = true
		$TabContainer/Tiles/ScrollContainer/TilesTree.is_busy = true
		$TabContainer/Maps/ScrollContainer/MapsTree.clear()
		$TabContainer/Tiles/ScrollContainer/TilesTree.clear()
		generate_trees()

func on_item_selected_from_tiles_tree() -> void:
	deselect_selected_from_tree($TabContainer/Maps/ScrollContainer/MapsTree)

func on_item_selected_from_maps_tree() -> void:
	deselect_selected_from_tree($TabContainer/Tiles/ScrollContainer/TilesTree)

func deselect_selected_from_tree(tree: Tree) -> void:
	var selected: TreeItem = tree.get_selected()
	if selected != null:
		selected.deselect(0)
