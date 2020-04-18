tool
extends Node2D

class_name GridCursor

var selected_stair: int = 0
var mouse_position: Vector2 = Vector2(0,0)

var map: IsoMap
var map_width: int
var map_depth: int
var map_height: int

var grid_size = 3

func set_map(size: Vector3):
	map_width = size.x
	map_depth = size.y
	map_height = size.z

func _init():
	z_index = 4096
	show_behind_parent = false

func _enter_tree():
	map = get_parent()

func _process(delta):
	var new_mouse_position = get_local_mouse_position()
	if mouse_position != new_mouse_position:
		mouse_position = new_mouse_position
		update()
	if map_width != map.aabb.size.x or map_depth != map.aabb.size.y or map_height != map.aabb.size.z:
		map_width = map.aabb.size.x
		map_depth = map.aabb.size.y
		map_height = map.aabb.size.z
		update()

func _draw():
	var tile_depth: int = MapSettings.tile_height
	var tile_width: int = MapSettings.tile_width
	var tile_height: int = MapSettings.e_z
	var offset: Vector2 = Vector2(0, tile_depth * 0.5)
	
	var position_3D = MapSettings.get_3d_coord_from_screen(offset + mouse_position, selected_stair)
	position_3D.x = clamp(int(position_3D.x), 0, map_width - 1)
	position_3D.y = clamp(int(position_3D.y), 0, map_depth - 1)
	position_3D.z = clamp(int(position_3D.z), 0, map_height - 1)
	offset = MapSettings.get_screen_coord_from_3d(position_3D)
	offset += Vector2(0, - tile_depth * grid_size * 0.5)
	
	var screen_x_delta = Vector2(tile_width * 0.5, tile_depth * 0.5)
	var screen_y_delta = Vector2(tile_width * -0.5, tile_depth * 0.5)

	var from: Vector2 = offset + screen_x_delta * 0.5
	var to: Vector2 = from + screen_x_delta * (grid_size - 1)
	for i in range(1, grid_size):
		from += screen_y_delta
		to += screen_y_delta
		draw_line(from, to, Color.green, 2.0)
	
	from = offset  + screen_y_delta * 0.5
	to = from + screen_y_delta * (grid_size - 1)
	for i in range(1, grid_size):
		from += screen_x_delta
		to += screen_x_delta
		draw_line(from, to, Color.green, 2.0)
