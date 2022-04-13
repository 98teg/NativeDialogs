#include "native_dialog_message.h"
#include "native_dialog_notify.h"
#include "native_dialog_open_file.h"
#include "native_dialog_save_file.h"
#include "native_dialog_select_folder.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_class<godot::NativeDialogMessage>();
	godot::register_class<godot::NativeDialogNotify>();
	godot::register_class<godot::NativeDialogOpenFile>();
	godot::register_class<godot::NativeDialogSaveFile>();
	godot::register_class<godot::NativeDialogSelectFolder>();
}
