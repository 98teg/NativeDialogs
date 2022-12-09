#ifndef NATIVECONFIRMATIONDIALOG_H
#define NATIVECONFIRMATIONDIALOG_H

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <portable-file-dialogs.h>

#include "native_accept_dialog.h"

namespace godot {

class NativeConfirmationDialog : public NativeAcceptDialog {
	GDCLASS(NativeConfirmationDialog, NativeAcceptDialog)

protected:
	static void _bind_methods();

public:
	enum ButtonsTexts {
		BUTTONS_TEXTS_OK_CANCEL,
		BUTTONS_TEXTS_YES_NO
	};

private:
	ButtonsTexts buttons_texts;

public:
	NativeConfirmationDialog();

	void _process(float delta);
	void _exit_tree();

	void set_buttons_texts(ButtonsTexts p_texts);
	ButtonsTexts get_buttons_texts();
};

} // namespace godot

VARIANT_ENUM_CAST(NativeConfirmationDialog, ButtonsTexts);

#endif // NATIVECONFIRMATIONDIALOG_H
