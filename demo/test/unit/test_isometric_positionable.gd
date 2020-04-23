extends "res://addons/gut/test.gd"

var test_positionable: IsometricPositionable

func before_each():
	test_positionable = IsometricPositionable.new()

func after_all():
	test_positionable.queue_free()

func test_assert_set_position():
	var expected_value = Vector3(3.0, 2.0, 2.0)
	var expected_iso_position = Vector2(128, 320)
	test_positionable.position3d = expected_value
	assert_eq(test_positionable.position3d, expected_value, "Position should be " + str(expected_value) + ".")
	assert_eq(test_positionable.iso_position, expected_iso_position, "iso_position should be " + str(128, 320) + ".")

func test_assert_hexagone_coordinates():
	var expected := Transform2D(Vector2(-1.21875, 1), Vector2(-1.21875, 1), Vector2(-1, 1))
	assert_eq(test_positionable.get_hexagone_coordinates(), expected, "Hexagone cooredinates should be " + str(expected) + ".")
