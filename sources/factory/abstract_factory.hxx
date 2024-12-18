#ifndef ABSTRACT_FACTORY_HXX
#define ABSTRACT_FACTORY_HXX

#include <iostream>
#include <memory>
#include <map>
#include <functional>

namespace factory {

struct Hot_drink {
    virtual void prepare(int volume) = 0;
};

struct Tea : public Hot_drink {
  void prepare(int volume) override {
    std::cout << "Take tea bag, boil water, pour "
                      << volume << "ml, add some lemon" << std::endl;
  }
};

struct Coffee : public Hot_drink {
  void prepare(int volume) override {
    std::cout << "Grind some beans, boil water, pour "
              << volume << "ml, add cream, enjoy!" << std::endl;
  }
};

struct Hot_drink_factory {
  virtual std::unique_ptr<Hot_drink> make() const = 0;
};

struct Tea_factory : public Hot_drink_factory {
  std::unique_ptr<Hot_drink> make() const override {
    return std::make_unique<Tea>();
  }
};

struct Coffee_factory : public Hot_drink_factory {
  std::unique_ptr<Hot_drink> make() const override {
    return std::make_unique<Coffee>();
  }
};

struct Drink_factory {
  std::map<std::string, std::unique_ptr<Hot_drink_factory>> m_factory;
  Drink_factory() {
    m_factory["Tea"] = std::make_unique<Tea_factory>();
    m_factory["Coffee"] = std::make_unique<Coffee_factory>();
  }
  std::unique_ptr<Hot_drink> create(const std::string &&name) {
    return m_factory[name]->make();
  }
};

struct Drink_factory_functional {
  std::map<std::string, std::function<std::unique_ptr<Hot_drink_factory>()>> m_factory;
  Drink_factory_functional() {
    m_factory["Tea"] = [](){
      auto drink = std::make_unique<Tea_factory>();
      drink->make()->prepare(200);
      return drink;
    };
    m_factory["Coffee"] = [](){
      auto drink = std::make_unique<Tea_factory>();
      drink->make()->prepare(150);
      return drink;
    };
  }

  void create(const std::string &&name) {
    m_factory[name]();
  }
};

}

#endif // ABSTRACT_FACTORY_HXX
