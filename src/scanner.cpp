#include "scanner.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace filer {

Scanner::Scanner() = default;

void Scanner::add_root(const std::string& path) {
    m_roots.push_back(path);
}

void Scanner::add_exclude(const std::string& path) {
    m_excludes.push_back(path);
}

// Check if path starts with any excluded prefix
bool Scanner::is_excluded(const std::string& path) const {
    for (const auto& excl : m_excludes) {
        if (path.rfind(excl, 0) == 0) {
            return true;
        }
    }
    return false;
}

void Scanner::scan(const Matcher& matcher, Aggregator& aggregator) const {

    for (const auto& root : m_roots) {
        try {
            for (auto& entry : fs::recursive_directory_iterator(
                    root,
                    fs::directory_options::skip_permission_denied)) {

                const std::string path = entry.path().string();

                if (is_excluded(path)) {
                    continue;
                }

                if (matcher.matches(path)) {

                    std::uint64_t size = 0;
                    if (fs::is_regular_file(entry.path())) {
                        try {
                            size = fs::file_size(entry.path());
                        } catch (...) {
                            size = 0;
                        }
                    }

                    Category cat = classify_path(path);
                    aggregator.add_file(path, size, cat);
                }
            }
        } catch (const fs::filesystem_error&) {
            // skip inaccessible root
            continue;
        }
    }
}

} // namespace filer