extends Node

class_name MapEditionHandler

var stair_selector: StairSelector = StairSelector.new()
var grid_cursor: GridCursor = GridCursor.new()

var map_ref: WeakRef
var map: IsometricMap = null
var selected_positionable = null
var selected_tile_item: TreeItem
var loaded_positionable = null

var undo_redo: UndoRedo
var editor_interface: EditorInterface
var isometric_asset_selector: IsometricAssetSelector

enum DragAction {
	NONE,
	TILING
}

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD
}

enum Axes {
	X,
	Y,
	Z
}

var drag_action: int = DragAction.NONE

func _init(iso_map, undo: UndoRedo, editor_interface: EditorInterface, asset_selector: IsometricAssetSelector):
	undo_redo = undo
	self.editor_interface = editor_interface
	self.isometric_asset_selector = asset_selector
	asset_selector.tiles_tree.connect("cell_selected", self, "on_tile_selected")
	asset_selector.maps_tree.connect("cell_selected", self, "on_map_selected")
	map_ref = weakref(iso_map)
	map = iso_map
	map.add_child(stair_selector)
	map.add_child(grid_cursor)
	print("stair selector parent: " + str(stair_selector.get_parent()))
	for child in map.get_children():
		if isIsopositionable(child):
			child.add_to_group("positionables", false)
			child.update()
	drag_action = DragAction.NONE
	map.update()

func reset(signal_argument):
	print("reset called with: " + str(signal_argument))
	map_ref = null
	map = null
	selected_positionable = null
	loaded_positionable = null
	drag_action = DragAction.NONE

func edit_placeholder(placeholder: IsometricPlaceholder):
	select_positionable(placeholder)
	drag_action = DragAction.NONE

