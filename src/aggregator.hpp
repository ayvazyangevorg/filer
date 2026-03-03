#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>

#include "classifier.hpp"

namespace filer {

struct FileRecord {
    std::string path;
    std::uint64_t size;
    Category category;
};

struct Stats {
    std::uint64_t file_count = 0;
    std::uint64_t total_size = 0;
};

class Aggregator {
public:
    void add_file(const std::string& path,
                  std::uint64_t size,
                  Category category);

    std::uint64_t total_files() const;
    std::uint64_t total_size() const;

    const std::unordered_map<Category, Stats>& category_stats() const;
    const std::vector<FileRecord>& files() const;

private:
    std::vector<FileRecord> m_files;
    std::unordered_map<Category, Stats> m_category_stats;

    std::uint64_t m_total_files = 0;
    std::uint64_t m_total_size = 0;
};

} // namespace filer