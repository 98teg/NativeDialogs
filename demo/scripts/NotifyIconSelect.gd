@tool
extends OptionButton


func _ready():
	clear()

	add_item("INFO", NativeNotification.ICON_INFO)
	add_item("WARNING", NativeNotification.ICON_WARNING)
	add_item("ERROR", NativeNotification.ICON_ERROR)