func forward_canvas_gui_input(event: InputEvent) -> bool:
	if event is InputEventMouseMotion:
		event as InputEventMouseMotion
		if loaded_positionable != null and is_instance_valid(loaded_positionable):
			if drag_action == DragAction.TILING:
				if selected_positionable != null :
					var target_position: Vector3 = IsoServer.get_3d_coord_from_screen(map.get_local_mouse_position(), stair_selector.selected_stair).round()
					if selected_positionable.get_class() == "IsometricPlaceholder":
						var positionable_pos: Vector3 = selected_positionable.position3d
						if target_position != positionable_pos:
							var width_offset: int = target_position.x - positionable_pos.x + 1
							var depth_offset: int = target_position.y - positionable_pos.y + 1
							var future_aabb: AABB = AABB(positionable_pos, Vector3(width_offset, depth_offset, selected_positionable.size3d.z))
							if !map.is_overlapping_aabb(future_aabb) and width_offset >= 0 and 1 + target_position.x <= map.size3d.x and depth_offset >= 0 and 1 + target_position.y <= map.size3d.y and !(width_offset == depth_offset and width_offset == 0):
								selected_positionable.set_aabb(future_aabb)
						return true
					else:
						if loaded_positionable.get_class() == "IsometricTile":
							var positionable_size = loaded_positionable.size3d
							var future_aabb: AABB = AABB(target_position, positionable_size)
							var is_position_positive := target_position.x >= 0 and target_position.y >= 0 and target_position.z >= 0
							var is_in_map = target_position.x + positionable_size.x <= map.size3d.x and target_position.y + positionable_size.y <= map.size3d.y and target_position.z + positionable_size.z <= map.size3d.z
							if !map.is_overlapping_aabb(future_aabb) and is_position_positive and is_in_map:
								select_positionable(loaded_positionable)
								selected_positionable.set_aabb(AABB(IsoServer.get_3d_coord_from_screen(map.get_local_mouse_position(), stair_selector.selected_stair).round(), selected_positionable.size3d))
								selected_positionable.visible = true
								selected_positionable.modulate.a = 1
								map.remove_child(selected_positionable)
								undo_redo.create_action("add_tile")
								undo_redo.add_do_method(map, "add_iso_positionable", selected_positionable)
								undo_redo.add_do_method(selected_positionable, "set_owner", editor_interface.get_edited_scene_root())
								undo_redo.add_do_method(selected_positionable, "_on_grid_updated", stair_selector.selected_stair)
								undo_redo.add_undo_method(map, "remove_iso_positionable", selected_positionable)
								undo_redo.commit_action()
								load_iso_for_edition(false)
								return true
			else:
				if !loaded_positionable.get_class() == "IsometricPlaceholder":
					var target_position: Vector3 = IsoServer.get_3d_coord_from_screen(map.get_local_mouse_position(), stair_selector.selected_stair).round()
					var positionable_size = loaded_positionable.size3d
					var future_aabb: AABB = AABB(target_position, positionable_size)
					var is_position_positive := target_position.x >= 0 and target_position.y >= 0 and target_position.z >= 0
					var is_in_map = target_position.x + positionable_size.x <= map.size3d.x and target_position.y + positionable_size.y <= map.size3d.y and target_position.z + positionable_size.z <= map.size3d.z
					if !map.is_overlapping_aabb(future_aabb) and is_position_positive and is_in_map:
						loaded_positionable.set_aabb(future_aabb)
						loaded_positionable.visible = true
						return true
					else:
						loaded_positionable.visible = false
						return false
				else:
					return false
	elif event is InputEventMouseButton:
		if event.is_pressed():
			if event.button_index == BUTTON_LEFT:
				var is_selecting_existing := check_and_select_existing()
				if !is_selecting_existing:
					select_positionable(loaded_positionable)
					if selected_positionable.get_class() == "IsometricMap":
						selected_positionable.modulate.a = 1
						selected_positionable.visible = true
						selected_positionable.set_aabb(AABB(IsoServer.get_3d_coord_from_screen(map.get_local_mouse_position(), stair_selector.selected_stair).round(), selected_positionable.size3d))
						map.remove_child(selected_positionable)
						undo_redo.create_action("add_map")
						undo_redo.add_do_method(map, "add_iso_positionable", selected_positionable)
						undo_redo.add_do_method(selected_positionable, "set_owner", editor_interface.get_edited_scene_root())
						undo_redo.add_do_method(selected_positionable, "_on_grid_updated", stair_selector.selected_stair)
						undo_redo.add_undo_method(map, "remove_iso_positionable", selected_positionable)
						undo_redo.commit_action()
						load_iso_for_edition(selected_positionable.get_class() == "IsometricMap")
						return true
					elif selected_positionable.get_class() == "IsometricTile":
						var ortho_pos: Vector3 = IsoServer.get_3d_coord_from_screen(map.get_local_mouse_position(), stair_selector.selected_stair).round()
						if 0 <= ortho_pos.x and 1 + ortho_pos.x <= map.size3d.x and 0 <= ortho_pos.y and 1 + ortho_pos.y <= map.size3d.y:
							selected_positionable.set_aabb(AABB(IsoServer.get_3d_coord_from_screen(map.get_local_mouse_position(), stair_selector.selected_stair).round(), selected_positionable.size3d))
							selected_positionable.visible = true
							selected_positionable.modulate.a = 1
							map.remove_child(selected_positionable)
							undo_redo.create_action("add_tile")
							undo_redo.add_do_method(map, "add_iso_positionable", selected_positionable)
							undo_redo.add_do_method(selected_positionable, "set_owner", editor_interface.get_edited_scene_root())
							undo_redo.add_do_method(selected_positionable, "_on_grid_updated", stair_selector.selected_stair)
							undo_redo.add_undo_method(map, "remove_iso_positionable", selected_positionable)
							undo_redo.commit_action()
							load_iso_for_edition(false)
							drag_action = DragAction.TILING
							return true
						else:
							return false
					elif selected_positionable.get_class() == "IsometricPlaceholder":
						var ortho_pos: Vector3 = IsoServer.get_3d_coord_from_screen(map.get_local_mouse_position(), stair_selector.selected_stair).round()
						if 0 <= ortho_pos.x and 1 + ortho_pos.x <= map.size3d.x and 0 <= ortho_pos.y and 1 + ortho_pos.y <= map.size3d.y:
							selected_positionable.position3d = ortho_pos
							if !map.is_overlapping(selected_positionable):
								selected_positionable.debug_z = 0
								map.add_child(selected_positionable)
								selected_positionable.set_owner(map)
								print("set position : " + str(selected_positionable.get_position()))
								drag_action = DragAction.TILING
								return true
					else :
						return selected_positionable != null
				else:
					return true
			elif event.button_index == BUTTON_RIGHT:
				pass
		else:
			if event.button_index == BUTTON_LEFT:
				if drag_action == DragAction.TILING:
					if selected_positionable != null:
						if selected_positionable.get_class() == "IsometricPlaceholder":
							print("finished creating placeholder")
							var root_node: Node = editor_interface.get_edited_scene_root()
							var positionable_pos: Vector3 = IsoServer.get_3d_coord_from_screen(selected_positionable.iso_position, stair_selector.selected_stair).round()
							selected_positionable.position3d = positionable_pos
							map.remove_child(selected_positionable)
							undo_redo.create_action("create_placeholder")
							undo_redo.add_do_method(map, "add_iso_positionable", selected_positionable)
							undo_redo.add_do_method(selected_positionable, "set_owner", root_node)
							undo_redo.add_do_method(selected_positionable, "_on_grid_updated", stair_selector.selected_stair)
							undo_redo.add_undo_method(map, "remove_iso_positionable", selected_positionable)
							undo_redo.commit_action()
							drag_action = DragAction.NONE
							scene_from_tile_tree(false)
							return true
						else:
							drag_action = DragAction.NONE
			elif event.button_index == BUTTON_RIGHT:
				pass
	elif event is InputEventKey:
		event as InputEventKey
		if(event.is_pressed()):
			match event.scancode:
				KEY_Y:
					if event.control and drag_action == DragAction.NONE:
						undo_redo.redo()
				KEY_Z:
					if event.command and event.shift and drag_action == DragAction.NONE:
						undo_redo.redo()
					elif (event.control or event.command) and drag_action == DragAction.NONE:
						undo_redo.undo()
					else:
						undo_redo.create_action("move_z_volume_up")
						undo_redo.add_do_method(self, "move_z_volume", selected_positionable, true)
						undo_redo.add_undo_method(self, "move_z_volume", selected_positionable, false)
						undo_redo.commit_action()
					return true
				KEY_S:
					if !(event.control or event.command):
						undo_redo.create_action("move_z_volume_down")
						undo_redo.add_do_method(self, "move_z_volume", selected_positionable, false)
						undo_redo.add_undo_method(self, "move_z_volume", selected_positionable, true)
						undo_redo.commit_action()
						return true
				KEY_C:
					if selected_positionable.get_class() == "IsometricPlaceholder":
						undo_redo.create_action("switch_slope_type")
						undo_redo.add_do_method(self, "switch_slope_type", selected_positionable)
						undo_redo.add_undo_method(self, "reverse_switch_slope_type", selected_positionable)
						undo_redo.commit_action()
					return true
				KEY_E:
					if drag_action == DragAction.NONE:
						return move_grid(true)
				KEY_D:
					if drag_action == DragAction.NONE:
						return move_grid(false)
				KEY_BACKSPACE:
					if drag_action == DragAction.NONE:
						if event.control:
							undo_redo.create_action("remove_iso_positionable")
							print("control backspace")
							for child in map.get_children():
								print("ctrl back : " + str(child))
								if isIsopositionable(child) and child != loaded_positionable:
									undo_redo.add_do_method(map, "remove_iso_positionable", child)
									undo_redo.add_undo_method(map, "add_iso_positionable", child)
							undo_redo.commit_action()
						else:
							if selected_positionable != null:
								remove_iso_positionable(selected_positionable)
					else:
						map.remove_iso_positionable(selected_positionable)
						drag_action = DragAction.NONE
					return true
				KEY_O:
					if event.shift:
						move_iso_positionable(selected_positionable, Direction.UP, true)
					else:
						move_iso_positionable(selected_positionable, Direction.FORWARD, true)
					return true
				KEY_L:
					if event.shift:
						move_iso_positionable(selected_positionable, Direction.DOWN, true)
					else:
						move_iso_positionable(selected_positionable, Direction.BACKWARD, true)
					return true
				KEY_K:
					move_iso_positionable(selected_positionable, Direction.LEFT, true)
					return true
				KEY_M:
					move_iso_positionable(selected_positionable, Direction.RIGHT, true)
					return true
				KEY_V:
					add_dimension_before(Axes.X)
					return true
				KEY_B:
					add_dimension_before(Axes.Y)
					return true
				KEY_N:
					add_dimension_before(Axes.Z)
					return true
	return false
	
	# ---------- UndoRedo Funcs
