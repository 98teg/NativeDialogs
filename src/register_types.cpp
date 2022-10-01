#include "register_types.h"

#include <godot/gdnative_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "native_message.h"
#include "native_accept_dialog.h"
#include "native_notification.h"
#include "native_file_dialog.h"

using namespace godot;

void register_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<NativeMessage>();
	ClassDB::register_class<NativeAcceptDialog>();
	ClassDB::register_class<NativeNotification>();
	ClassDB::register_class<NativeFileDialog>();
}

void unregister_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {

// Initialization.

GDNativeBool GDN_EXPORT native_dialogs_init(const GDNativeInterface *p_interface, const GDNativeExtensionClassLibraryPtr p_library, GDNativeInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

	init_obj.register_initializer(register_types);
	init_obj.register_terminator(unregister_types);

	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
