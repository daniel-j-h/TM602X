#ifndef TM602X_HPP
#define TM602X_HPP

#include <cstddef>
#include <array>
#include <string>

namespace TM602X {

template<typename T, std::size_t C, std::size_t R>
using Table = std::array<std::array<T, C>, R>;

template<typename T, std::size_t N>
using Alphabet = std::array<T, N>;

template<typename T, std::size_t N>
using Round = std::array<T, N>;


constexpr Table<int, 5, 7> firstTable = {{
  {{15, 15, 24, 20, 24}},
  {{13, 14, 27, 32, 10}},
  {{29, 14, 32, 29, 24}},
  {{23, 32, 24, 29, 29}},
  {{14, 29, 10, 21, 29}},
  {{4, 27, 16, 23, 30}},
  {{4, 22, 24, 17, 1}},
}};

constexpr Table<int, 10, 6> secondTable = {{
  {{0, 1, 2, 9, 3, 4, 5, 6, 7, 8}},
  {{1, 4, 3, 9, 0, 7, 8, 2, 5, 6}},
  {{7, 2, 8, 9, 4, 1, 6, 0, 3, 5}},
  {{6, 3, 5, 9, 1, 8, 2, 7, 4, 0}},
  {{4, 7, 0, 9, 5, 2, 3, 1, 8, 6}},
  {{5, 6, 1, 9, 8, 0, 4, 3, 2, 7}},
}};

constexpr Alphabet<char, 36> alphaTable = {{
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y', 'Z',
}};


// TODO: generate date automatically
struct Date {
  int year;       // last two digits
  int month;      // Jan. = 1
  int dayOfMonth; // day of month
  int dayOfWeek;  // Mon. = 0
};


class KeyGenerator {
  public:
    // change default seed; key is valid for date
    explicit KeyGenerator(Date date_, std::string seed_)
      : seed(seed_), date(date_) { }

    // use the default seed; key is valid for date
    explicit KeyGenerator(Date date_)
      : KeyGenerator(date_, "MPSJKMDHAI") { }

    // TODO: default constructor with date = today

    // generates the key based on seed and date
    std::string operator()();

  private:
    std::string seed;
    Date date;
};

}

#endif