func remove_iso_positionable(iso_positionable) -> void:
	var root_node: Node = editor_interface.get_edited_scene_root()
	var positionable_pos: Vector3 = iso_positionable.position3d
	undo_redo.create_action("remove_iso_positionable")
	undo_redo.add_do_method(map, "remove_iso_positionable", iso_positionable)
	if iso_positionable.get_class() == "IsometricPlaceholder":
		undo_redo.add_do_method(self, "deselect_positionable", iso_positionable)
	undo_redo.add_undo_method(map, "add_iso_positionable", iso_positionable)
	undo_redo.add_undo_method(iso_positionable, "set_owner", root_node)
	undo_redo.add_undo_method(iso_positionable, "_on_grid_updated", stair_selector.selected_stair)
	undo_redo.commit_action()

func deselect_positionable(positionable):
	if selected_positionable == positionable:
		selected_positionable = null

func move_z_volume(positionable, up: bool) -> void:
	print(str(positionable))
	if positionable != null and positionable.get_class() == "IsometricPlaceholder":
		map.remove_iso_positionable(positionable)
		var future_aabb: = AABB(positionable.position3d, positionable.size3d)
		var offset: int = 0
		if up and positionable.position3d.z + positionable.size3d.z < map.size3d.z:
			future_aabb.size.z += 1
		elif !up and positionable.size3d.z > 0:
			future_aabb.size.z -= 1
		if !map.is_overlapping_aabb(future_aabb):
			positionable.set_aabb(future_aabb)
		map.add_iso_positionable(positionable)
		positionable._on_grid_updated(stair_selector.selected_stair)

