#ifndef OPEN_CLOSE_HXX
#define OPEN_CLOSE_HXX

#include <string>
#include <vector>

namespace solid {
enum class Color {red, blue, green};
enum class Size  {large, medium, small};
struct Product {
    std::string name;
    Color color;
    Size size;
};

template<typename T>
struct And_specification;

template<typename T>
struct Specification {
    virtual bool is_satisfied(T *item) = 0;
    virtual ~Specification() = default;
};

template<typename T>
struct Filter {
    virtual std::vector<T*> filter(std::vector<T*>& items,
                                   Specification<T>& spec) = 0;
};

struct Product_filter : public Filter<Product> {
    std::vector<Product*> filter(std::vector<Product*> &items,
                                 Specification<Product> &spec) override {
        std::vector<Product*> ret_val;
        for (auto& o : items)
            if (spec.is_satisfied(o))
                ret_val.push_back(o);
        return ret_val;
    }
};

struct By_color : public Specification<Product> {
    Color m_color;
    By_color(Color color) : m_color(color) {}
    bool is_satisfied(Product *item) override {
        return m_color == item->color;
    }
};

struct By_size : public Specification<Product> {
    Size m_size;
    By_size(Size size) : m_size(size) {}
    bool is_satisfied(Product *item) override {
        return m_size == item->size;
    }
};

template<typename T>
struct And_specification : Specification<T> {
    Specification<T>& m_first;
    Specification<T>& m_second;
    explicit And_specification(Specification<T>& first, Specification<T>& second)
        : m_first(first), m_second(second) {}

    bool is_satisfied(T *item) override {
        return m_first.is_satisfied(item) && m_second.is_satisfied(item);
    }
};





}

#endif // OPEN_CLOSE_HXX
