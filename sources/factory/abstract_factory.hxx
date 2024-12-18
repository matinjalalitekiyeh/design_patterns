#ifndef ABSTRACT_FACTORY_HXX
#define ABSTRACT_FACTORY_HXX

namespace factory {

struct Hot_drink {
    virtual void prepare(int volume) = 0;
};

struct Tea : public Hot_drink {
  void prepare(int volume) override {

  }
};

struct Coffee : public Hot_drink {
  void prepare(int volume) override {

  }
};


}

#endif // ABSTRACT_FACTORY_HXX
