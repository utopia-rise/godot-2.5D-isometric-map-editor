tool
extends IsoPositionable
class_name BasePlaceholder

export (Resource) var placeholder_type: Resource = load("res://addons/IsometricMap/prefab/types/default.tres")

var temp_alpha: float = 0.15
var selected: bool = false

var debug_points: PoolVector2Array = PoolVector2Array()

var left_color: PoolColorArray
var right_color: PoolColorArray
var up_color: PoolColorArray
var down_color: PoolColorArray
var side_slope_color: PoolColorArray
var forward_slope_color: PoolColorArray
var backward_slope_color: PoolColorArray
var stair_color: Color

var map setget set_map
var map_width: int
var map_depth: int
var map_height: int

func set_map(size: Vector3):
	map_width = size.x
	map_depth = size.y
	map_height = size.z

func _draw():
	left_color = PoolColorArray([placeholder_type.color.darkened(0.5)])
	right_color = PoolColorArray([placeholder_type.color.darkened(0.25)])
	up_color = PoolColorArray([placeholder_type.color])
	down_color = PoolColorArray([placeholder_type.color.darkened(0.9)])
	side_slope_color = PoolColorArray([placeholder_type.color.darkened(0.10)])
	forward_slope_color = PoolColorArray([placeholder_type.color.darkened(0.10)])
	backward_slope_color = PoolColorArray([placeholder_type.color.lightened(0.10)])
	
	if self.debug_z == self.aabb.size.z:
		stair_color = Color.orange.linear_interpolate(down_color[0], 0.3)
	elif self.debug_z == 0:
		stair_color = Color.purple.linear_interpolate(down_color[0], 0.3)
	else:
		stair_color = Color.red.linear_interpolate(down_color[0], 0.3)
	stair_color.a = 0.2
	_prepare_points()
	draw_points()

func _prepare_points() -> void:
	pass

func draw_points() -> void:
	draw_polygon(up_points, up_color)
	draw_polygon(left_points, left_color)
	draw_polygon(right_points, right_color)
	
	var ortho_position: Vector3 = self.aabb.position
	var size: Vector3 = self.aabb.size

	if self.debug_z > -1 and self.debug_z <= size.z:
		draw_polygon(debug_points, [stair_color])
		stair_color.a = 1
		draw_line(debug_points[0], debug_points[1], stair_color, 2.0)
		draw_line(debug_points[1], debug_points[2], stair_color, 4.0)
		draw_line(debug_points[2], debug_points[3], stair_color, 4.0)
		draw_line(debug_points[3], debug_points[0], stair_color, 2.0)
			
	if self.debug_z > -1:
		var tile_depth: int = MapSettings.tile_height
		var tile_width: int = MapSettings.tile_width
		var tile_height: int = MapSettings.e_z
			
		var corrected_z =  clamp(self.debug_z, 0, size.z)
		var added_line: int = ceil(MapSettings.z_ratio * corrected_z) + 1
		
		var z_delta = self.debug_z - corrected_z
		var offset = int((MapSettings.z_ratio-1) * z_delta)
		var base = down_points[0] + Vector2(0, (z_delta + offset) * tile_depth - tile_height * self.debug_z)
		
		var max_x = map_width - ortho_position.x - z_delta - offset
		var max_y = map_depth - ortho_position.y - z_delta - offset
		max_x = min(max_x, size.x + added_line - 1)
		max_y = min(max_y, size.y + added_line - 1)
		
		if max_y > 0 and max_x > 0:
			for i in range(0, max_y + 1):
				var from: Vector2 = base + Vector2(tile_width * 0.5 * -i, tile_depth * 0.5 * i)
				var to: Vector2 = base + Vector2(tile_width * 0.5 * (max_x - i), tile_depth * 0.5 * (max_x + i))
				draw_line(from, to, Color.black, 2.0)
			for i in range(0, max_x + 1):
				var from: Vector2 = base + Vector2(tile_width * 0.5 * i, tile_depth * 0.5 * i)
				var to: Vector2 = base + Vector2(tile_width * 0.5 * (i - max_y), tile_depth * 0.5 * (max_y + i))
				draw_line(from, to, Color.black, 2.0)
	
	
	if self.temporary:
		up_color[0].a = temp_alpha
		left_color[0].a = temp_alpha
		right_color[0].a = temp_alpha
		stair_color.a = 0.05

		draw_polygon(up_points, up_color)
		draw_polygon(left_points, left_color)
		draw_polygon(right_points, right_color)
		if self.debug_z >= 0 and self.debug_z <= size.z:
			draw_polygon(debug_points, [stair_color])
	
	if selected and !self.temporary:
		draw_outline()


func _grid_updated(grid_z: int) -> void:
	self.debug_z = grid_z - self.aabb.position.z
	update()

func _on_select(is_selected: bool) -> void:
	 selected = is_selected
