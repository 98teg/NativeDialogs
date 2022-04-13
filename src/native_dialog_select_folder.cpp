#include "native_dialog_select_folder.h"

using namespace godot;

void NativeDialogSelectFolder::_register_methods() {
	register_property<NativeDialogSelectFolder, String>(
		"title",
		&NativeDialogSelectFolder::title,
		""
	);
	register_property<NativeDialogSelectFolder, String>(
		"initial_path",
		&NativeDialogSelectFolder::initial_path,
	"");
	register_property<NativeDialogSelectFolder, bool>(
		"force_path",
		&NativeDialogSelectFolder::force_path,
        false
	);

    register_method("_process", &NativeDialogSelectFolder::_process);
    register_method("_exit_tree", &NativeDialogSelectFolder::_exit_tree);

    register_method("show", &NativeDialogSelectFolder::show);
    register_method("hide", &NativeDialogSelectFolder::hide);

    register_method("set_title", &NativeDialogSelectFolder::set_title);
    register_method("get_title", &NativeDialogSelectFolder::get_title);
    register_method("set_initial_path", &NativeDialogSelectFolder::set_initial_path);
    register_method("get_initial_path", &NativeDialogSelectFolder::get_initial_path);
    register_method("set_force_path", &NativeDialogSelectFolder::set_force_path);
    register_method("get_force_path", &NativeDialogSelectFolder::get_force_path);

	register_signal<NativeDialogSelectFolder>(
		"folder_selected",
		"folder",
		GODOT_VARIANT_TYPE_STRING
	);
}

NativeDialogSelectFolder::NativeDialogSelectFolder() {
}

NativeDialogSelectFolder::~NativeDialogSelectFolder() {
	if(select_folder) hide();
}

void NativeDialogSelectFolder::_init() {
	title = "";
	initial_path = "";
	force_path = false;

	select_folder = NULL;
}

void NativeDialogSelectFolder::_process(float delta) {
	if(!select_folder || !select_folder->ready(0)) return;

	emit_signal("folder_selected", select_folder->result().c_str());

	hide();
}

void NativeDialogSelectFolder::_exit_tree() {
	if(select_folder) hide();
}

void NativeDialogSelectFolder::show() {
	ERR_FAIL_COND(!is_inside_tree());
	ERR_FAIL_COND(!is_processing());

	if(select_folder) hide();

	select_folder = new pfd::select_folder(
		title.alloc_c_string(),
		initial_path.alloc_c_string(),
		force_path ? pfd::opt::force_path : pfd::opt::none
	);
}

void NativeDialogSelectFolder::hide() {
	if(!select_folder) return;

	select_folder->kill();

	delete select_folder;

	select_folder = NULL;
}

void NativeDialogSelectFolder::set_title(String p_title) {
	title = p_title;
}

String NativeDialogSelectFolder::get_title() {
	return title;
}

void NativeDialogSelectFolder::set_initial_path(String p_initial_path) {
	initial_path = p_initial_path;
}

String NativeDialogSelectFolder::get_initial_path() {
	return initial_path;
}

void NativeDialogSelectFolder::set_force_path(bool p_force_path) {
	force_path = p_force_path;
}

bool NativeDialogSelectFolder::get_force_path() {
	return force_path;
}
