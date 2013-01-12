#include <iostream>

#include "TM602X.hpp"

using TM602X::KeyGenerator;
using TM602X::Date;

// example usage
int main() {
  KeyGenerator g{
    Date{13, 1, 12, 5}, // generate key for: 2013, Jan., 12th, Sat.
  };

  std::cout << g() << std::endl;
}
