#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/translation_server.hpp>

#include "native_file_dialog.h"

using namespace godot;

void NativeFileDialog::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_title", "title"), &NativeFileDialog::set_title);
	ClassDB::bind_method(D_METHOD("get_title"), &NativeFileDialog::get_title);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");

	ClassDB::bind_method(D_METHOD("set_mode_overrides_title", "override"), &NativeFileDialog::set_mode_overrides_title);
	ClassDB::bind_method(D_METHOD("is_mode_overriding_title"), &NativeFileDialog::is_mode_overriding_title);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "mode_overrides_title"), "set_mode_overrides_title", "is_mode_overriding_title");

	ClassDB::bind_method(D_METHOD("set_file_mode", "mode"), &NativeFileDialog::set_file_mode);
	ClassDB::bind_method(D_METHOD("get_file_mode"), &NativeFileDialog::get_file_mode);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "file_mode", PROPERTY_HINT_ENUM, "Open File,Open Files,Open Folder,Save"), "set_file_mode", "get_file_mode");

	ClassDB::bind_method(D_METHOD("set_access", "access"), &NativeFileDialog::set_access);
	ClassDB::bind_method(D_METHOD("get_access"), &NativeFileDialog::get_access);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "access", PROPERTY_HINT_ENUM, "Resources,User Data,File System"), "set_access", "get_access");

	ClassDB::bind_method(D_METHOD("set_root_subfolder", "dir"), &NativeFileDialog::set_root_subfolder);
	ClassDB::bind_method(D_METHOD("get_root_subfolder"), &NativeFileDialog::get_root_subfolder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "root_subfolder"), "set_root_subfolder", "get_root_subfolder");

	ClassDB::bind_method(D_METHOD("set_filters", "filter"), &NativeFileDialog::set_filters);
	ClassDB::bind_method(D_METHOD("get_filters"), &NativeFileDialog::get_filters);
	ClassDB::bind_method(D_METHOD("add_filter", "filter", "description"), &NativeFileDialog::add_filter, DEFVAL(""));
	ClassDB::bind_method(D_METHOD("clear_filters"), &NativeFileDialog::clear_filters);
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "filters"), "set_filters", "get_filters");

	ClassDB::bind_method(D_METHOD("show"), &NativeFileDialog::show);
	ClassDB::bind_method(D_METHOD("hide"), &NativeFileDialog::hide);

	ADD_SIGNAL(MethodInfo("file_selected", PropertyInfo(Variant::STRING, "path")));
	ADD_SIGNAL(MethodInfo("files_selected", PropertyInfo(Variant::PACKED_STRING_ARRAY, "paths")));
	ADD_SIGNAL(MethodInfo("dir_selected", PropertyInfo(Variant::STRING, "dir")));

	BIND_ENUM_CONSTANT(FILE_MODE_OPEN_FILE);
	BIND_ENUM_CONSTANT(FILE_MODE_OPEN_FILES);
	BIND_ENUM_CONSTANT(FILE_MODE_OPEN_DIR);
	BIND_ENUM_CONSTANT(FILE_MODE_SAVE_FILE);

	BIND_ENUM_CONSTANT(ACCESS_RESOURCES);
	BIND_ENUM_CONSTANT(ACCESS_USERDATA);
	BIND_ENUM_CONSTANT(ACCESS_FILESYSTEM);
}

NativeFileDialog::NativeFileDialog() {
	mode_overrides_title = true;
	mode = FILE_MODE_SAVE_FILE;
	access = ACCESS_RESOURCES;
	root_subfolder = "";
	filters = PackedStringArray();
	title = "Save a File";
}

NativeFileDialog::~NativeFileDialog() {
	hide();
}

void NativeFileDialog::_process(float delta) {
	if (open_file && open_file->ready(0)) {
		PackedStringArray result = PackedStringArray();
		for (int i = 0; i < open_file->result().size(); i++)
			result.append(get_godot_path(open_file->result()[i]));

		if (!result.is_empty())
			emit_signal("files_selected", result);

		hide();
	} else if (save_file && save_file->ready(0)) {
		String result = get_godot_path(save_file->result());

		if (!result.is_empty())
			emit_signal("file_selected", result);

		hide();
	} else if (select_folder && select_folder->ready(0)) {
		String result = get_godot_path(select_folder->result());

		if (!result.is_empty())
			emit_signal("dir_selected", get_godot_path(select_folder->result()));

		hide();
	}
}

void NativeFileDialog::_exit_tree() {
	hide();
}

