tool
extends IsometricKinematicBody
class_name ExampleKinematicBodyAutoshapeImpl

var collision_shape: CollisionShape = CollisionShape.new()
var shape: CapsuleShape = CapsuleShape.new()
var linear_velocity: Vector3

export(float) var gravity: float
export(int) var speed: int

func _init():
	add_child(collision_shape)
	collision_shape.set_owner(self)

func _recalibrate_from_parent() -> void:
	._recalibrate_from_parent()
	var size = parent.size3d
	var position = parent.get_global_3D_position()
	var shape_radius = sqrt(size.x * size.x + size.y * size.y) * 0.5
	var shape_height = size.z - 2 * shape_radius
	collision_shape.global_transform = Transform(Basis(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1)), Vector3(position.x + size.x * 0.5, position.z + 0.5 * size.z, position.y + size.y * 0.5))
	collision_shape.rotate_x(deg2rad(90));
	calculate_collision_shape()

func _do_physics(delta: float) -> void:
	linear_velocity += Vector3(0, -gravity * delta, 0)
	
	var horizontal_velocity: Vector3 = Vector3()
	var vertical_velocity: Vector3 = Vector3(0, linear_velocity.y, 0)
	
	if Input.is_action_pressed("player_goes_forward"):
		horizontal_velocity += Vector3(-1, 0, -1).normalized() * speed
	if Input.is_action_pressed("player_goes_backward"):
		horizontal_velocity += Vector3(1, 0, 1).normalized() * speed
	if Input.is_action_pressed("player_goes_left"):
		horizontal_velocity += Vector3(-1, 0, 1).normalized() * speed
	if Input.is_action_pressed("player_goes_right"):
		horizontal_velocity += Vector3(1, 0, -1).normalized() * speed
	
	linear_velocity = horizontal_velocity + vertical_velocity
	linear_velocity = move_and_slide(linear_velocity, Vector3(0, 1, 0))

func calculate_collision_shape() -> void:
	if parent != null:
		var size = parent.size3d
		var shape_radius = sqrt(size.x * size.x + size.y * size.y) * 0.5
		var shape_height = size.z - 2 * shape_radius
		shape_height = shape_height if shape_height > 0 else 0
		shape.set_radius(shape_radius);
		shape.set_height(shape_height);
		collision_shape.set_shape(shape);
