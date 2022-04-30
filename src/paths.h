#ifndef PATHS_H
#define PATHS_H

#include <Godot.hpp>
#include <ProjectSettings.hpp>

#include <string>

namespace godot {

inline std::string pfd_path(const String &godot_path) {
    String global_path = ProjectSettings::get_singleton()->globalize_path(godot_path);

#if _WIN32
    global_path = global_path.replace("/", "\\");
#endif

    return global_path.alloc_c_string();
}

inline String godot_path(const std::string &pfd_path) {
    String godot_path = pfd_path.c_str();

#if _WIN32
    godot_path = godot_path.replace("\\", "/");
#endif

    return godot_path;
}

}

#endif
