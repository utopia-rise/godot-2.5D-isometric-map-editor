tool
extends Node2D

class_name StairSelector

var selected_stair: int = 0

var map
var map_width: int
var map_depth: int
var map_height: int

func _init():
	z_index = 4096
	show_behind_parent = true

func _enter_tree():
	map = get_parent()

func _ready():
	for i in range(0, 4):
		add_child(Node2D.new())
	set_children_position()

func _process(delta):
	if map_width != map.size3d.x or map_depth != map.size3d.y or map_height != map.size3d.z:
		map_width = map.size3d.x
		map_depth = map.size3d.y
		map_height = map.size3d.z
		update()
		set_children_position()

func _draw():
	var tile_depth: int = IsoServer.tile_height
	var tile_width: int = IsoServer.tile_width
	var offset: Vector2 = Vector2(0, - tile_depth * 0.5)
	var height_offset = Vector2(0, IsoServer.get_ez() * selected_stair)
	for i in range(0, map_depth + 1):
		var from: Vector2 = Vector2(-tile_width * 0.5 * i, tile_depth * 0.5 * i) + offset - height_offset
		var to: Vector2 = Vector2(tile_width * 0.5 * (map_width - i), tile_depth * 0.5 * (i + map_width)) + offset - height_offset
		draw_line(from, to, Color.black, 2.0)
	for i in range(0, map_width + 1):
		var from: Vector2 = Vector2(tile_width * 0.5 * i, tile_depth * 0.5 * i) + offset - height_offset
		var to: Vector2 = Vector2(tile_width * 0.5 * (i - map_depth), tile_depth * 0.5 * (map_depth + i)) + offset - height_offset
		draw_line(from, to, Color.black, 2.0)

func move_selected_stair(up: bool) -> bool:
	var offset: int = 0
	if up and selected_stair < map_height - 1:
		offset = 1
	elif !up and selected_stair > 0:
		offset = -1
	else:
		return false
	selected_stair += offset
	self.update()
	get_tree().call_group("positionables", "_on_grid_updated", selected_stair)
	return true

func set_children_position():
	var tile_depth: int = IsoServer.tile_height
	var tile_width: int = IsoServer.tile_width
	var offset: Vector2 = Vector2(0, - tile_depth * 0.5)
	var children = get_children()
	children[0].position = Vector2(tile_width * 0.5 * map_width, tile_depth * 0.5 * map_width) + offset
	children[1].position = Vector2(tile_width * 0.5 * (map_width - map_depth), tile_depth * 0.5 * (map_depth + map_width)) + offset
	children[2].position = Vector2(-tile_width * 0.5 * map_depth, tile_depth * 0.5 * map_depth) + offset
	children[3].position = offset - Vector2(0, IsoServer.get_ez() * map_height)
