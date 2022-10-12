extends PanelContainer


@onready var native_file_dialog: NativeFileDialog = $NativeFileDialog
@onready var title_line_edit: LineEdit = $HBoxContainer/VBoxContainer/FirstRow/Title/LineEdit
@onready var overrides_check_button: CheckButton = $HBoxContainer/VBoxContainer/FirstRow/ModeOverridesTitle/CheckButton
@onready var file_mode_option_button: OptionButton = $HBoxContainer/VBoxContainer/SecondRow/FileMode/OptionButton
@onready var filter_line_edit: LineEdit = $HBoxContainer/VBoxContainer/Filters/HBoxContainer/Filter/LineEdit
@onready var description_line_edit: LineEdit = $HBoxContainer/VBoxContainer/Filters/HBoxContainer/Description/LineEdit
@onready var filters_list: VBoxContainer = $HBoxContainer/VBoxContainer/Filters/ScrollContainer/PanelContainer/VBoxContainer


func select_file_mode(file_mode):
	native_file_dialog.file_mode = file_mode_option_button.get_selected_id()

	override_title()


func override_title():
	native_file_dialog.mode_overrides_title = overrides_check_button.button_pressed

	if (native_file_dialog.mode_overrides_title):
		title_line_edit.editable = false
		title_line_edit.text = native_file_dialog.title
	else:
		title_line_edit.editable = true


func add_filter():
	native_file_dialog.add_filter(filter_line_edit.text, description_line_edit.text)

	filter_line_edit.text = ""
	description_line_edit.text = ""

	update_filters()


func clear_filters():
	native_file_dialog.clear_filters()

	update_filters()


func update_filters():
	for child in filters_list.get_children():
		child.queue_free()

	for filter in native_file_dialog.filters:
		var label = Label.new()
		label.text = filter

		filters_list.add_child(label)
