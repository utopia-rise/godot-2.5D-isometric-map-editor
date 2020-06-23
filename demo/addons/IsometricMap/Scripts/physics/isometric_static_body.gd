tool
extends StaticBody
class_name IsometricStaticBody

var parent

func _enter_tree():
	self.parent = get_parent()

func _physics_process(delta):
	if parent != null && parent.has_moved():
		_recalibrate_from_parent()
		parent.set_has_moved(false)

func _recalibrate_from_parent():
	var position = parent.position3D
	self.global_transform = Transform(Basis(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1)), Vector3(position.x, position.z, position.y))
