#ifndef NDOPENFILE_H
#define NDOPENFILE_H

#include <Godot.hpp>
#include <Node.hpp>

#include <portable-file-dialogs.h>

namespace godot {

class NativeDialogOpenFile : public Node {
	GODOT_CLASS(NativeDialogOpenFile, Node)

private:
	String title;
	String initial_path;
    PoolStringArray filters;
    bool multiselect;

	pfd::open_file* open_file;

public:
	static void _register_methods();

	NativeDialogOpenFile();
	~NativeDialogOpenFile();

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

	void set_multiselect(bool p_multiselect);
	bool get_multiselect();
};

}

#endif
