tool
extends KinematicBody
class_name IsometricKinematicBody

var parent: DynamicIsometricElement

func _enter_tree() -> void:
	self.parent = get_parent()

func _physics_process(delta: float) -> void:
	if parent != null:
		if parent.has_moved():
			_recalibrate_from_parent()
			parent.set_has_moved(false)
		if !Engine.editor_hint:
			_do_physics(delta)
			parent.update_position_from_body(self)

func _recalibrate_from_parent() -> void:
	var position = parent.position3d
	self.global_transform = Transform(Basis(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1)), Vector3(position.x, position.z, position.y))

func _do_physics(delta: float) -> void:
	pass
