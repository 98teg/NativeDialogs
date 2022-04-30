#include "native_dialog_save_file.h"
#include "filters.h"
#include "paths.h"

using namespace godot;

void NativeDialogSaveFile::_register_methods() {
	register_property<NativeDialogSaveFile, String>("title", &NativeDialogSaveFile::title, "");
	register_property<NativeDialogSaveFile, String>(
		"initial_path",
		&NativeDialogSaveFile::initial_path,
		""
	);
	register_property<NativeDialogSaveFile, PoolStringArray>(
		"filters",
		&NativeDialogSaveFile::filters,
		default_filters()
	);
	register_property<NativeDialogSaveFile, bool>(
        "force_overwrite",
        &NativeDialogSaveFile::force_overwrite,
        false
	);

    register_method("_process", &NativeDialogSaveFile::_process);
    register_method("_exit_tree", &NativeDialogSaveFile::_exit_tree);

    register_method("show", &NativeDialogSaveFile::show);
    register_method("hide", &NativeDialogSaveFile::hide);

    register_method("set_title", &NativeDialogSaveFile::set_title);
    register_method("get_title", &NativeDialogSaveFile::get_title);
    register_method("set_initial_path", &NativeDialogSaveFile::set_initial_path);
    register_method("get_initial_path", &NativeDialogSaveFile::get_initial_path);
    register_method("set_filters", &NativeDialogSaveFile::set_filters);
    register_method("get_filters", &NativeDialogSaveFile::get_filters);
    register_method("add_filter", &NativeDialogSaveFile::add_filter);
    register_method("clear_filters", &NativeDialogSaveFile::clear_filters);
    register_method("set_force_overwrite", &NativeDialogSaveFile::set_force_overwrite);
    register_method("get_force_overwrite", &NativeDialogSaveFile::get_force_overwrite);

	register_signal<NativeDialogSaveFile>(
		"file_selected",
		"file",
		GODOT_VARIANT_TYPE_STRING
	);
}

NativeDialogSaveFile::NativeDialogSaveFile() {
}

NativeDialogSaveFile::~NativeDialogSaveFile() {
	if(save_file) hide();
}

void NativeDialogSaveFile::_init() {
	title = "";
	initial_path = "";
	filters = default_filters();
	force_overwrite = false;

	save_file = NULL;
}

void NativeDialogSaveFile::_process(float delta) {
	if(!save_file || !save_file->ready(0)) return;

	emit_signal("file_selected", godot_path(save_file->result()));

	hide();
}

void NativeDialogSaveFile::_exit_tree() {
	if(save_file) hide();
}

void NativeDialogSaveFile::show() {
	ERR_FAIL_COND(!is_inside_tree());
	ERR_FAIL_COND(!is_processing());

	if(save_file) hide();

	save_file = new pfd::save_file(
		title.alloc_c_string(),
		pfd_path(initial_path),
		pfd_filters(filters),
		force_overwrite ? pfd::opt::force_overwrite : pfd::opt::none
	);
}

void NativeDialogSaveFile::hide() {
	if(!save_file) return;

	save_file->kill();

	delete save_file;

	save_file = NULL;
}

void NativeDialogSaveFile::set_title(String p_title) {
	title = p_title;
}

String NativeDialogSaveFile::get_title() {
	return title;
}

void NativeDialogSaveFile::set_initial_path(String p_initial_path) {
	initial_path = p_initial_path;
}

String NativeDialogSaveFile::get_initial_path() {
	return initial_path;
}

void NativeDialogSaveFile::set_filters(PoolStringArray p_filters) {
	filters = p_filters;
}

void NativeDialogSaveFile::add_filter(String filter) {
	filters.append(filter);
}

void NativeDialogSaveFile::clear_filters() {
	filters.resize(0);
}

PoolStringArray NativeDialogSaveFile::get_filters() {
	return filters;
}

void NativeDialogSaveFile::set_force_overwrite(bool p_force_overwrite) {
	force_overwrite = p_force_overwrite;
}

bool NativeDialogSaveFile::get_force_overwrite() {
	return force_overwrite;
}
