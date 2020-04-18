tool
extends IsoPositionable
class_name IsoTile

# Do we draw tile lines
export (bool) var outline: bool = true setget set_outline

func set_outline(b: bool):
	outline = b
	update()
