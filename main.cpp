#include <iostream>

#include "TM602X.hpp"

using TM602X::KeyGenerator;

// example usage
int main() {
  KeyGenerator g;

  std::cout << g() << std::endl;
}
