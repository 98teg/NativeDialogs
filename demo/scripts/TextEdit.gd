tool
extends TextEdit


signal text_modified(text)


func emit_text():
	emit_signal("text_modified", text)
