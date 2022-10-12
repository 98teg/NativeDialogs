#ifndef NATIVENOTIFICATION_H
#define NATIVENOTIFICATION_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <portable-file-dialogs.h>

namespace godot {

class NativeNotification : public Node {
	GDCLASS(NativeNotification, Node);

protected:
	static void _bind_methods();

public:
	enum Icon {
		ICON_INFO,
		ICON_WARNING,
		ICON_ERROR
	};

private:
	String title;
	String text;
	Icon icon;

public:
	NativeNotification();

	void send();

	void set_title(const String &p_title);
	String get_title();

	void set_text(const String &p_text);
	String get_text();

	void set_icon(Icon p_icon);
	Icon get_icon();
};

} // namespace godot

VARIANT_ENUM_CAST(NativeNotification, Icon);

#endif // NATIVENOTIFICATION_H
