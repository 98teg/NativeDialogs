#include "native_dialog_message.h"

using namespace godot;

void NativeDialogMessage::_register_methods() {
	register_property<NativeDialogMessage, String>("title", &NativeDialogMessage::title, "");
	register_property<NativeDialogMessage, String>("text", &NativeDialogMessage::text, "");
	register_property<NativeDialogMessage, int>(
        "choice",
        &NativeDialogMessage::set_choice,
        &NativeDialogMessage::get_choice,
        (int) pfd::choice::ok_cancel,
		GODOT_METHOD_RPC_MODE_DISABLED,
		GODOT_PROPERTY_USAGE_DEFAULT,
		GODOT_PROPERTY_HINT_ENUM,
		"OK,OK_CANCEL,YES_NO,YES_NO_CANCEL"
	);
	register_property<NativeDialogMessage, int>(
        "icon",
        &NativeDialogMessage::set_icon,
        &NativeDialogMessage::get_icon,
        (int) pfd::icon::info,
		GODOT_METHOD_RPC_MODE_DISABLED,
		GODOT_PROPERTY_USAGE_DEFAULT,
		GODOT_PROPERTY_HINT_ENUM,
		"INFO,WARNING,ERROR,QUESTION"
	);

    register_method("_process", &NativeDialogMessage::_process);
    register_method("_exit_tree", &NativeDialogMessage::_exit_tree);

    register_method("show", &NativeDialogMessage::show);
    register_method("hide", &NativeDialogMessage::hide);

    register_method("set_title", &NativeDialogMessage::set_title);
    register_method("get_title", &NativeDialogMessage::get_title);
    register_method("set_text", &NativeDialogMessage::set_text);
    register_method("get_text", &NativeDialogMessage::get_text);
    register_method("set_choice", &NativeDialogMessage::set_choice);
    register_method("get_choice", &NativeDialogMessage::get_choice);
    register_method("set_icon", &NativeDialogMessage::set_icon);
    register_method("get_icon", &NativeDialogMessage::get_icon);

	register_signal<NativeDialogMessage>(
		(char *)"result_selected",
		"result",
		GODOT_VARIANT_TYPE_INT
	);
}

NativeDialogMessage::NativeDialogMessage() {
}

NativeDialogMessage::~NativeDialogMessage() {
	hide();
}

void NativeDialogMessage::_init() {
	title = "";
	text = "";
	choice = pfd::choice::ok_cancel;
	icon = pfd::icon::info;

	message = NULL;
}

void NativeDialogMessage::_process(float delta) {
	if(!message || !message->ready(0)) return;

	int result;
	switch(message->result()){
		case pfd::button::ok:
			result = 0;
			break;
		case pfd::button::cancel:
			result = 1;
			break;
		case pfd::button::yes:
			result = 2;
			break;
		case pfd::button::no:
			result = 3;
			break;
	}

	emit_signal("result_selected", result);

	hide();
}

void NativeDialogMessage::_exit_tree() {
	hide();
}

void NativeDialogMessage::show() {
	ERR_FAIL_COND(!is_inside_tree());
	ERR_FAIL_COND(!is_processing());

	hide();

	message = new pfd::message(title.alloc_c_string(), text.alloc_c_string(), choice, icon);
}

void NativeDialogMessage::hide() {
	if(!message) return;

	message->kill();

	delete message;

	message = NULL;
}

void NativeDialogMessage::set_title(String p_title) {
	title = p_title;
}

String NativeDialogMessage::get_title() {
	return title;
}

void NativeDialogMessage::set_text(String p_text) {
	text = p_text;
}

String NativeDialogMessage::get_text() {
	return text;
}

void NativeDialogMessage::set_choice(int p_choice) {
	switch(p_choice){
		case 0:
			choice = pfd::choice::ok;
			break;
		case 1:
			choice = pfd::choice::ok_cancel;
			break;
		case 2:
			choice = pfd::choice::yes_no;
			break;
		case 3:
			choice = pfd::choice::yes_no_cancel;
			break;
	}
}

int NativeDialogMessage::get_choice() {
	switch(choice){
		case pfd::choice::ok:
			return 0;
		case pfd::choice::ok_cancel:
			return 1;
		case pfd::choice::yes_no:
			return 2;
		case pfd::choice::yes_no_cancel:
			return 3;
	}

	return -1;
}

void NativeDialogMessage::set_icon(int p_icon) {
	switch(p_icon){
		case 0:
			icon = pfd::icon::info;
			break;
		case 1:
			icon = pfd::icon::warning;
			break;
		case 2:
			icon = pfd::icon::error;
			break;
		case 3:
			icon = pfd::icon::question;
			break;
	}
}

int NativeDialogMessage::get_icon() {
	switch(icon){
		case pfd::icon::info:
			return 0;
		case pfd::icon::warning:
			return 1;
		case pfd::icon::error:
			return 2;
		case pfd::icon::question:
			return 3;
	}

	return -1;
}
