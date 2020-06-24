tool
extends IsometricKinematicBody
class_name RollingBallBody

var linear_velocity: Vector3

export(float) var gravity: float
export(int) var speed: int

func _recalibrate_from_parent() -> void:
	._recalibrate_from_parent()

func _do_physics(delta: float) -> void:
	linear_velocity += Vector3(0, -gravity * delta, 0)
	
	var vertical_velocity: Vector3 = Vector3(0, linear_velocity.y, 0)
	
	linear_velocity = vertical_velocity
	linear_velocity = move_and_slide(linear_velocity, Vector3(0, 1, 0))