func switch_slope_type(placeholder):
	if placeholder != null and placeholder.get_class() == "IsometricPlaceholder":
		if placeholder.slope_type == placeholder.SlopeType.size() - 1:
			placeholder.slope_type = 0
		else:
			placeholder.slope_type += 1

func reverse_switch_slope_type(placeholder):
	if placeholder != null and placeholder.get_class() == "IsometricPlaceholder":
		if placeholder.slope_type == 0:
			placeholder.slope_type = placeholder.SlopeType.size() - 1
		else:
			placeholder.slope_type -= 1
# ----------

func move_grid(up: bool) -> bool:
	var result  = stair_selector.move_selected_stair(up)
	grid_cursor.selected_stair = stair_selector.selected_stair
	grid_cursor.update()
	return result

func add_dimension_before(axe: int) -> void:
	var direction_to_move: int
	var reverse_direction: int
	var future_aabb: AABB
	var current_aabb = map.get_aabb() #TODO : add method to get aabb
	if axe == Axes.X:
		future_aabb = AABB(current_aabb.position, current_aabb.size + Vector3(1, 0, 0))
		direction_to_move = Direction.RIGHT
		reverse_direction = Direction.LEFT
	elif axe == Axes.Y:
		future_aabb = AABB(current_aabb.position, current_aabb.size + Vector3(0, 1, 0))
		direction_to_move = Direction.BACKWARD
		reverse_direction = Direction.FORWARD
	elif axe == Axes.Z:
		future_aabb = AABB(current_aabb.position, current_aabb.size + Vector3(0, 0, 1))
		direction_to_move = Direction.UP
		reverse_direction = Direction.DOWN
	undo_redo.create_action("add_dimension_before")
	undo_redo.add_do_method(map, "set_aabb", future_aabb)
	for child in map.get_children():
		if isIsopositionable(child):
			undo_redo.add_do_method(self, "move_iso_positionable", child, direction_to_move, false)
			undo_redo.add_undo_method(self, "move_iso_positionable", child, reverse_direction, false)
	undo_redo.add_undo_method(map, "set_aabb", current_aabb)
	undo_redo.commit_action()

