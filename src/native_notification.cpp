#include "native_notification.h"

using namespace godot;

void NativeNotification::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_title"), &NativeNotification::set_title);
    ClassDB::bind_method(D_METHOD("get_title"), &NativeNotification::get_title);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");

    ClassDB::bind_method("set_text", &NativeNotification::set_text);
    ClassDB::bind_method("get_text", &NativeNotification::get_text);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text"), "set_text", "get_text");

    ClassDB::bind_method("set_icon", &NativeNotification::set_icon);
    ClassDB::bind_method("get_icon", &NativeNotification::get_icon);
	ADD_PROPERTY(
		PropertyInfo(Variant::INT, "icon", PROPERTY_HINT_ENUM, "INFO,WARNING,ERROR"),
		"set_icon",
		"get_icon"
	);

    ClassDB::bind_method("send", &NativeNotification::send);

	BIND_ENUM_CONSTANT(ICON_INFO);
    BIND_ENUM_CONSTANT(ICON_WARNING);
    BIND_ENUM_CONSTANT(ICON_ERROR);
}

NativeNotification::NativeNotification() {
	title = "";
	text = "";
	icon = pfd::icon::info;
}

void NativeNotification::send() {
	pfd::notify(title.utf8().get_data(), text.utf8().get_data(), icon);
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

	switch(p_icon){
		case ICON_WARNING:
			icon = pfd::icon::warning;
			break;
		case ICON_ERROR:
			icon = pfd::icon::error;
			break;
		default:
			icon = pfd::icon::info;
	}
}

NativeNotification::Icon NativeNotification::get_icon() {
	switch(icon){
		case pfd::icon::warning:
			return ICON_WARNING;
		case pfd::icon::error:
			return ICON_ERROR;
		default:
			return ICON_INFO;
	}
}
