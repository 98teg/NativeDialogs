extends PanelContainer


@onready var native_accept_dialog: NativeAcceptDialog = $NativeAcceptDialog
@onready var text_edit: TextEdit = $HBoxContainer/VBoxContainer/Text/TextEdit
@onready var result: LineEdit = $HBoxContainer/VBoxContainer/Result/LineEdit


func text_changed():
	native_accept_dialog.set_text(text_edit.text)


func set_confirmed():
	result.text = "Confirmed"


func set_cancelled():
	result.text = "Cancelled"
