tool
extends Node

var terrain_types: PlaceholderTypes = load("res://addons/IsometricMap/Config/placeholder_types.tres")

var tile_width: int = 256
var tile_height: int = 128
var tile_Z_length: int = 128

var e_z: int = int((tile_height / sin(deg2rad(30)) / sqrt(2)) * cos(deg2rad(30)))
var z_ratio: float = float(e_z)/tile_Z_length

func _init():
	print("width: ", tile_width)
	print("height: ", tile_height)
	var angle = atan2(tile_width, tile_height) * 360 / PI
	print("wide angle: ", angle)
	print("small angle: ", (180 - angle) /2)
	var visual_unit = sqrt(pow(tile_width, 2) + pow(tile_height, 2)) /2
	var true_unit = visual_unit/cos(PI/4)
	print("visual unit: ", visual_unit)
	print("true unit: ", true_unit)

	#This formule give the angle for perfect alignement of cube in false isometric 3D
	var game_top_angle = atan(sin(PI/4))
	#tile_Z_length = int(true_unit * cos(game_top_angle))
	print("depth unit: ", tile_Z_length)
	print("half_depth unit: ", int(tile_Z_length/2))
	#tile_Z_length = tile_Z_length * 0.5
	
	print("z_ratio:", z_ratio)

func get_3d_coord_from_screen(pos: Vector2, orth_z: int) -> Vector3:
	var iso_x = pos.x
	var iso_y = pos.y
	var orth_x = iso_x/tile_width + (iso_y + orth_z * e_z)/tile_height
	var orth_y = (iso_y + orth_z * e_z)/tile_height - iso_x/tile_width
	return Vector3(orth_x, orth_y, orth_z)

func get_screen_coord_from_3d(pos: Vector3) -> Vector2:
	return Vector2((pos.x - pos.y) * tile_width * 0.5, (pos.x + pos.y) * tile_height * 0.5 - e_z * pos.z)

func do_hexagone_overlap(hex1: Transform2D, hex2: Transform2D) -> bool:
	return !(hex1.x.x >= hex2.x.y || hex2.x.x >= hex1.x.y) and !(hex1.y.x >= hex2.y.y || hex2.y.x >= hex1.y.y) and !(hex1.origin.x >= hex2.origin.y || hex2.origin.x >= hex1.origin.y)

# return true id box is in front of other
func is_box_in_front(box: AABB, other: AABB) -> bool:
	if box.end.x <= other.position.x:
		return false
	elif other.end.x <= box.position.x:
		return true
	
	if box.end.y <= other.position.y:
		return false
	elif other.end.y <= box.position.y:
		return true
	
	if box.end.z <= other.position.z:
		return false
	elif other.end.z <= box.position.z:
		return true
	return false
