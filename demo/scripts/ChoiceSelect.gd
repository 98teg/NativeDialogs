tool
extends OptionButton


func _ready():
	clear()

	add_item("OK", 0)
	add_item("OK_CANCEL", 1)
	add_item("YES_NO", 2)
	add_item("YES_NO_CANCEL", 3)

	selected = 1
