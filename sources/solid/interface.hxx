#ifndef INTERFACE_HXX
#define INTERFACE_HXX

#include <string>

namespace solid {

struct Ifax  { virtual std::string fax()   = 0; };
struct Iscan { virtual std::string scan()  = 0; };
struct Iprint{ virtual std::string print() = 0; };

struct Imachine : public Iprint, public Ifax {};

struct machine : public Imachine {
  std::string fax()    override { return "Fax"; }
  std::string print()  override { return "Print"; }
};

}

#endif // INTERFACE_HXX


