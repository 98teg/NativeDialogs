#ifndef NDSAVEFILE_H
#define NDSAVEFILE_H

#include <Godot.hpp>
#include <Node.hpp>

#include <portable-file-dialogs.h>

namespace godot {

class NativeDialogSaveFile : public Node {
	GODOT_CLASS(NativeDialogSaveFile, Node)

private:
	String title;
	String initial_path;
    PoolStringArray filters;
    bool force_overwrite;

	pfd::save_file* save_file;

public:
	static void _register_methods();

	NativeDialogSaveFile();
	~NativeDialogSaveFile();

	void _init();
	void _process(float delta);
	void _exit_tree();

	void show();
	void hide();

	void set_title(String p_title);
	String get_title();

	void set_initial_path(String p_initial_path);
	String get_initial_path();

	void set_filters(PoolStringArray p_filters);
	PoolStringArray get_filters();
	void add_filter(String filter);
	void clear_filters();

	void set_force_overwrite(bool p_force_overwrite);
	bool get_force_overwrite();
};

}

#endif
