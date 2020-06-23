tool
extends IsometricKinematicBody
class_name ExampleKinematicBodyAutoshapeImpl

var shape: CollisionShape

func _ready():
	shape = $CollisionShape

func _recalibrate_from_parent() -> void:
	._recalibrate_from_parent()

func _do_physics(delta: float) -> void:
	pass
