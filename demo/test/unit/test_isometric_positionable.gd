extends "res://addons/gut/test.gd"

var test_positionable: IsometricMap

func before_each():
	test_positionable = IsometricMap.new()

func after_all():
	test_positionable.queue_free()

func test_assert_get_hexagone_coordinates():
	var expected := Transform2D(Vector2(-1.21875, 1), Vector2(-1.21875, 1), Vector2(-1, 1))
	assert_eq(test_positionable.get_hexagone_coordinates(), expected, "Hexagone cooredinates should be " + str(expected) + ".")
