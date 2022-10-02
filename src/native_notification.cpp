#include <godot_cpp/classes/translation_server.hpp>

#include "native_notification.h"

using namespace godot;

void NativeNotification::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_title"), &NativeNotification::set_title);
    ClassDB::bind_method(D_METHOD("get_title"), &NativeNotification::get_title);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");

	ADD_GROUP("Notification", "notification");
    ClassDB::bind_method("set_text", &NativeNotification::set_text);
    ClassDB::bind_method("get_text", &NativeNotification::get_text);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::STRING,
			"notification_text",
			PROPERTY_HINT_MULTILINE_TEXT,
			""
		),
		"set_text",
		"get_text"
	);

    ClassDB::bind_method("set_icon", &NativeNotification::set_icon);
    ClassDB::bind_method("get_icon", &NativeNotification::get_icon);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::INT,
			"notification_icon",
			PROPERTY_HINT_ENUM,
			"INFO,WARNING,ERROR"
		),
		"set_icon",
		"get_icon"
	);

    ClassDB::bind_method("send", &NativeNotification::send);

	BIND_ENUM_CONSTANT(ICON_INFO);
    BIND_ENUM_CONSTANT(ICON_WARNING);
    BIND_ENUM_CONSTANT(ICON_ERROR);
}

NativeNotification::NativeNotification() {
	title = TranslationServer::get_singleton()->translate("Alert!");
	text = "";
	icon = ICON_WARNING;
}

void NativeNotification::send() {
	pfd::icon pfd_icon;

	switch(icon) {
		case ICON_INFO:
			pfd_icon = pfd::icon::info;
			break;
		case ICON_WARNING:
			pfd_icon = pfd::icon::warning;
			break;
		case ICON_ERROR:
			pfd_icon = pfd::icon::error;
			break;
	}

	pfd::notify(title.utf8().get_data(), text.utf8().get_data(), pfd_icon);
}

void NativeNotification::set_title(const String &p_title) {
	title = p_title;
}

String NativeNotification::get_title() {
	return title;
}

void NativeNotification::set_text(const String &p_text) {
	text = p_text;
}

String NativeNotification::get_text() {
	return text;
}

void NativeNotification::set_icon(Icon p_icon) {
	ERR_FAIL_INDEX(p_icon, 3);

	icon = p_icon;
}

NativeNotification::Icon NativeNotification::get_icon() {
	return icon;
}
