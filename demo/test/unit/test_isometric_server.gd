extends "res://addons/gut/test.gd"

func after_each():
	IsoServer.tile_width = 256
	IsoServer.tile_height = 128
	IsoServer.angle = 30

func test_should_change_tile_width():
	var expected_tile_width = 2560
	var expected_tile_height = 1280
	var expected_angle = 30
	IsoServer.tile_width = expected_tile_width
	assert_eq(IsoServer.tile_width, expected_tile_width, "Tile width should be " + str(expected_tile_width) + ".")
	assert_eq(IsoServer.tile_height, expected_tile_height, "Tile height should be " + str(expected_tile_height) + ".")
	assert_eq(IsoServer.angle, expected_angle, "Tile width should be " + str(expected_angle) + ".")

func test_should_not_change_tile_height():
	var expected_tile_width = 256
	var expected_tile_height = 128
	var expected_angle = 30
	IsoServer.tile_height = 456651
	assert_eq(IsoServer.tile_width, expected_tile_width, "Tile width should be " + str(expected_tile_width) + ".")
	assert_eq(IsoServer.tile_height, expected_tile_height, "Tile height should be " + str(expected_tile_height) + ".")
	assert_eq(IsoServer.angle, expected_angle, "Tile width should be " + str(expected_angle) + ".")

func test_should_change_angle():
	var expected_tile_width = 256
	var expected_tile_height = 222
	var expected_angle = 60
	IsoServer.angle = expected_angle
	assert_eq(IsoServer.tile_width, expected_tile_width, "Tile width should be " + str(expected_tile_width) + ".")
	assert_eq(IsoServer.tile_height, expected_tile_height, "Tile height should be " + str(expected_tile_height) + ".")
	assert_eq(IsoServer.angle, expected_angle, "Tile width should be " + str(expected_angle) + ".")
	expected_tile_width = 256
	expected_tile_height = 256
	expected_angle = 90
	IsoServer.angle = expected_angle
	assert_eq(IsoServer.tile_width, expected_tile_width, "Tile width should be " + str(expected_tile_width) + ".")
	assert_eq(IsoServer.tile_height, expected_tile_height, "Tile height should be " + str(expected_tile_height) + ".")
	assert_eq(IsoServer.angle, expected_angle, "Tile width should be " + str(expected_angle) + ".")
