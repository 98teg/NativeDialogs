extends PanelContainer


@onready var native_file_dialog: NativeFileDialog = %_NativeFileDialog
@onready var title: LineEdit = %_Title
@onready var overrides: CheckButton = %_Overrides
@onready var filter: LineEdit = %_Filter
@onready var description: LineEdit = %_Description
@onready var filters: VBoxContainer = %_Filters
@onready var result: LineEdit = %_Result


func select_file_mode(file_mode):
	native_file_dialog.file_mode = file_mode

	override_title()


func override_title():
	native_file_dialog.mode_overrides_title = overrides.button_pressed

	if native_file_dialog.mode_overrides_title:
		title.editable = false
		title.text = native_file_dialog.title
	else:
		title.editable = true


func add_filter():
	native_file_dialog.add_filter(filter.text, description.text)

	filter.text = ""
	description.text = ""

	update_filters()


func clear_filters():
	native_file_dialog.clear_filters()

	update_filters()


func update_filters():
	for child in filters.get_children():
		child.queue_free()

	for filter in native_file_dialog.filters:
		var label = Label.new()
		label.text = filter

		filters.add_child(label)


func file_selected(paths: String):
	files_selected([paths])


func files_selected(paths: Array[String]):
	result.text = paths.reduce(
		func(paths, path): return path if paths == "" else paths + ", " + path, ""
	)


func dialog_closed():
	result.text = ""
