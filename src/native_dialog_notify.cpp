#include "native_dialog_notify.h"

using namespace godot;

void NativeDialogNotify::_register_methods() {
	register_property<NativeDialogNotify, String>("title", &NativeDialogNotify::title, "");
	register_property<NativeDialogNotify, String>("text", &NativeDialogNotify::text, "");
	register_property<NativeDialogNotify, int>(
        "icon",
        &NativeDialogNotify::set_icon,
        &NativeDialogNotify::get_icon,
        (int) pfd::icon::info,
		GODOT_METHOD_RPC_MODE_DISABLED,
		GODOT_PROPERTY_USAGE_DEFAULT,
		GODOT_PROPERTY_HINT_ENUM,
		"INFO,WARNING,ERROR"
	);

    register_method("send", &NativeDialogNotify::send);

    register_method("set_title", &NativeDialogNotify::set_title);
    register_method("get_title", &NativeDialogNotify::get_title);
    register_method("set_text", &NativeDialogNotify::set_text);
    register_method("get_text", &NativeDialogNotify::get_text);
    register_method("set_icon", &NativeDialogNotify::set_icon);
    register_method("get_icon", &NativeDialogNotify::get_icon);
}

NativeDialogNotify::NativeDialogNotify() {
}

NativeDialogNotify::~NativeDialogNotify() {
}

void NativeDialogNotify::_init() {
	title = "";
	text = "";
	icon = pfd::icon::info;
}

void NativeDialogNotify::send() {
	pfd::notify(title.alloc_c_string(), text.alloc_c_string(), icon);
}

void NativeDialogNotify::set_title(String p_title) {
	title = p_title;
}

String NativeDialogNotify::get_title() {
	return title;
}

void NativeDialogNotify::set_text(String p_text) {
	text = p_text;
}

String NativeDialogNotify::get_text() {
	return text;
}

void NativeDialogNotify::set_icon(int p_icon) {
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
	}
}

int NativeDialogNotify::get_icon() {
	switch(icon){
		case pfd::icon::info:
			return 0;
		case pfd::icon::warning:
			return 1;
		case pfd::icon::error:
			return 2;
	}

	return -1;
}
