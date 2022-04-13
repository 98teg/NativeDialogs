extends LineEdit


enum results {OK, CANCEL, YES, NO}


func set_result(result: int):
	match(result):
		results.OK:
			text = "OK"
		results.CANCEL:
			text = "CANCEL"
		results.YES:
			text = "YES"
		results.NO:
			text = "NO"
