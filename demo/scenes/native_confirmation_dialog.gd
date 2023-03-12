extends PanelContainer


@onready var native_confirmation_dialog: NativeConfirmationDialog = %_NativeConfirmationDialog
@onready var text: TextEdit = %_Text
@onready var result: LineEdit = %_Result


func text_changed():
	native_confirmation_dialog.set_text(text.text)


func set_confirmed():
	result.text = "Confirmed"


func set_canceled():
	result.text = "Canceled"
