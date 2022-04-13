#ifndef FILTERS_H
#define FILTERS_H

#include <Godot.hpp>

#include <vector>
#include <string>

namespace godot {

inline PoolStringArray default_filters() {
    PoolStringArray default_filters = PoolStringArray();
    default_filters.append("* ; All Files");
    return default_filters;
}

inline std::vector<std::string> pfd_filters(const PoolStringArray &godot_filters) {
	std::vector<std::string> pfd_filters = std::vector<std::string>();

	for(int i = 0; i < godot_filters.size(); i++) {
		PoolStringArray filter = godot_filters.read()[i].split(" ; ");

		String name = filter[1];
		String extensions = filter[0].replace(", ", " ");

		pfd_filters.push_back(name.alloc_c_string());
		pfd_filters.push_back(extensions.alloc_c_string());
	}

    return pfd_filters;
}

}

#endif
