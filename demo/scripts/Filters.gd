extends VBoxContainer


@export var native_dialog_path: NodePath

@onready var native_dialog = get_node(native_dialog_path)
@onready var name_line_edit = get_node("HBoxContainer/NameLineEdit")
@onready var extensions_line_edit = get_node("HBoxContainer/ExtensionsLineEdit")


func _ready():
	show_filters()


func show_filters():
	var filters = native_dialog.get_filters()

	for child in get_children():
		if child is LineEdit:
			child.free()

	for filter in filters:
		var line_edit = LineEdit.new()

		line_edit.editable = false
		line_edit.size_flags_horizontal = SIZE_EXPAND_FILL
		line_edit.text = filter

		add_child(line_edit)


func add_filter():
	var name = name_line_edit.text
	name_line_edit.text = ""

	var extensions = extensions_line_edit.text
	extensions_line_edit.text = ""

	native_dialog.add_filter(extensions + " ; " + name)

	show_filters()


func clear_filters():
	native_dialog.clear_filters()

	show_filters()
