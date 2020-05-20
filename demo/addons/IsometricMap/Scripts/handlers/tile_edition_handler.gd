extends EditionHandler

class_name TileEditionHandler

var undo_redo: UndoRedo
var tile: IsometricTile

func _init(tile: IsometricTile, undo_redo: UndoRedo):
	self.undo_redo = undo_redo
	self.tile = tile
	tile.set_outline_drawer(Color(0, 0, 0, 1), 1.0)
