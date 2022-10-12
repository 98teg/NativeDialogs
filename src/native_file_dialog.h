#ifndef NATIVEFILEDIALOG_H
#define NATIVEFILEDIALOG_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>

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
	bool mode_overrides_title;
	FileMode mode;
	Access access;
	String root_subfolder;
	PackedStringArray filters;

	pfd::open_file *open_file = nullptr;
	pfd::save_file *save_file = nullptr;
	pfd::select_folder *select_folder = nullptr;

	std::vector<std::string> get_pfd_filters() const;

	std::string get_pfd_path() const;
	String get_godot_path(const std::string &pfd_path) const;

	void override_title();

	String get_root_string() const;

public:
	NativeFileDialog();
	~NativeFileDialog();

	void _process(float delta);
	void _exit_tree();

	void show();
	void hide();

	void set_title(const String &p_title);
	String get_title() const;

	void set_mode_overrides_title(bool p_override);
	bool is_mode_overriding_title();

	void set_file_mode(FileMode p_mode);
	FileMode get_file_mode() const;

	void set_access(Access p_access);
	Access get_access() const;

	void set_root_subfolder(const String &p_root);
	String get_root_subfolder() const;

	void set_filters(const PackedStringArray &p_filters);
	PackedStringArray get_filters() const;
	void add_filter(const String &p_filter, const String &p_description);
	void clear_filters();
};

} // namespace godot

VARIANT_ENUM_CAST(NativeFileDialog, FileMode);
VARIANT_ENUM_CAST(NativeFileDialog, Access);

#endif // NATIVEFILEDIALOG_H
