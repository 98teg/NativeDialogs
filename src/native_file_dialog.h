#ifndef NATIVEFILEDIALOG_H
#define NATIVEFILEDIALOG_H

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>

#include <portable-file-dialogs.h>

namespace godot {

class NativeFileDialog : public Node {
	GDCLASS(NativeFileDialog, Node)

protected:
	static void _bind_methods();

public:
    enum FileMode {
		FILE_MODE_OPEN_FILE,
		FILE_MODE_OPEN_FILES,
		FILE_MODE_OPEN_DIR,
		FILE_MODE_SAVE_FILE
    };

    enum Access {
		ACCESS_RESOURCES,
		ACCESS_USERDATA,
		ACCESS_FILESYSTEM
    };

private:
	String title;
	String initial_path;
    PackedStringArray filters;
	FileMode mode;
    Access access;

	pfd::open_file* open_file = nullptr;
	pfd::save_file* save_file = nullptr;
	pfd::select_folder* select_folder = nullptr;

    PackedStringArray default_filters();
    std::vector<std::string> pfd_filters();

    std::string pfd_path(const String &godot_path);
    String godot_path(const std::string &pfd_path);
public:
	NativeFileDialog();
	~NativeFileDialog();

	void _process(float delta);
	void _exit_tree();

	void show();
	void hide();

	void set_title(const String &p_title);
	String get_title();

	void set_initial_path(const String &p_initial_path);
	String get_initial_path();

	void set_mode(FileMode p_mode);
	FileMode get_mode();

	void set_filters(const PackedStringArray &p_filters);
	PackedStringArray get_filters();
	void add_filter(const String &filter);
	void clear_filters();
};

}

VARIANT_ENUM_CAST(NativeFileDialog, FileMode);
VARIANT_ENUM_CAST(NativeFileDialog, Access);

#endif // NATIVEFILEDIALOG_H
