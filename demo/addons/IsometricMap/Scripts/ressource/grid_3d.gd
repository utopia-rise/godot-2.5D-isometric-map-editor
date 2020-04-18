extends Reference
class_name Grid3D

export(bool) var erase: bool = false setget reset

export(int, 1, 100) var width: int = 1 setget set_width
export(int, 1, 100) var depth: int = 1 setget set_depth
export(int, 1, 100) var height: int = 1 setget set_height

var position: Vector3 = Vector3()

export(Array) var array: Array = []

func set_width(w: int):
	updateArraySize(Vector3(w, depth, height))
	
func set_depth(d: int):
	updateArraySize(Vector3(width, d, height))
	
func set_height(h: int):
	updateArraySize(Vector3(width, depth, h))

func reset(b: bool):
	if(b):
		b = false
		updateArraySize(Vector3(width, depth, height), true)
	return

func getArraySize():
	return width * height * depth
	
func updateArraySize(size: Vector3, reset: bool = false):
	#Save old Values
	var old_size = array.size()
	var old_array = array
	var old_w = width
	var old_d = depth
	var old_h = height
	
	#Set new Values
	width = size.x
	depth = size.y
	height = size.z
	array = []

	var new_size = getArraySize()
	for i in range(new_size):
		array.append(-1)
	
	if(reset):
		return
		
	var x = 0
	var y = 0
	var z = 0
	
	for i in range(old_size):
		x = i % old_w
		y = int(i /old_w) % (old_d)
		z = int (i / (old_w * old_d))
		if(!in_range(x, y, z)):
			continue
		var value =  old_array[i]
		set_data(Vector3(x, y, z), value)
	
	return

func in_range(x, y, z):
	var b1: bool = x < width
	var b2: bool = y < depth
	var b3: bool = z < height
	return b1 && b2 && b3
	
func foreach_indexed_3d(ref_to_func):
	var pos = Vector3()
	var array_size = getArraySize()
	for i in range(array_size):
		var res = array[i]
		ref_to_func.call_func(pos, res)
		pos.x += 1
		if pos.x == width:
			pos.x = 0
			pos.y += 1
			if pos.y == depth:
				pos.y = 0
				pos.z += 1
				
func foreach_indexed_relative_3d(ref_to_func):
	var pos = position
	var rel_width = width + position.x
	var rel_depth = depth + position.y
	var array_size = getArraySize()
	for i in range(array_size):
		var id = array[i]
		if id > -1:
			var res = array[i]
			ref_to_func.call_func(pos, res)
		pos.x += 1
		if pos.x == rel_width:
			pos.x = position.x
			pos.y += 1
			if pos.y == rel_depth:
				pos.y = position.y
				pos.z += 1

func foreach_3d(ref_to_func):
	for item in array:
		ref_to_func.call_func(item)

func set_data(position: Vector3, data) -> void:
	array[position.x + width * position.y + width * depth * position.z] = data

func get_data(position: Vector3):
	return array[position.x + width * position.y + width * depth * position.z] if position.x in range(0, width) and position.y in range(0, depth) and position.z in range(0, height) else null
	
func getPosition3D(id) -> Vector3:
	var x = id % width
	var y = int(id /width) % (depth)
	var z = int (id/ (width * depth))
	return Vector3(x, y, z)

func insert_box(aabb: AABB, data: Object, remove = false) -> bool:
	var position: = aabb.position
	var size: = aabb.size
	var index: int = self.get_id(position)
	var end_x: int = int(position.x) + size.x
	var end_y: int = int(position.y) + size.y
	var end_z: int = int(position.z) + size.z
	
	if end_x > self.width or end_y > self.depth or end_z > self.height:
		return false
	
	var plane_square: int = size.x * size.y
	var x_jump = self.width - size.x
	var y_jump = self.width * (self.depth - size.y)
	print("y_jump : "+ str(y_jump))
	print("self.width: " + str(self.width) + ", self.depth: " + str(self.depth) + ", depth: " + str(size.y))
	self.array[index] = null if remove else data
	print("insert into " + str(self.getPosition3D(index)))
	for i in range(1, size.x * size.y * size.z):
		index += x_jump if i % int(size.x) == 0 else 0
		index += y_jump if i % plane_square == 0 else 0
		index += 1
		self.array[index] = null if remove else data
		print("insert into " + str(self.getPosition3D(index)))
	return true

func get_id(position: Vector3) -> int:
	return int(position.x + width * position.y + width * depth * position.z)

func is_overlapping(aabb: AABB) -> bool:
	var index: int = self.get_id(aabb.position)
	var size: = aabb.size
	var plane_square: int = size.x * size.y
	var x_jump = self.width - size.x
	var y_jump = self.width * (self.depth - size.y)
	if self.array[index] is IsoPositionable:
		return true
	for i in range(1, size.x * size.y * size.z):
		index += x_jump if i % int(size.x) == 0 else 0
		index += y_jump if i % plane_square == 0 else 0
		index += 1
		if self.array[index] is IsoPositionable:
			return true
	return false

func has(obj: Object) -> bool:
	for elmt in array:
		if elmt == obj:
			return true
	return false
