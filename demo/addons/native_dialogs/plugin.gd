tool
extends EditorPlugin


func _enter_tree():
	add_custom_type(
		"NativeDialogMessage",
		"Node",
		preload("./bin/native_dialog_message.gdns"),
		preload("./icons/native_dialog_message.png")
	)

	add_custom_type(
		"NativeDialogNotify",
		"Node",
		preload("./bin/native_dialog_notify.gdns"),
		preload("./icons/native_dialog_notify.png")
	)

	add_custom_type(
		"NativeDialogOpenFile",
		"Node",
		preload("./bin/native_dialog_open_file.gdns"),
		preload("./icons/native_dialog_open_file.png")
	)

	add_custom_type(
		"NativeDialogSaveFile",
		"Node",
		preload("./bin/native_dialog_save_file.gdns"),
		preload("./icons/native_dialog_save_file.png")
	)

	add_custom_type(
		"NativeDialogSelectFolder",
		"Node",
		preload("./bin/native_dialog_select_folder.gdns"),
		preload("./icons/native_dialog_select_folder.png")
	)


func _exit_tree():
	remove_custom_type("NativeDialogMessage")
	remove_custom_type("NativeDialogNotify")
	remove_custom_type("NativeDialogOpenFile")
	remove_custom_type("NativeDialogSaveFile")
	remove_custom_type("NativeDialogSelectFolder")
