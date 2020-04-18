extends LineEdit

class_name NumericLineEdit

var regex = RegEx.new()
var oldtext = ""

func _ready():
	self.connect("text_changed", self, "_on_LineEdit_text_changed")
	regex.compile("^[0-9]*$")

func _on_LineEdit_text_changed(new_text):
	if regex.search(new_text):
		text = new_text
		oldtext = text
	else:
		text = oldtext
	set_cursor_position(text.length())

func get_value():
	return(int(text))