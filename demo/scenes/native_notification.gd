extends PanelContainer


@onready var native_notification: NativeNotification = %_NativeNotification
@onready var text: TextEdit = %_Text


func text_changed():
	native_notification.set_text(text.text)
