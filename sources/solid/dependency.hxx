#ifndef DEPENDENCY_HXX
#define DEPENDENCY_HXX

#include <vector>
#include <string>
#include <tuple>

namespace solid {

enum class Relations {parent, child, sibling};
struct Person {
  std::string name;
};

struct Relationship {
  std::vector<std::tuple<Person, Relations, Person>> m_relations;
  void add_new_parent(Person &parent, Person &child) {
    m_relations.push_back({parent, Relations::parent, child});
    m_relations.push_back({child, Relations::child, parent});
  }
};

struct Research_relations {
  Research_relations() { }

  std::vector<std::string> search(Relationship &rs, const std::string &&parent_name) {
    std::vector<std::string> names;
    for (auto [first, rel, second] : rs.m_relations) {
      if (first.name==parent_name, rel == Relations::parent)
        names.push_back(second.name);
    }
    return names;
  }
};

}

#endif // DEPENDENCY_HXX
