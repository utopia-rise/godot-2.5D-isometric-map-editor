extends Node2D
class_name IsoPositionable

#LOGIC DATA
export var iso_position: Vector2 = Vector2(0, 0)
export(AABB) var aabb: AABB = AABB(Vector3(0, 0, 0), Vector3(1, 1, 1)) setget set_aabb

#RENDERING DATA
var z_order_size: int setget _set_z_order_size
var is_rendered: bool = false

#EDITOR DATA
var debug_z: int = 0
var temporary: bool = true

#OUTLINE DATA
var left_points: PoolVector2Array = PoolVector2Array()
var right_points: PoolVector2Array = PoolVector2Array()
var up_points: PoolVector2Array = PoolVector2Array()
var down_points: PoolVector2Array = PoolVector2Array()

func _enter_tree():
	z_order_size = 1
	update_z_order_size(z_order_size)

func _exit_tree():
	update_z_order_size(-z_order_size)		

func _set_z_order_size(new_z: int) -> void:
	var old_z = z_order_size
	var delta = new_z - old_z
	if delta != 0:
		update_z_order_size(delta)
	z_order_size = new_z

func update_z_order_size(change: int) -> void:
	var parent = self.get_parent() as IsoPositionable
	if parent:
		var parent_z_order_size = parent.z_order_size
		parent.z_order_size = parent_z_order_size + change

	
func set_aabb(ab: AABB) -> void:
	aabb = ab
	position = MapSettings.get_screen_coord_from_3d(ab.position)
	iso_position = position
	_on_resize(ab.size)

func get_hexagone_coordinates() -> Transform2D:
	var hexa_coord: Transform2D = Transform2D()
	var ortho_position: Vector3 = self.aabb.position
	var size: Vector3 = self.aabb.size
	var upper_point: Vector3 = Vector3(ortho_position.x, ortho_position.y, ortho_position.z + MapSettings.z_ratio * size.z)
	var lower_point: Vector3 = Vector3(ortho_position.x + size.x, ortho_position.y + size.y, ortho_position.z)
	var left_point: Vector3 = Vector3(ortho_position.x, ortho_position.y + size.y, ortho_position.z)
	var right_point: Vector3 = Vector3(ortho_position.x + size.x, ortho_position.y, ortho_position.z)
	var min_x: float = upper_point.x - upper_point.z
	var max_x: float = lower_point.x - lower_point.z
	var min_y: float = upper_point.y - upper_point.z
	var max_y: float = lower_point.y - lower_point.z
	var h_min: float = left_point.x - left_point.y
	var h_max: float = right_point.x - right_point.y
	hexa_coord.x = Vector2(min_x, max_x)
	hexa_coord.y = Vector2(min_y, max_y)
	hexa_coord.origin = Vector2(h_min, h_max)
	return hexa_coord

func draw_outline():
	##Upper Lines
	draw_line(up_points[0], up_points[1], Color.red, 2.0)
	draw_line(up_points[1], up_points[2], Color.red, 2.0)
	draw_line(up_points[2], up_points[3], Color.red, 2.0)
	draw_line(up_points[3], up_points[0], Color.red, 2.0)
	
	##Vertical Lines
	draw_line(up_points[0], down_points[0], Color.red, 1.0)
	draw_line(up_points[1], down_points[1], Color.red, 2.0)
	draw_line(up_points[2], down_points[2], Color.red, 2.0)
	draw_line(up_points[3], down_points[3], Color.red, 2.0)
	
	##Lower Lines
	draw_line(down_points[0], down_points[1], Color.red, 1.0)
	draw_line(down_points[1], down_points[2], Color.red, 2.0)
	draw_line(down_points[2], down_points[3], Color.red, 2.0)
	draw_line(down_points[3], down_points[0], Color.red, 1.0)

func _on_resize(size: Vector3) -> void:
	pass

func _grid_updated(stair: int) -> void:
	pass

func _on_select(is_selected: bool) -> void:
	pass
