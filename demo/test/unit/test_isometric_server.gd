extends "res://addons/gut/test.gd"

func after_each():
	IsometricServer.tile_width = 256
	IsometricServer.tile_height = 128
	IsometricServer.angle = 30

func test_should_change_tile_width():
	var expected_tile_width = 2560
	var expected_tile_height = 128
	var expected_angle = 30
	IsometricServer.tile_width = expected_tile_width
	assert_eq(IsometricServer.tile_width, expected_tile_width, "Tile width should be " + str(expected_tile_width) + ".")
	assert_eq(IsometricServer.tile_height, expected_tile_height, "Tile height should be " + str(expected_tile_height) + ".")
	assert_eq(IsometricServer.angle, expected_angle, "Tile width should be " + str(expected_angle) + ".")

func test_should_change_tile_height():
	var expected_tile_width = 256
	var expected_tile_height = 1280
	var expected_angle = 30
	IsometricServer.tile_height = expected_tile_height
	assert_eq(IsometricServer.tile_width, expected_tile_width, "Tile width should be " + str(expected_tile_width) + ".")
	assert_eq(IsometricServer.tile_height, expected_tile_height, "Tile height should be " + str(expected_tile_height) + ".")
	assert_eq(IsometricServer.angle, expected_angle, "Tile width should be " + str(expected_angle) + ".")

func test_should_change_angle():
	var expected_tile_width = 256
	var expected_tile_height = 128
	var expected_angle = 300
	IsometricServer.angle = expected_angle
	assert_eq(IsometricServer.tile_width, expected_tile_width, "Tile width should be " + str(expected_tile_width) + ".")
	assert_eq(IsometricServer.tile_height, expected_tile_height, "Tile height should be " + str(expected_tile_height) + ".")
	assert_eq(IsometricServer.angle, expected_angle, "Tile width should be " + str(expected_angle) + ".")