void NativeFileDialog::show() {
	ERR_FAIL_COND(!is_inside_tree());
	ERR_FAIL_COND(!is_processing());

	hide();

	const char *title = String(TranslationServer::get_singleton()->translate(get_title())).utf8().get_data();

	if (mode == FILE_MODE_OPEN_FILE || mode == FILE_MODE_OPEN_FILES) {
		pfd::opt option = mode == FILE_MODE_OPEN_FILES ? pfd::opt::multiselect : pfd::opt::none;

		open_file = new pfd::open_file(title, get_pfd_path(), get_pfd_filters(), option);
	}

	if (mode == FILE_MODE_SAVE_FILE) {
		save_file = new pfd::save_file(title, get_pfd_path(), get_pfd_filters(), pfd::opt::none);
	}

	if (mode == FILE_MODE_OPEN_DIR) {
		select_folder = new pfd::select_folder(title, get_pfd_path(), pfd::opt::none);
	}
}

void NativeFileDialog::hide() {
	if (open_file) {
		open_file->kill();

		delete open_file;

		open_file = nullptr;
	}

	if (save_file) {
		save_file->kill();

		delete save_file;

		save_file = nullptr;
	}

	if (select_folder) {
		select_folder->kill();

		delete select_folder;

		select_folder = nullptr;
	}
}

void NativeFileDialog::set_title(const String &p_title) {
	title = p_title;
}

String NativeFileDialog::get_title() const {
	return title;
}

void NativeFileDialog::set_mode_overrides_title(bool p_override) {
	if (mode_overrides_title == p_override) {
		return;
	}

	mode_overrides_title = p_override;

	override_title();
}

bool NativeFileDialog::is_mode_overriding_title() {
	return mode_overrides_title;
}

void NativeFileDialog::set_file_mode(FileMode p_mode) {
	ERR_FAIL_INDEX((int)p_mode, 4);

	if (mode == p_mode) {
		return;
	}

	mode = p_mode;

	override_title();
}

NativeFileDialog::FileMode NativeFileDialog::get_file_mode() const {
	return mode;
}

void NativeFileDialog::set_access(Access p_access) {
	ERR_FAIL_INDEX(p_access, 3);

	if (access == p_access) {
		return;
	}

	access = p_access;

	set_root_subfolder("");
}

NativeFileDialog::Access NativeFileDialog::get_access() const {
	return access;
}

void NativeFileDialog::set_root_subfolder(const String &p_root) {
	ERR_FAIL_COND_MSG(!DirAccess::dir_exists_absolute(get_root_string() + p_root), "root_subfolder must be an existing sub-directory.");

	root_subfolder = p_root;
}

String NativeFileDialog::get_root_subfolder() const {
	return root_subfolder;
}

void NativeFileDialog::set_filters(const PackedStringArray &p_filters) {
	filters = p_filters;
}

PackedStringArray NativeFileDialog::get_filters() const {
	return filters;
}

void NativeFileDialog::add_filter(const String &p_filter, const String &p_description = "") {
	ERR_FAIL_COND_MSG(p_filter.begins_with("."), "Filter must be \"filename.extension\", can't start with dot.");

	if (p_description.is_empty()) {
		filters.push_back(p_filter);
	} else {
		filters.push_back(p_filter + String(" ; ") + p_description);
	}
}

void NativeFileDialog::clear_filters() {
	filters.clear();
}

std::vector<std::string> NativeFileDialog::get_pfd_filters() const {
	std::vector<std::string> pfd_filters = std::vector<std::string>();

	for (int i = 0; i < filters.size(); i++) {
		PackedStringArray filter = filters[i].split(" ; ");

		String name = TranslationServer::get_singleton()->translate(filter.size() == 2 ? filter[1] : "");
		String extensions = filter[0].replace(", ", " ");

		pfd_filters.push_back(name.utf8().get_data());
		pfd_filters.push_back(extensions.utf8().get_data());
	}

	return pfd_filters;
}

std::string NativeFileDialog::get_pfd_path() const {
	String path = get_root_string() + get_root_subfolder();
	String global_path = ProjectSettings::get_singleton()->globalize_path(path);

	// Fixes issue with Open Folder mode, as it requires the string to end with slash
	if (!global_path.ends_with("/")) {
		global_path = global_path + "/";
	}

#if _WIN32
	global_path = global_path.replace("/", "\\");
#endif

	return global_path.utf8().get_data();
}

String NativeFileDialog::get_godot_path(const std::string &pfd_path) const {
	String godot_path = String::utf8(pfd_path.c_str());

#if _WIN32
	godot_path = godot_path.replace("\\", "/");
#endif

	return godot_path;
}

void NativeFileDialog::override_title() {
	if (!mode_overrides_title) {
		return;
	}

	switch (mode) {
		case FILE_MODE_OPEN_FILE:
			set_title("Open a File");
			break;
		case FILE_MODE_OPEN_FILES:
			set_title("Open File(s)");
			break;
		case FILE_MODE_OPEN_DIR:
			set_title("Open a Directory");
			break;
		case FILE_MODE_SAVE_FILE:
			set_title("Save a File");
	}
}

String NativeFileDialog::get_root_string() const {
	switch (access) {
		case ACCESS_RESOURCES:
			return "res://";
		case ACCESS_USERDATA:
			return "user://";
		default:
			return "";
	}
}
