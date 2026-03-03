#include "aggregator.hpp"

namespace filer {

void Aggregator::add_file(const std::string& path,
                          std::uint64_t size,
                          Category category)
{
    FileRecord record{path, size, category};
    m_files.push_back(record);

    m_total_files += 1;
    m_total_size += size;

    auto& stats = m_category_stats[category];
    stats.file_count += 1;
    stats.total_size += size;
}

std::uint64_t Aggregator::total_files() const {
    return m_total_files;
}

std::uint64_t Aggregator::total_size() const {
    return m_total_size;
}

const std::unordered_map<Category, Stats>&
Aggregator::category_stats() const {
    return m_category_stats;
}

const std::vector<FileRecord>&
Aggregator::files() const {
    return m_files;
}

} // namespace filer