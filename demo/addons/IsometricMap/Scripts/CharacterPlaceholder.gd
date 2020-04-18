tool
extends BasePlaceholder
class_name CharacterPlaceholder

onready var g_ortho_position: Vector3 = self.ortho_position

var floor_num: int = 0

var is_my_character: bool = false

func _ready():
	placeholder_type = load("res://addons/IsometricMap/prefab/types/character.tres")

func _process(delta):
	var pos_delta: float = 0.3
	var need_position_refresh: bool = g_ortho_position != self.ortho_position
	if need_position_refresh:
		var direction_3d: Vector3 = (self.ortho_position - g_ortho_position)
		var distance_3d: Vector3 = direction_3d.normalized() * pos_delta
		if direction_3d.length() > distance_3d.length():
			g_ortho_position += distance_3d
			
		else:
			 g_ortho_position = self.ortho_position
		var iso_pos: Vector2 = Vector2(MapSettings.get_iso_x_from_ortho(g_ortho_position), MapSettings.get_iso_y_from_ortho(g_ortho_position))
		set_position(iso_pos)
		update()
		
		
func is_on_right_location() -> bool:
	return g_ortho_position == self.ortho_position

func _prepare_points():
	var w = 0
	var d = 0
	var h = 0

	var pos = self.position
	w = self.width
	d = self.depth
	h = self.height
	var tile_height = MapSettings.tile_height
	var tile_width= MapSettings.tile_width
	var x = pos.x
	var y = pos.y
	var points = PoolVector2Array()

	var offset = Vector2(0, - tile_height * 0.5)

	var ratio = 0
	if h > 0:
		ratio =  float(self.debug_z) / h

	#lower points
	points.push_back(Vector2(0, 0))
	points.push_back(Vector2(tile_width * 0.5 * w, tile_height * 0.5 * w))
	points.push_back(Vector2(tile_width * 0.5 * (w - d), tile_height * 0.5 * (d + w)))
	points.push_back(Vector2(-tile_width * 0.5 * d, tile_height * 0.5 * d))

	#upper points
	var height_offset = Vector2(0, - MapSettings.e_z * h)
	points.push_back(points[0] + height_offset)
	points.push_back(points[1] + height_offset)
	points.push_back(points[2] + height_offset)
	points.push_back(points[3] + height_offset)

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
		self.debug_points.push_back(offset + points[0] + grid_offset)
		self.debug_points.push_back(offset + points[1] + grid_offset)
		self.debug_points.push_back(offset + points[2] + grid_offset)
		self.debug_points.push_back(offset + points[3] + grid_offset)
