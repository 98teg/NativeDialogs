#include "native_dialog_open_file.h"
#include "filters.h"

using namespace godot;

void NativeDialogOpenFile::_register_methods() {
	register_property<NativeDialogOpenFile, String>("title", &NativeDialogOpenFile::title, "");
	register_property<NativeDialogOpenFile, String>(
		"initial_path",
		&NativeDialogOpenFile::initial_path,
		""
	);
	register_property<NativeDialogOpenFile, PoolStringArray>(
		"filters",
		&NativeDialogOpenFile::filters,
		default_filters()
	);
	register_property<NativeDialogOpenFile, bool>(
        "multiselect",
        &NativeDialogOpenFile::multiselect,
        false
	);

    register_method("_process", &NativeDialogOpenFile::_process);
    register_method("_exit_tree", &NativeDialogOpenFile::_exit_tree);

    register_method("show", &NativeDialogOpenFile::show);
    register_method("hide", &NativeDialogOpenFile::hide);

    register_method("set_title", &NativeDialogOpenFile::set_title);
    register_method("get_title", &NativeDialogOpenFile::get_title);
    register_method("set_initial_path", &NativeDialogOpenFile::set_initial_path);
    register_method("get_initial_path", &NativeDialogOpenFile::get_initial_path);
    register_method("set_filters", &NativeDialogOpenFile::set_filters);
    register_method("get_filters", &NativeDialogOpenFile::get_filters);
    register_method("add_filter", &NativeDialogOpenFile::add_filter);
    register_method("clear_filters", &NativeDialogOpenFile::clear_filters);
    register_method("set_multiselect", &NativeDialogOpenFile::set_multiselect);
    register_method("get_multiselect", &NativeDialogOpenFile::get_multiselect);

	register_signal<NativeDialogOpenFile>(
		"files_selected",
		"files",
		GODOT_VARIANT_TYPE_POOL_STRING_ARRAY
	);
}

NativeDialogOpenFile::NativeDialogOpenFile() {
}

NativeDialogOpenFile::~NativeDialogOpenFile() {
	if(open_file) hide();
}

void NativeDialogOpenFile::_init() {
	title = "";
	initial_path = "";
	filters = default_filters();
	multiselect = false;

	open_file = NULL;
}

void NativeDialogOpenFile::_process(float delta) {
	if(!open_file || !open_file->ready(0)) return;

	PoolStringArray result = PoolStringArray();
	for(int i = 0; i < open_file->result().size(); i++) {
		result.append(open_file->result()[i].c_str());
	}

	emit_signal("files_selected", result);

	hide();
}

void NativeDialogOpenFile::_exit_tree() {
	if(open_file) hide();
}

void NativeDialogOpenFile::show() {
	ERR_FAIL_COND(!is_inside_tree());
	ERR_FAIL_COND(!is_processing());

	if(open_file) hide();

	open_file = new pfd::open_file(
		title.alloc_c_string(),
		initial_path.alloc_c_string(),
		pfd_filters(filters),
		multiselect ? pfd::opt::multiselect : pfd::opt::none
	);
}

void NativeDialogOpenFile::hide() {
	if(!open_file) return;

	open_file->kill();

	delete open_file;

	open_file = NULL;
}

void NativeDialogOpenFile::set_title(String p_title) {
	title = p_title;
}

String NativeDialogOpenFile::get_title() {
	return title;
}

void NativeDialogOpenFile::set_initial_path(String p_initial_path) {
	initial_path = p_initial_path;
}

String NativeDialogOpenFile::get_initial_path() {
	return initial_path;
}

void NativeDialogOpenFile::set_filters(PoolStringArray p_filters) {
	filters = p_filters;
}

void NativeDialogOpenFile::add_filter(String filter) {
	filters.append(filter);
}

void NativeDialogOpenFile::clear_filters() {
	filters.resize(0);
}

PoolStringArray NativeDialogOpenFile::get_filters() {
	return filters;
}

void NativeDialogOpenFile::set_multiselect(bool p_multiselect) {
	multiselect = p_multiselect;
}

bool NativeDialogOpenFile::get_multiselect() {
	return multiselect;
}