func move_iso_positionable(iso_positionable, direction: int, as_action: bool) -> void:
	if iso_positionable != null:
		var current_aabb = iso_positionable.get_aabb()
		var current_position = current_aabb.position
		var current_size = current_aabb.size
		var future_position: Vector3
		map.remove_iso_positionable(iso_positionable)
		if direction == Direction.UP:
			future_position = current_position + Vector3(0, 0, 1)
		elif direction == Direction.DOWN:
			future_position = current_position - Vector3(0, 0, 1)
		elif direction == Direction.LEFT:
			future_position = current_position - Vector3(1, 0, 0)
		elif direction == Direction.RIGHT:
			future_position = current_position + Vector3(1, 0, 0)
		elif direction == Direction.FORWARD:
			future_position = current_position - Vector3(0, 1, 0)
		elif direction == Direction.BACKWARD:
			future_position = current_position + Vector3(0, 1, 0)
		var future_aabb := AABB(future_position, current_size)
		var is_position_positive := future_position.x >= 0 and future_position.y >= 0 and future_position.z >= 0
		var is_in_map = future_position.x + current_size.x <= map.size3d.x and future_position.y + current_size.y <= map.size3d.y and future_position.z + current_size.z <= map.size3d.z
		if !map.is_overlapping_aabb(future_aabb) and is_position_positive and is_in_map:
			if as_action:
				undo_redo.create_action("move_iso_positionable")
				undo_redo.add_do_method(iso_positionable, "set_aabb", future_aabb)
				undo_redo.add_do_method(map, "add_iso_positionable", iso_positionable)
				undo_redo.add_do_method(iso_positionable, "set_owner", editor_interface.get_edited_scene_root())
				undo_redo.add_do_method(iso_positionable, "_on_grid_updated", stair_selector.selected_stair)
				undo_redo.add_undo_method(map, "remove_iso_positionable", iso_positionable)
				undo_redo.add_undo_method(iso_positionable, "set_aabb", current_aabb)
				undo_redo.add_undo_method(map, "add_iso_positionable", iso_positionable)
				undo_redo.add_undo_method(iso_positionable, "set_owner", editor_interface.get_edited_scene_root())
				undo_redo.add_undo_method(iso_positionable, "_on_grid_updated", stair_selector.selected_stair)
				undo_redo.commit_action()
			else:
				iso_positionable.set_aabb(future_aabb)
				map.add_iso_positionable(iso_positionable)
				iso_positionable.set_owner(editor_interface.get_edited_scene_root())
				iso_positionable._on_grid_updated(stair_selector.selected_stair)
		else:
			map.add_iso_positionable(iso_positionable)
			iso_positionable.set_owner(editor_interface.get_edited_scene_root())
			iso_positionable._on_grid_updated(stair_selector.selected_stair)

func select_positionable(positionable):
	print("selecting " + str(positionable))
	if selected_positionable != null:
		selected_positionable._on_select(false)
	selected_positionable = positionable
	if positionable != null:
		positionable._on_select(true)

func load_positionable(positionable) -> void:
	loaded_positionable = positionable

func unload_positionable() -> void:
	if loaded_positionable != null and is_instance_valid(loaded_positionable):
		if loaded_positionable.get_class() == "IsometricMap":
			if !map.grid_3d.has(loaded_positionable):
				map.remove_child(loaded_positionable)
		loaded_positionable.queue_free()
		loaded_positionable = null

func create_new_placeholder() -> void:
	var root_node: Node = editor_interface.get_edited_scene_root()
	load_positionable(IsometricPlaceholder.new())

func check_and_select_existing() -> bool:
	for z in range(map.size3d.z, 0, -1):
		var ortho_pos: Vector3 = IsoServer.get_3d_coord_from_screen(map.get_local_mouse_position(), z-1).round()
		var posi = map.get_positionable_at(ortho_pos)
		if posi != null:
			if posi.position3d.z + posi.size3d.z > stair_selector.selected_stair:
				select_positionable(posi)
				editor_interface.inspect_object(posi)
				return true
	return false

func create_new_map() -> bool:
	var created_map: IsometricMap = load(selected_tile_item.get_metadata(0)).instance()
	if (created_map != null):
		load_positionable(created_map)
		return true
	return false
	
func create_new_tile() -> bool:
	var created_tile: IsometricTile = load(selected_tile_item.get_metadata(0)).instance()
	if (created_tile != null):
		load_positionable(created_tile)
		return true
	return false	

func scene_from_tile_tree(is_map: bool) -> void:
	if selected_tile_item != null:
		var node_path: String = selected_tile_item.get_metadata(0)
		if is_map:
			create_new_map()
		else:
			if node_path == "placeholder":
				create_new_placeholder()
			else:
				create_new_tile()

func load_iso_for_edition(is_map: bool) -> void:
	scene_from_tile_tree(is_map)
	if not loaded_positionable.get_class() == "IsometricPlaceholder":
		loaded_positionable.visible = false
		loaded_positionable.modulate.a = 0.5
		map.add_child(loaded_positionable)

func on_tile_selected() -> void:
	unload_positionable()
	selected_tile_item = isometric_asset_selector.tiles_tree.get_selected()
	load_iso_for_edition(false)

func on_map_selected() -> void:
	unload_positionable()
	selected_tile_item = isometric_asset_selector.maps_tree.get_selected()
	load_iso_for_edition(true)

func isIsopositionable(object):
	var object_class = object.get_class()
	return object_class == "IsometricTile" or object_class == "IsometricMap" or object_class == "IsometricPlaceholder"
