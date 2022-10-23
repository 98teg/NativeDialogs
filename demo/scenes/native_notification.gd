extends PanelContainer


@onready var native_notification: NativeNotification = $NativeNotification
@onready var text_edit: TextEdit = $MarginContainer/VBoxContainer/VBoxContainer/Text/TextEdit


func text_changed():
	native_notification.set_text(text_edit.text)
