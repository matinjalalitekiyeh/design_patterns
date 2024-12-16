#ifndef SINGLE_RESPONSIBLE_HXX
#define SINGLE_RESPONSIBLE_HXX

#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <fstream>

namespace solid {
struct Journal {
    std::string m_title;
    std::vector<std::string> m_entries;
    explicit
    Journal(std::string &&title) : m_title(std::move(title)) {}

    void add_new_entry(const std::string &new_entry) {
      static uint32_t counter = 1;
      m_entries.push_back(boost::lexical_cast<std::string>(counter++) + ") " + new_entry);
    }
};

struct persistence_manager {
  static void save(const std::string &&filename, const Journal &journal) {
      std::ofstream ofs(filename);
      ofs << '<' << journal.m_title << '>' << '\n';
      for (const auto& o : journal.m_entries)
        ofs << o << '\n';
  }
};
}

#endif // SINGLE_RESPONSIBLE_HXX
