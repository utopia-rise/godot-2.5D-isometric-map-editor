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
	var inner_map = IsometricMap.new()
	inner_map.size3d = Vector3(5, 5, 5)
	inner_map.position3d = Vector3(1, 1, 2)
	test_map.add_iso_positionable(inner_map)
	assert_eq(inner_map.get_parent(), test_map, "Should have added as child iso map.")
	assert_eq(test_map.get_positionable_at(inner_map.position3d), inner_map, "inner_map should be found at " + str(inner_map.position3d))
	assert_eq(test_map.get_positionable_at(Vector3(2, 2, 2), false), inner_map, "inner_map should be found at " + str(Vector3(2, 2, 2)))
	var overlap_map = IsometricMap.new()
	overlap_map.position3d = Vector3(0, 0, 2)
	overlap_map.size3d = Vector3(5, 5, 1)
	assert_true(test_map.is_overlapping(overlap_map), "Should overlap.")
	test_map.remove_iso_positionable(inner_map, "Should have remove isomap as child.")
	assert_eq(inner_map.get_parent(), null)
	inner_map.queue_free()

func test_should_not_add_iso_positionable_out_of_map():
	test_map.size3d = Vector3 (2, 2, 2)
	var inner_map = IsometricMap.new()
	inner_map.position3d = Vector3(2, 0, 0)
	test_map.add_iso_positionable(inner_map)
	assert_eq(test_map.get_children().size(), 0, "Should not find any positionable as child in map.")
	inner_map.position3d = Vector3(0, 2, 0)
	test_map.add_iso_positionable(inner_map)
	assert_eq(test_map.get_children().size(), 0, "Should not find any positionable as child in map.")
	inner_map.position3d = Vector3(0, 0, 2)
	test_map.add_iso_positionable(inner_map)
	assert_eq(test_map.get_children().size(), 0, "Should not find any positionable as child in map.")
	inner_map.queue_free()

func test_should_not_add_overlapping_iso_positionable():
	test_map.size3d = Vector3(10, 10, 10)
	var inner_map = IsometricMap.new()
	inner_map.size3d = Vector3(5, 5, 5)
	inner_map.position3d = Vector3(1, 1, 2)
	test_map.add_iso_positionable(inner_map)
	var overlapping_map = IsometricMap.new()
	overlapping_map.position3d = Vector3(2, 2, 2)
	test_map.add_iso_positionable(overlapping_map)
	assert_eq(overlapping_map.get_parent(), null, "Overlapping map should not have parent")
	overlapping_map.queue_free()
	inner_map.queue_free()
