extends "res://addons/gut/test.gd"

var placeholder = IsometricPlaceholder.new()
var test_type = load("res://addons/IsometricMap/prefab/types/character.tres")

func test_should_change_placeholder_type():
	placeholder.placeholder_type = test_type
	assert_eq(placeholder.placeholder_type.type_name, "Character", "Type should be Character")
	assert_ne(placeholder.placeholder_type.color, Color(0.83, 0.83, 0.83, 1), "Color should be default value")
