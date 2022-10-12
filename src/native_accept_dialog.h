#ifndef NATIVEACCEPTDIALOG_H
#define NATIVEACCEPTDIALOG_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <portable-file-dialogs.h>

namespace godot {

  class NativeAcceptDialog : public Node {
    GDCLASS(NativeAcceptDialog, Node)

  protected:
    static void _bind_methods();

    void process_button(pfd::button button);

    void set_choice(pfd::choice p_choice);
    pfd::choice get_choice();

  public:
    enum Icon { ICON_INFO, ICON_WARNING, ICON_ERROR, ICON_QUESTION };

  private:
    String title;
    String text;
    Icon icon;

    pfd::choice choice = pfd::choice::ok;
    pfd::message *message = nullptr;

  public:
    NativeAcceptDialog();
    ~NativeAcceptDialog();

    void _process(float delta);
    void _exit_tree();

    void show();
    void hide();

    void set_title(const String &p_title);
    String get_title();

    void set_text(const String &p_text);
    String get_text();

    void set_icon(Icon p_icon);
    Icon get_icon();
  };

} // namespace godot

VARIANT_ENUM_CAST(NativeAcceptDialog, Icon);

#endif // NATIVEACCEPTDIALOG_H
