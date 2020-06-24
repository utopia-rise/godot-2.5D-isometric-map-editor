tool
extends IsometricKinematicBody
class_name ExampleKinematicBodySimpleImpl

var linear_velocity: Vector3

export(float) var gravity: float
export(int) var speed: int

func _recalibrate_from_parent() -> void:
	._recalibrate_from_parent()

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
