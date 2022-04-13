#ifndef NDMESSAGE_H
#define NDMESSAGE_H

#include <Godot.hpp>
#include <Node.hpp>

#include <portable-file-dialogs.h>

namespace godot {

class NativeDialogMessage : public Node {
	GODOT_CLASS(NativeDialogMessage, Node)

private:
	String title;
	String text;
	pfd::choice choice;
	pfd::icon icon;

	pfd::message* message;

public:
	static void _register_methods();

	NativeDialogMessage();
	~NativeDialogMessage();

	void _init();
	void _process(float delta);
	void _exit_tree();

	void show();
	void hide();

	void set_title(String p_title);
	String get_title();

	void set_text(String p_text);
	String get_text();

	void set_choice(int p_choice);
	int get_choice();

	void set_icon(int p_icon);
	int get_icon();
};

}

#endif
