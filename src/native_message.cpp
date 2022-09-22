#include "native_message.h"

using namespace godot;

void NativeMessage::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_title"), &NativeMessage::set_title);
    ClassDB::bind_method(D_METHOD("get_title"), &NativeMessage::get_title);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");

    ClassDB::bind_method("set_text", &NativeMessage::set_text);
    ClassDB::bind_method("get_text", &NativeMessage::get_text);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text"), "set_text", "get_text");

    ClassDB::bind_method("set_icon", &NativeMessage::set_icon);
    ClassDB::bind_method("get_icon", &NativeMessage::get_icon);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::INT,
			"icon",
			PROPERTY_HINT_ENUM,
			"Info,Warning,Error,Question"
		),
		"set_icon",
		"get_icon"
	);

    ClassDB::bind_method("set_choice", &NativeMessage::set_choice);
    ClassDB::bind_method("get_choice", &NativeMessage::get_choice);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::INT,
			"choice",
			PROPERTY_HINT_ENUM,
			"Ok,Ok Cancel,Yes No,Yes No Cancel"
		),
		"set_choice",
		"get_choice"
	);

    ClassDB::bind_method("show", &NativeMessage::show);
    ClassDB::bind_method("hide", &NativeMessage::hide);

	ADD_SIGNAL(
		MethodInfo(
			"result_selected",
			PropertyInfo(
				Variant::INT,
				"result",
				PROPERTY_HINT_ENUM,
				"Ok,Cancel,Yes,No"
			)
		)
	);

	BIND_ENUM_CONSTANT(CHOICE_OK);
    BIND_ENUM_CONSTANT(CHOICE_OK_CANCEL);
    BIND_ENUM_CONSTANT(CHOICE_YES_NO);
    BIND_ENUM_CONSTANT(CHOICE_YES_NO_CANCEL);

	BIND_ENUM_CONSTANT(ICON_INFO);
    BIND_ENUM_CONSTANT(ICON_WARNING);
    BIND_ENUM_CONSTANT(ICON_ERROR);
    BIND_ENUM_CONSTANT(ICON_QUESTION);

	BIND_ENUM_CONSTANT(RESULT_OK);
    BIND_ENUM_CONSTANT(RESULT_CANCEL);
    BIND_ENUM_CONSTANT(RESULT_YES);
    BIND_ENUM_CONSTANT(RESULT_NO);
}

NativeMessage::NativeMessage() {
	title = "";
	text = "";
	choice = pfd::choice::ok_cancel;
	icon = pfd::icon::info;
}

NativeMessage::~NativeMessage() {
	hide();
}

void NativeMessage::_process(float delta) {
	if(!message || !message->ready(0)) return;

	Result result;
	switch(message->result()){
		case pfd::button::cancel:
			result = RESULT_CANCEL;
			break;
		case pfd::button::yes:
			result = RESULT_YES;
			break;
		case pfd::button::no:
			result = RESULT_NO;
			break;
		default:
			result = RESULT_OK;
	}

	emit_signal("result_selected", result);

	hide();
}

void NativeMessage::_exit_tree() {
	hide();
}

void NativeMessage::show() {
	ERR_FAIL_COND(!is_inside_tree());
	ERR_FAIL_COND(!is_processing());

	hide();

	message = new pfd::message(title.utf8().get_data(), text.utf8().get_data(), choice, icon);
}

void NativeMessage::hide() {
	if(!message) return;

	message->kill();

	delete message;

	message = nullptr;
}

void NativeMessage::set_title(const String &p_title) {
	title = p_title;
}

String NativeMessage::get_title() {
	return title;
}

void NativeMessage::set_text(const String &p_text) {
	text = p_text;
}

String NativeMessage::get_text() {
	return text;
}

void NativeMessage::set_choice(Choice p_choice) {
	ERR_FAIL_INDEX(p_choice, 4);

	switch(p_choice){
		case CHOICE_OK_CANCEL:
			choice = pfd::choice::ok_cancel;
			break;
		case CHOICE_YES_NO:
			choice = pfd::choice::yes_no;
			break;
		case CHOICE_YES_NO_CANCEL:
			choice = pfd::choice::yes_no_cancel;
			break;
		default:
			choice = pfd::choice::ok;
	}
}

NativeMessage::Choice NativeMessage::get_choice() {
	switch(choice){
		case pfd::choice::ok_cancel:
			return CHOICE_OK_CANCEL;
		case pfd::choice::yes_no:
			return CHOICE_YES_NO;
		case pfd::choice::yes_no_cancel:
			return CHOICE_YES_NO_CANCEL;
		default:
			return CHOICE_OK;
	}
}

void NativeMessage::set_icon(Icon p_icon) {
	ERR_FAIL_INDEX(p_icon, 4);

	switch(p_icon){
		case ICON_WARNING:
			icon = pfd::icon::warning;
			break;
		case ICON_ERROR:
			icon = pfd::icon::error;
			break;
		case ICON_QUESTION:
			icon = pfd::icon::question;
			break;
		default:
			icon = pfd::icon::info;
	}
}

NativeMessage::Icon NativeMessage::get_icon() {
	switch(icon){
		case pfd::icon::warning:
			return ICON_WARNING;
		case pfd::icon::error:
			return ICON_ERROR;
		case pfd::icon::question:
			return ICON_QUESTION;
		default:
			return ICON_INFO;
	}
}
