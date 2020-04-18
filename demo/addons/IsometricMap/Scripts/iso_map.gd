tool
extends IsoPositionable
class_name IsoMap

# Do we draw tile lines
export (bool) var draw_tiles = true setget set_draw

# reference to draw_grid function
var fun_get_grid = funcref(self, 'grid_iterator')
var fun_draw_debug = funcref(self, 'draw_debug')

var current_sorting_order: int = 0

var grid_3d: Grid3D = Grid3D.new()
var edition_grid_3d: Grid3D = Grid3D.new()

func _init():
	grid_3d.updateArraySize(self.aabb.size, true)

func _on_resize(size: Vector3) -> void:
	grid_3d.updateArraySize(size, false)
	edition_grid_3d.updateArraySize(size, false)

func set_draw(b: bool):
	draw_tiles = b
	update()

func _draw():
	pass

func _process(delta):
	generate_topoligical_render_graph()

func generate_topoligical_render_graph():
	current_sorting_order = 0
	for child in get_children():
		if child is IsoPositionable:
			child as IsoPositionable
			child.is_rendered = false
	for child in get_children():
		if child is IsoPositionable:
			child as IsoPositionable
			if !child.is_rendered:
				render_iso_node(child)

func render_iso_node(iso_node: IsoPositionable):
	iso_node.is_rendered = true
	var max_z_size = 0
	var iso_nodes: Array = get_positionable_behind(iso_node)
	for node in iso_nodes:
		node as IsoPositionable
		if !node.is_rendered:
			render_iso_node(node)
		max_z_size = max(node.z_order_size, max_z_size)
	current_sorting_order +=  max_z_size
	iso_node.z_index = current_sorting_order
	current_sorting_order += 1


func get_positionable_behind(iso_node: IsoPositionable) -> Array:
	var iso_nodes: Array = Array()
	for child in get_children():
		child = child as IsoPositionable
		if child and child != iso_node:
				if MapSettings.do_hexagone_overlap(iso_node.get_hexagone_coordinates(), child.get_hexagone_coordinates()):
					if MapSettings.is_box_in_front(iso_node.aabb, child.aabb):
						iso_nodes.append(child)
	return iso_nodes

###### Undo Redo Func

func add_iso_positionable(iso_node: IsoPositionable):
	iso_node.temporary = false
	iso_node.debug_z = 0
	grid_3d.set_data(iso_node.aabb.position, iso_node)
	edition_grid_3d.insert_box(iso_node.aabb, iso_node)
	iso_node.add_to_group("positionables", false)

func remove_iso_positionable(iso_node: IsoPositionable):
	self.remove_child(iso_node)
	grid_3d.set_data(iso_node.aabb.position, null)
	edition_grid_3d.insert_box(iso_node.aabb, iso_node, true)
	if iso_node.is_in_group("positionables"):
		iso_node.remove_from_group("positionables")
	iso_node.update()
######

func _grid_updated(stair: int) -> void:
	for child in get_children():
		child._grid_updated(stair - self.aabb.position.z)
