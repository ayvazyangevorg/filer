#pragma once

#include <string>
#include <regex>

namespace filer {

enum class MatchMode {
    Substring,
    Wildcard,
    Regex
};

class Matcher {
public:
    Matcher(const std::string& pattern, MatchMode mode = MatchMode::Substring, bool case_insensitive = true);

    bool matches(const std::string& path) const;

private:
    std::string m_pattern;
    MatchMode m_mode;
    bool m_case_insensitive;

    std::regex m_regex;
    bool m_use_regex = false;

    std::string wildcard_to_regex(const std::string& pattern) const;
    std::string to_lower(const std::string& str) const;
};

} // namespace filer