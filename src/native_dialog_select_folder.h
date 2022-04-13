#ifndef NDSELECTFOLDER_H
#define NDSELECTFOLDER_H

#include <Godot.hpp>
#include <Node.hpp>

#include <portable-file-dialogs.h>

namespace godot {

class NativeDialogSelectFolder : public Node {
	GODOT_CLASS(NativeDialogSelectFolder, Node)

private:
	String title;
	String initial_path;
    bool force_path;

	pfd::select_folder* select_folder;

public:
	static void _register_methods();

	NativeDialogSelectFolder();
	~NativeDialogSelectFolder();

	void _init();
	void _process(float delta);
	void _exit_tree();

	void show();
	void hide();

	void set_title(String p_title);
	String get_title();

	void set_initial_path(String p_initial_path);
	String get_initial_path();

	void set_force_path(bool p_force_path);
	bool get_force_path();
};

}

#endif
