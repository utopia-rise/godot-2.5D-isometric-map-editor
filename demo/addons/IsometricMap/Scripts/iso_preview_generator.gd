tool
extends Resource

class_name IsoPreviewGenerator

signal image_generated(treeitem, texture)

var root_node: Node

func generate_from_path(path: String, size: Vector2, treeitem: TreeItem) -> Texture:
	var viewport := Viewport.new()
	var scene := load(path).instance() as IsoPositionable
	var hexa_coord := scene.get_hexagone_coordinates()
	var x_scene_size := hexa_coord.x.y - hexa_coord.x.x
	var y_scene_size := hexa_coord.y.y - hexa_coord.y.x
	scene.scale = scene.scale / Vector2(x_scene_size, y_scene_size)
	scene.position = size / 2
	viewport.render_target_update_mode = Viewport.UPDATE_ALWAYS
	viewport.set_clear_mode(Viewport.CLEAR_MODE_ONLY_NEXT_FRAME)
	viewport.size = size
	viewport.add_child(Camera2D.new())
	viewport.add_child(scene)
	root_node.call_deferred("add_child", viewport)
	yield(root_node.get_tree(), "idle_frame")
	yield(root_node.get_tree(), "idle_frame")
	var image_texture := ImageTexture.new()
	var image := Image.new()
	var viewport_image := viewport.get_texture().get_data()
	viewport_image.flip_y()
	image.copy_from(viewport_image)
	image_texture.create_from_image(image)
	root_node.remove_child(viewport)
	emit_signal("image_generated", treeitem, image_texture)
	return image_texture

func _init(node: Node):
	self.root_node = node