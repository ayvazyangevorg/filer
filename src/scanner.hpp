#pragma once

#include <string>
#include <vector>
#include "matcher.hpp"
#include "aggregator.hpp"
#include "classifier.hpp"

namespace filer {

class Scanner {
public:
    Scanner();

    void add_root(const std::string& path);  // directories to scan
    void add_exclude(const std::string& path); // directories to skip

    void scan(const Matcher& matcher, Aggregator& aggregator) const;

private:
    std::vector<std::string> m_roots;
    std::vector<std::string> m_excludes;

    bool is_excluded(const std::string& path) const;
};

} // namespace filer