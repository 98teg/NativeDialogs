#include <godot_cpp/classes/translation_server.hpp>

#include "native_accept_dialog.h"

using namespace godot;

void NativeAcceptDialog::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_title"), &NativeAcceptDialog::set_title);
    ClassDB::bind_method(D_METHOD("get_title"), &NativeAcceptDialog::get_title);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");

	ADD_GROUP("Dialog", "dialog");
    ClassDB::bind_method("set_text", &NativeAcceptDialog::set_text);
    ClassDB::bind_method("get_text", &NativeAcceptDialog::get_text);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::STRING,
			"dialog_text",
			PROPERTY_HINT_MULTILINE_TEXT,
			""
		),
		"set_text",
		"get_text"
	);

    ClassDB::bind_method("set_icon", &NativeAcceptDialog::set_icon);
    ClassDB::bind_method("get_icon", &NativeAcceptDialog::get_icon);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::INT,
			"dialog_icon",
			PROPERTY_HINT_ENUM,
			"Info,Warning,Error,Question"
		),
		"set_icon",
		"get_icon"
	);

    ClassDB::bind_method("show", &NativeAcceptDialog::show);
    ClassDB::bind_method("hide", &NativeAcceptDialog::hide);

	ADD_SIGNAL(MethodInfo("confirmed"));
	ADD_SIGNAL(MethodInfo("cancelled"));

	BIND_ENUM_CONSTANT(ICON_INFO);
    BIND_ENUM_CONSTANT(ICON_WARNING);
    BIND_ENUM_CONSTANT(ICON_ERROR);
    BIND_ENUM_CONSTANT(ICON_QUESTION);
}

NativeAcceptDialog::NativeAcceptDialog() {
	title = TranslationServer::get_singleton()->translate("Alert!");
	text = "";
	icon = ICON_WARNING;
}

NativeAcceptDialog::~NativeAcceptDialog() {
	hide();
}

void NativeAcceptDialog::_process(float delta) {
	if(!message || !message->ready(0)) return;

	switch(message->result()){
		case pfd::button::cancel:
			emit_signal("cancelled");
			break;
		default:
			emit_signal("confirmed");
	}

	hide();
}

void NativeAcceptDialog::_exit_tree() {
	hide();
}

void NativeAcceptDialog::show() {
	ERR_FAIL_COND(!is_inside_tree());
	ERR_FAIL_COND(!is_processing());

	hide();

	pfd::icon pfd_icon;

	switch(icon) {
		case ICON_INFO:
			pfd_icon = pfd::icon::info;
			break;
		case ICON_ERROR:
			pfd_icon = pfd::icon::error;
			break;
		case ICON_QUESTION:
			pfd_icon = pfd::icon::question;
			break;
		default:
			pfd_icon = pfd::icon::warning;
	}

	message = new pfd::message(
		title.utf8().get_data(),
		text.utf8().get_data(),
		pfd::choice::ok,
		pfd_icon
	);
}

void NativeAcceptDialog::hide() {
	if(!message) return;

	message->kill();

	delete message;

	message = nullptr;
}

void NativeAcceptDialog::set_title(const String &p_title) {
	title = p_title;
}

String NativeAcceptDialog::get_title() {
	return title;
}

void NativeAcceptDialog::set_text(const String &p_text) {
	text = p_text;
}

String NativeAcceptDialog::get_text() {
	return text;
}

void NativeAcceptDialog::set_icon(Icon p_icon) {
	ERR_FAIL_INDEX(p_icon, 4);

	icon = p_icon;
}

NativeAcceptDialog::Icon NativeAcceptDialog::get_icon() {
	return icon;
}
