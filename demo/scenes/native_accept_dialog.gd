extends PanelContainer


@onready var native_accept_dialog: NativeAcceptDialog = %_NativeAcceptDialog
@onready var text: TextEdit = %_Text
@onready var result: LineEdit = %_Result


func text_changed():
	native_accept_dialog.set_text(text.text)


func set_confirmed():
	result.text = "Confirmed"


func set_canceled():
	result.text = "Canceled"
