#ifndef NATIVEMESSAGE_H
#define NATIVEMESSAGE_H

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>

#include <portable-file-dialogs.h>

namespace godot {

class NativeMessage : public Node {
	GDCLASS(NativeMessage, Node)

protected:
	static void _bind_methods();

private:
	String title;
	String text;
	pfd::choice choice;
	pfd::icon icon;

	pfd::message* message;

public:
	enum Choice {
		CHOICE_OK,
		CHOICE_OK_CANCEL,
		CHOICE_YES_NO,
		CHOICE_YES_NO_CANCEL
	};

	enum Icon {
		ICON_INFO,
		ICON_WARNING,
		ICON_ERROR,
		ICON_QUESTION
	};

	enum Result {
		RESULT_OK,
		RESULT_CANCEL,
		RESULT_YES,
		RESULT_NO
	};

	NativeMessage();
	~NativeMessage();

	void _process(float delta);
	void _exit_tree();

	void show();
	void hide();

	void set_title(const String &p_title);
	String get_title();

	void set_text(const String &p_text);
	String get_text();

	void set_choice(Choice p_choice);
	Choice get_choice();

	void set_icon(Icon p_icon);
	Icon get_icon();
};

}

VARIANT_ENUM_CAST(NativeMessage, Choice);
VARIANT_ENUM_CAST(NativeMessage, Icon);
VARIANT_ENUM_CAST(NativeMessage, Result);

#endif // NATIVEMESSAGE_H
