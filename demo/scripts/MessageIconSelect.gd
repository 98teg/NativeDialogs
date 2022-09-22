@tool
extends OptionButton


func _ready():
	clear()

	add_item("INFO", 0)
	add_item("WARNING", 1)
	add_item("ERROR", 2)
	add_item("QUESTION", 3)
