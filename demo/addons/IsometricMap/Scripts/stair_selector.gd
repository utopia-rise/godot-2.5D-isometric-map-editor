tool
extends Node2D

class_name StairSelector

var selected_stair: int = 0

var map
var map_width: int
var map_depth: int
var map_height: int

func _init():
	z_index = 0
	show_behind_parent = true

func _enter_tree():
	map = get_parent()

func _process(delta):
	if map_width != map.size3d.x or map_depth != map.size3d.y or map_height != map.size3d.z:
		map_width = map.size3d.x
		map_depth = map.size3d.y
		map_height = map.size3d.z
		update()

func _draw():
	var tile_depth: int = IsoServer.tile_height
	var tile_width: int = IsoServer.tile_width
	var e_z: int = IsoServer.get_ez()
	var offset: Vector2 = Vector2(0, - tile_depth * 0.5)
	var height_offset = Vector2(0, e_z * selected_stair)
	for i in range(0, map_depth):
		var from: Vector2 = Vector2(-tile_width * 0.5 * i, tile_depth * 0.5 * i) + offset - height_offset
		var to: Vector2 = Vector2(tile_width * 0.5 * (map_width - 1 - i), tile_depth * 0.5 * (i + map_width - 1)) + offset - height_offset
		draw_line(from, to, Color.black, 2.0)
	for i in range(0, map_width):
		var from: Vector2 = Vector2(tile_width * 0.5 * i, tile_depth * 0.5 * i) + offset - height_offset
		var to: Vector2 = Vector2(tile_width * 0.5 * (i - map_depth + 1), tile_depth * 0.5 * (map_depth - 1 + i)) + offset - height_offset
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
