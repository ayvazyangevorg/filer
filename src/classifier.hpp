#pragma once

#include <string>

namespace filer {

enum class Category {
    SystemBinary,
    SystemConfig,
    SystemData,
    SystemCache,
    SystemLog,
    UserConfig,
    UserCache,
    UserData,
    Other
};

std::string category_to_string(Category category);

Category classify_path(const std::string& path);

} // namespace filer