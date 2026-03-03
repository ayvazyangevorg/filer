#include "classifier.hpp"

namespace filer {

std::string category_to_string(Category category) {
    switch (category) {
        case Category::SystemBinary: return "System Binaries";
        case Category::SystemConfig: return "System Config";
        case Category::SystemData:   return "System Data";
        case Category::SystemCache:  return "System Cache";
        case Category::SystemLog:    return "System Logs";
        case Category::UserConfig:   return "User Config";
        case Category::UserCache:    return "User Cache";
        case Category::UserData:     return "User Data";
        case Category::Other:        return "Other";
        default:                     return "Unknown";
    }
}

Category classify_path(const std::string& path) {

    if (path.rfind("/usr/bin", 0) == 0 ||
        path.rfind("/usr/sbin", 0) == 0) {
        return Category::SystemBinary;
    }

    if (path.rfind("/etc", 0) == 0) {
        return Category::SystemConfig;
    }

    if (path.rfind("/var/log", 0) == 0) {
        return Category::SystemLog;
    }

    if (path.rfind("/var/cache", 0) == 0) {
        return Category::SystemCache;
    }

    if (path.rfind("/var", 0) == 0) {
        return Category::SystemData;
    }

    if (path.find("/.config/") != std::string::npos) {
        return Category::UserConfig;
    }

    if (path.find("/.cache/") != std::string::npos) {
        return Category::UserCache;
    }

    if (path.find("/.local/share/") != std::string::npos) {
        return Category::UserData;
    }

    return Category::Other;
}

} // namespace filer