extends "res://addons/gut/test.gd"

var test_map: IsometricMap

func before_each():
	test_map = IsometricMap.new()

func after_all():
	test_map.queue_free()

func test_assert_map_init_values():
	var expected_position = Vector3(0, 0, 0)
	var expected_size = Vector3(1, 1, 1)
	assert_eq(test_map.position3d, expected_position, "Isometric map initial position should be " + str(expected_position) + ".")
	assert_eq(test_map.size3d, Vector3(1.0, 1.0, 1.0), "Isometric map initial size should be " + str(expected_size) + ".")
	assert_eq(test_map.get_positionable_at(expected_position), null, "Nothing should be found at " + str(expected_position))

func test_should_add_remove_iso_positionable():
	test_map.size3d = Vector3(10, 10, 10)
	var inner_pos = IsometricPositionable.new()
	inner_pos.size3d = Vector3(5, 5, 5)
	inner_pos.position3d = Vector3(1, 1, 2)
	test_map.add_iso_positionable(inner_pos)
	assert_eq(inner_pos.get_parent(), test_map, "Should have added as child iso map.")
	assert_eq(test_map.get_positionable_at(inner_pos.position3d), inner_pos, "inner_pos should be found at " + str(inner_pos.position3d))
	assert_eq(test_map.get_positionable_at(Vector3(2, 2, 2), false), inner_pos, "inner_pos should be found at " + str(Vector3(2, 2, 2)))
	var overlap_map = IsometricPositionable.new()
	overlap_map.position3d = Vector3(0, 0, 2)
	overlap_map.size3d = Vector3(5, 5, 1)
	assert_true(test_map.is_overlapping(overlap_map), "Should overlap.")
	test_map.remove_iso_positionable(inner_pos, "Should have remove isomap as child.")
	assert_eq(inner_pos.get_parent(), null)
	inner_pos.queue_free()

func test_should_not_add_iso_positionable_out_of_map():
	test_map.size3d = Vector3 (2, 2, 2)
	var inner_pos = IsometricPositionable.new()
	inner_pos.position3d = Vector3(2, 0, 0)
	test_map.add_iso_positionable(inner_pos)
	assert_eq(test_map.get_children().size(), 0, "Should not find any positionable as child in map.")
	inner_pos.position3d = Vector3(0, 2, 0)
	test_map.add_iso_positionable(inner_pos)
	assert_eq(test_map.get_children().size(), 0, "Should not find any positionable as child in map.")
	inner_pos.position3d = Vector3(0, 0, 2)
	test_map.add_iso_positionable(inner_pos)
	assert_eq(test_map.get_children().size(), 0, "Should not find any positionable as child in map.")
	inner_pos.queue_free()

func test_should_not_add_overlapping_iso_positionable():
	test_map.size3d = Vector3(10, 10, 10)
	var inner_pos = IsometricPositionable.new()
	inner_pos.size3d = Vector3(5, 5, 5)
	inner_pos.position3d = Vector3(1, 1, 2)
	test_map.add_iso_positionable(inner_pos)
	var overlapping_pos = IsometricPositionable.new()
	overlapping_pos.position3d = Vector3(2, 2, 2)
	test_map.add_iso_positionable(overlapping_pos)
	assert_eq(overlapping_pos.get_parent(), null, "Overlapping map should not have parent")
	overlapping_pos.queue_free()
	inner_pos.queue_free()

func test_assert_topological_graph():
	test_map.size3d = Vector3(10, 10, 10)
	var first_pos = IsometricPositionable.new()
	first_pos.size3d = Vector3(5, 5, 5)
	first_pos.position3d = Vector3(0, 0, 0)
	var second_pos = IsometricPositionable.new()
	second_pos.position3d = Vector3(0, 5, 0)
	var third_pos = IsometricPositionable.new()
	third_pos.position3d = Vector3(1, 5, 0)
	var forth_pos = IsometricPositionable.new()
	forth_pos.position3d = Vector3(1, 5, 1)
	first_pos._enter_tree()
	second_pos._enter_tree()
	third_pos._enter_tree()
	forth_pos._enter_tree()
	test_map.add_iso_positionable(first_pos)
	test_map.add_iso_positionable(second_pos)
	test_map.add_iso_positionable(third_pos)
	test_map.add_iso_positionable(forth_pos)
	test_map._process()
	assert_eq(first_pos.z_index, 0, "z_index should be 0.")
	assert_eq(second_pos.z_index, 2, "z_index should be 2.")
	assert_eq(third_pos.z_index, 4, "z_index should be 4.")
	assert_eq(forth_pos.z_index, 6, "z_index should be 6.")
