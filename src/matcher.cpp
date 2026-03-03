#include "matcher.hpp"
#include <algorithm>
#include <stdexcept>

namespace filer {

Matcher::Matcher(const std::string& pattern, MatchMode mode, bool case_insensitive)
    : m_pattern(pattern), m_mode(mode), m_case_insensitive(case_insensitive)
{
    std::string regex_pattern;

    switch (m_mode) {
        case MatchMode::Substring:
            m_use_regex = false;
            break;
        case MatchMode::Wildcard:
            regex_pattern = wildcard_to_regex(pattern);
            m_regex = std::regex(regex_pattern,
                        case_insensitive ? std::regex_constants::icase : std::regex_constants::ECMAScript);
            m_use_regex = true;
            break;
        case MatchMode::Regex:
            m_regex = std::regex(pattern,
                        case_insensitive ? std::regex_constants::icase : std::regex_constants::ECMAScript);
            m_use_regex = true;
            break;
        default:
            throw std::invalid_argument("Unknown match mode");
    }
}

// Convert wildcard (* and ?) to regex
std::string Matcher::wildcard_to_regex(const std::string& pattern) const {
    std::string result;
    result += "^";
    for (char c : pattern) {
        switch (c) {
            case '*': result += ".*"; break;
            case '?': result += "."; break;
            case '.': result += "\\."; break;
            case '\\': result += "\\\\"; break;
            default: result += c; break;
        }
    }
    result += "$";
    return result;
}

std::string Matcher::to_lower(const std::string& str) const {
    std::string copy = str;
    std::transform(copy.begin(), copy.end(), copy.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return copy;
}

bool Matcher::matches(const std::string& path) const {
    if (m_use_regex) {
        return std::regex_search(path, m_regex);
    } else {
        if (m_case_insensitive) {
            return to_lower(path).find(to_lower(m_pattern)) != std::string::npos;
        } else {
            return path.find(m_pattern) != std::string::npos;
        }
    }
}

} // namespace filer