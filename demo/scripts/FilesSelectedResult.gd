extends VBoxContainer


func show_result(result: PoolStringArray):
	for child in get_children():
		if child is LineEdit:
			child.free()

	for file in result:
		var line_edit = LineEdit.new()

		line_edit.editable = false
		line_edit.size_flags_horizontal = SIZE_EXPAND_FILL
		line_edit.text = file

		add_child(line_edit)
