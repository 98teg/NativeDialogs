#ifndef NDNOTIFICATION_H
#define NDNOTIFICATION_H

#include <Godot.hpp>
#include <Node.hpp>

#include <portable-file-dialogs.h>

namespace godot {

class NativeDialogNotify : public Node {
	GODOT_CLASS(NativeDialogNotify, Node)

private:
	String title;
	String text;
	pfd::icon icon;

public:
	static void _register_methods();

	NativeDialogNotify();
	~NativeDialogNotify();

	void _init();

	void send();

	void set_title(String p_title);
	String get_title();

	void set_text(String p_text);
	String get_text();

	void set_icon(int p_icon);
	int get_icon();
};

}

#endif
