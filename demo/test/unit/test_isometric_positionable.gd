extends "res://addons/gut/test.gd"

var test_positionable: IsometricPositionable

func before_each():
	test_positionable = IsometricPositionable.new()

func after_all():
	test_positionable.queue_free()

func test_assert_set_position():
	var expected_value = Vector3(3.0, 2.0, 2.0)
	var expected_iso_position = (Vector2(128, 6.465302) * 1000).round()
	test_positionable.position3d = expected_value
	assert_eq(test_positionable.position3d, expected_value, "Position should be " + str(expected_value) + ".")
	assert_eq((test_positionable.iso_position * 1000).round(), expected_iso_position, "iso_position should be " + str(expected_iso_position) + ".")

func test_assert_hexagone_coordinates():
	var hexa_coord: Transform2D = test_positionable.get_hexagone_coordinates()
	var expected := Transform2D((Vector2(-1.2247450, 1) * 1000).round(), (Vector2(-1.2247450, 1) * 1000).round(), Vector2(-1, 1))
	var received := Transform2D((test_positionable.get_hexagone_coordinates().x * 1000).round(), (test_positionable.get_hexagone_coordinates().y * 1000).round(), test_positionable.get_hexagone_coordinates().get_origin())
	assert_eq(received, expected, "Hexagone cooredinates should be " + str(expected) + ".")
