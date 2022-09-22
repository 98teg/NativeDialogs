@tool
extends OptionButton


func _ready():
	clear()

	add_item("INFO", NativeDialogNotify.INFO)
	add_item("WARNING", NativeDialogNotify.WARNING)
	add_item("ERROR", NativeDialogNotify.ERROR)
