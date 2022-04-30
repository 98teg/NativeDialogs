#ifndef PATHS_H
#define PATHS_H

#include <Godot.hpp>

#include <string>

namespace godot {

inline std::string pfd_path(const String &godot_path) {
#if _WIN32
    return godot_path.replace("/", "\\").alloc_c_string();
#else
    return godot_path.alloc_c_string();
#endif
}

inline String godot_path(const std::string &pfd_path) {
#if _WIN32
    return String(pfd_path.c_str()).replace("\\", "/");
#else
    return pfd_path.c_str();
#endif
}

}

#endif
