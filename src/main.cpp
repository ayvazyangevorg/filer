#include "scanner.hpp"
#include "matcher.hpp"
#include "aggregator.hpp"
#include "classifier.hpp"

#include <iostream>
#include <iomanip>
#include <map>

using namespace filer;

// Convert bytes to human-readable string
std::string human_readable(std::uint64_t bytes) {
    constexpr const char* units[] = {"B","KB","MB","GB","TB"};
    double size = static_cast<double>(bytes);
    int unit = 0;
    while (size >= 1024 && unit < 4) {
        size /= 1024;
        ++unit;
    }
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << size << " " << units[unit];
    return oss.str();
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: filer <pattern>\n";
        return 1;
    }

    std::string pattern = argv[1];
    Matcher matcher(pattern, MatchMode::Substring, true);
    Aggregator aggregator;
    Scanner scanner;

    // Add roots
    scanner.add_root("/usr");
    scanner.add_root("/etc");
    scanner.add_root("/var");
    scanner.add_root("/opt");
    scanner.add_root("/home");

    // Add exclusions
    scanner.add_exclude("/proc");
    scanner.add_exclude("/sys");
    scanner.add_exclude("/dev");
    scanner.add_exclude("/run");

    std::cout << "Scanning for pattern: " << pattern << " ...\n\n";

    scanner.scan(matcher, aggregator);

    // Group files by category
    std::map<Category, std::vector<FileRecord>> grouped;
    for (const auto& f : aggregator.files()) {
        grouped[f.category].push_back(f);
    }

    // Print grouped results
    for (const auto& [cat, files] : grouped) {
        std::cout << "[" << category_to_string(cat) << "]\n";
        for (const auto& f : files) {
            std::cout << "  " << f.path << " (" << human_readable(f.size) << ")\n";
        }
        std::uint64_t cat_size = 0;
        for (const auto& f : files) cat_size += f.size;
        std::cout << "  -> Total: " << files.size()
                  << " files, " << human_readable(cat_size) << "\n\n";
    }

    std::cout << "=================================\n";
    std::cout << "TOTAL FILES: " << aggregator.total_files()
              << ", TOTAL SIZE: " << human_readable(aggregator.total_size()) << "\n";

    return 0;
}