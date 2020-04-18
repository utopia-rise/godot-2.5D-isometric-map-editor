tool
extends BasePlaceholder
class_name TilePlaceholder

enum SlopeType {
	NONE,
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD
}

export (SlopeType) var slope_type: int = SlopeType.NONE setget set_slope_type

export(Dictionary) var user_data: Dictionary = Dictionary()

func _prepare_points():
	var w = 0
	var d = 0
	var h = 0

	var pos = self.position
	w = self.aabb.size.x
	d = self.aabb.size.y
	h = self.aabb.size.z
	var tile_height = MapSettings.tile_height
	var tile_width= MapSettings.tile_width
	var x = pos.x
	var y = pos.y
	var points = PoolVector2Array()

	var left_slope = 0
	var right_slope = 0
	var forward_slope = 0
	var backward_slope = 0
	var slope_offset = Vector2(0,0)

	var offset = Vector2(0, - tile_height * 0.5)
	var grid_slope_offset = Vector2(0,0)

	var ratio = 0
	if h > 0:
		ratio =  float(self.debug_z) / h
	match slope_type:
		SlopeType.LEFT:
			left_slope = 1
			self.up_color = side_slope_color
			grid_slope_offset = -Vector2(tile_width * 0.5 * w, tile_height * 0.5 * w) * ratio
		SlopeType.RIGHT:
			right_slope = 1
			self.up_color = side_slope_color
			grid_slope_offset = Vector2(tile_width * 0.5 * w, tile_height * 0.5 * w) * ratio
		SlopeType.FORWARD:
			forward_slope = 1
			self.up_color = forward_slope_color
			grid_slope_offset = -Vector2(-tile_width * 0.5 * d, tile_height * 0.5 * d) * ratio
		SlopeType.BACKWARD:
			backward_slope = 1
			self.up_color = backward_slope_color
			grid_slope_offset = Vector2(-tile_width * 0.5 * d, tile_height * 0.5 * d) * ratio

	#lower points
	points.push_back(Vector2(0, 0))
	points.push_back(Vector2(tile_width * 0.5 * w, tile_height * 0.5 * w))
	points.push_back(Vector2(tile_width * 0.5 * (w - d), tile_height * 0.5 * (d + w)))
	points.push_back(Vector2(-tile_width * 0.5 * d, tile_height * 0.5 * d))

	#upper points
	var height_offset = Vector2(0, - MapSettings.e_z * h)
	points.push_back(points[0] + (1 - (right_slope + backward_slope)) * height_offset)
	points.push_back(points[1] + (1 - (left_slope + backward_slope)) * height_offset)
	points.push_back(points[2] + (1 - (left_slope + forward_slope)) * height_offset)
	points.push_back(points[3] + (1 - (right_slope + forward_slope)) * height_offset)

	self.up_points.resize(0)
	self.up_points.push_back(offset + points[4])
	self.up_points.push_back(offset + points[5])
	self.up_points.push_back(offset + points[6])
	self.up_points.push_back(offset + points[7])

	self.left_points.resize(0)
	self.left_points.push_back(offset + points[2])
	self.left_points.push_back(offset + points[3])
	self.left_points.push_back(offset + points[7])
	self.left_points.push_back(offset + points[6])

	self.right_points.resize(0)
	self.right_points.push_back(offset + points[1])
	self.right_points.push_back(offset + points[2])
	self.right_points.push_back(offset + points[6])
	self.right_points.push_back(offset + points[5])

	self.down_points.resize(0)
	self.down_points.push_back(offset + points[0])
	self.down_points.push_back(offset + points[1])
	self.down_points.push_back(offset + points[2])
	self.down_points.push_back(offset + points[3])
	

	if self.debug_z > -1:
		var grid_offset = Vector2(0, - MapSettings.e_z * self.debug_z)
		self.debug_points.resize(0)
		self.debug_points.push_back(offset + points[0] + grid_offset + (right_slope + backward_slope) * grid_slope_offset)
		self.debug_points.push_back(offset + points[1] + grid_offset + (left_slope + backward_slope) * grid_slope_offset)
		self.debug_points.push_back(offset + points[2] + grid_offset + (left_slope + forward_slope) * grid_slope_offset)
		self.debug_points.push_back(offset + points[3] + grid_offset + (right_slope + forward_slope) * grid_slope_offset)

func set_slope_type(type: int) -> void:
	slope_type = type
	self.update()
