#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/os.hpp>

#include "native_file_dialog.h"

using namespace godot;

void NativeFileDialog::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_title"), &NativeFileDialog::set_title);
    ClassDB::bind_method(D_METHOD("get_title"), &NativeFileDialog::get_title);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "title"), "set_title", "get_title");

    ClassDB::bind_method(D_METHOD("set_root_subfolder"), &NativeFileDialog::set_root_subfolder);
    ClassDB::bind_method(D_METHOD("get_root_subfolder"), &NativeFileDialog::get_root_subfolder);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "root_subfolder"), "set_root_subfolder", "get_root_subfolder");

    ClassDB::bind_method("set_mode", &NativeFileDialog::set_mode);
    ClassDB::bind_method("get_mode", &NativeFileDialog::get_mode);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::INT,
			"mode",
			PROPERTY_HINT_ENUM,
			"Open file,Open files,Open dir,Save file"
		),
		"set_mode",
		"get_mode"
	);

    ClassDB::bind_method("set_access", &NativeFileDialog::set_access);
    ClassDB::bind_method("get_access", &NativeFileDialog::get_access);
	ADD_PROPERTY(
		PropertyInfo(
			Variant::INT,
			"access",
			PROPERTY_HINT_ENUM,
			"Resources,User Data,File System"
		),
		"set_access",
		"get_access"
	);

    ClassDB::bind_method("show", &NativeFileDialog::show);
    ClassDB::bind_method("hide", &NativeFileDialog::hide);

	ADD_SIGNAL(
		MethodInfo(
			"file_selected",
			PropertyInfo(
				Variant::STRING,
				"file"
			)
		)
	);

	ADD_SIGNAL(
		MethodInfo(
			"files_selected",
			PropertyInfo(
				Variant::PACKED_STRING_ARRAY,
				"files"
			)
		)
	);

	ADD_SIGNAL(
		MethodInfo(
			"dir_selected",
			PropertyInfo(
				Variant::STRING,
				"dir"
			)
		)
	);

	BIND_ENUM_CONSTANT(FILE_MODE_OPEN_FILE);
    BIND_ENUM_CONSTANT(FILE_MODE_OPEN_FILES);
    BIND_ENUM_CONSTANT(FILE_MODE_OPEN_DIR);
    BIND_ENUM_CONSTANT(FILE_MODE_SAVE_FILE);

    BIND_ENUM_CONSTANT(ACCESS_RESOURCES);
    BIND_ENUM_CONSTANT(ACCESS_USERDATA);
	BIND_ENUM_CONSTANT(ACCESS_FILESYSTEM);
}

NativeFileDialog::NativeFileDialog() {
	title = "";
	root_subfolder = "";
	filters = get_default_filters();
}

NativeFileDialog::~NativeFileDialog() {
	hide();
}

void NativeFileDialog::_process(float delta) {
	if(open_file && open_file->ready(0)) {
		PackedStringArray result = PackedStringArray();
		for(int i = 0; i < open_file->result().size(); i++) {
			result.append(get_godot_path(open_file->result()[i]));
		}

		if (result.size() == 1) {
			emit_signal("file_selected", result[0]);
		} else {
			emit_signal("files_selected", result);
		}

		hide();
	}

	if(save_file && save_file->ready(0)) {
		emit_signal("file_selected", get_godot_path(save_file->result()));

		hide();
	}


	if(select_folder && select_folder->ready(0)) {
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

	if(mode == FILE_MODE_OPEN_FILE || mode == FILE_MODE_OPEN_FILES) {
		open_file = new pfd::open_file(
			title.utf8().get_data(),
			get_pfd_path(),
			get_pfd_filters(),
			mode == FILE_MODE_OPEN_FILES ? pfd::opt::multiselect : pfd::opt::none
		);
	}

	if(mode == FILE_MODE_SAVE_FILE) {
		save_file = new pfd::save_file(
			title.utf8().get_data(),
			get_pfd_path(),
			get_pfd_filters(),
			pfd::opt::none
		);
	}

	if(mode == FILE_MODE_OPEN_DIR) {
		select_folder = new pfd::select_folder(
			title.utf8().get_data(),
			get_pfd_path(),
			pfd::opt::none
		);
	} 
}

void NativeFileDialog::hide() {
	if(open_file) {
		open_file->kill();

		delete open_file;

		open_file = nullptr;
	}

	if(save_file) {
		save_file->kill();

		delete save_file;

		save_file = nullptr;
	}

	if(select_folder) {
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

void NativeFileDialog::set_root_subfolder(const String &p_root) {
	root_subfolder = p_root;
}

String NativeFileDialog::get_root_subfolder() const {
	return root_subfolder;
}

void NativeFileDialog::set_mode(FileMode p_mode) {
	ERR_FAIL_INDEX(p_mode, 4);

	mode = p_mode;
}

NativeFileDialog::FileMode NativeFileDialog::get_mode() const {
	return mode;
}

void NativeFileDialog::set_access(Access p_access) {
	ERR_FAIL_INDEX(p_access, 3);

	access = p_access;
}

NativeFileDialog::Access NativeFileDialog::get_access() const {
	return access;
}

void NativeFileDialog::set_filters(const PackedStringArray &p_filters) {
	filters = p_filters;
}

void NativeFileDialog::add_filter(const String &filter) {
	filters.append(filter);
}

void NativeFileDialog::clear_filters() {
	filters.resize(0);
}

PackedStringArray NativeFileDialog::get_filters() const {
	return filters;
}

PackedStringArray NativeFileDialog::get_default_filters() const {
    PackedStringArray default_filters = PackedStringArray();
    default_filters.append("* ; All Files");
    return default_filters;
}

std::vector<std::string> NativeFileDialog::get_pfd_filters() const {
    std::vector<std::string> pfd_filters = std::vector<std::string>();

    for(int i = 0; i < filters.size(); i++) {
        PackedStringArray filter = filters[i].split(" ; ");

        String name = filter[1];
        String extensions = filter[0].replace(", ", " ");

        pfd_filters.push_back(name.utf8().get_data());
        pfd_filters.push_back(extensions.utf8().get_data());
    }
    return pfd_filters;
}

std::string NativeFileDialog::get_pfd_path() const {
	String path = get_root_string() + get_root_subfolder();
    String global_path = ProjectSettings::get_singleton()->globalize_path(path);

#if _WIN32
    global_path = global_path.replace("/", "\\");
#endif

    return global_path.utf8().get_data();
}

String NativeFileDialog::get_godot_path(const std::string &pfd_path) const {
    String godot_path = pfd_path.c_str();

#if _WIN32
    godot_path = godot_path.replace("\\", "/");
#endif

    return godot_path;
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
