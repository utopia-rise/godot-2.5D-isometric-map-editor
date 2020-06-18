extends EditionHandler

class_name ElementEditionHandler

var undo_redo: UndoRedo
var element

func _init(element, undo_redo: UndoRedo):
	self.undo_redo = undo_redo
	self.element = element
	element.set_outline_drawer(Color(0, 0, 0, 1), 1.0)
