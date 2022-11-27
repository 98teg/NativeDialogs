#include <godot_cpp/classes/translation_server.hpp>

#include "native_confirmation_dialog.h"

using namespace godot;

void NativeConfirmationDialog::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_buttons_texts", "buttons_texts"), &NativeConfirmationDialog::set_buttons_texts);
	ClassDB::bind_method(D_METHOD("get_buttons_texts"), &NativeConfirmationDialog::get_buttons_texts);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "buttons_texts", PROPERTY_HINT_ENUM, "OK Cancel,Yes No"), "set_buttons_texts", "get_buttons_texts");

	BIND_ENUM_CONSTANT(BUTTONS_TEXTS_OK_CANCEL);
	BIND_ENUM_CONSTANT(BUTTONS_TEXTS_YES_NO);
}

NativeConfirmationDialog::NativeConfirmationDialog() {
	set_title(TranslationServer::get_singleton()->translate("Please Confirm..."));
	set_icon(ICON_QUESTION);
	set_buttons_texts(BUTTONS_TEXTS_OK_CANCEL);
}

void NativeConfirmationDialog::_process(float delta) {
	NativeAcceptDialog::_process(delta);
}

void NativeConfirmationDialog::_exit_tree() {
	NativeAcceptDialog::_exit_tree();
}

void NativeConfirmationDialog::set_buttons_texts(ButtonsTexts p_buttons_texts) {
	buttons_texts = p_buttons_texts;

	switch (buttons_texts) {
		case BUTTONS_TEXTS_OK_CANCEL:
			set_choice(pfd::choice::ok_cancel);
			break;
		case BUTTONS_TEXTS_YES_NO:
			set_choice(pfd::choice::yes_no);
			break;
	}
}

NativeConfirmationDialog::ButtonsTexts NativeConfirmationDialog::get_buttons_texts() {
	return buttons_texts;
}
