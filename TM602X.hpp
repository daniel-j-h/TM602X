#ifndef TM602X_HPP
#define TM602X_HPP

#include <cstddef>
#include <array>
#include <string>

#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace TM602X {

template<std::size_t C, std::size_t R>
using Table = std::array<std::array<int, C>, R>;

template<std::size_t N>
using Alphabet = std::array<char, N>;

template<std::size_t N>
using Round = std::array<int, N>;

const Table<5, 7> firstTable = {{
  {{15, 15, 24, 20, 24}},
  {{13, 14, 27, 32, 10}},
  {{29, 14, 32, 29, 24}},
  {{23, 32, 24, 29, 29}},
  {{14, 29, 10, 21, 29}},
  {{34, 27, 16, 23, 30}},
  {{14, 22, 24, 17, 13}},
}};

const Table<10, 6> secondTable = {{
  {{0, 1, 2, 9, 3, 4, 5, 6, 7, 8}},
  {{1, 4, 3, 9, 0, 7, 8, 2, 5, 6}},
  {{7, 2, 8, 9, 4, 1, 6, 0, 3, 5}},
  {{6, 3, 5, 9, 1, 8, 2, 7, 4, 0}},
  {{4, 7, 0, 9, 5, 2, 3, 1, 8, 6}},
  {{5, 6, 1, 9, 8, 0, 4, 3, 2, 7}},
}};

const Alphabet<36> alphaTable = {{
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y', 'Z',
}};

class KeyGenerator final {
  public:
    // uses the default seed; key is valid for today
    explicit KeyGenerator()
      : KeyGenerator(boost::gregorian::day_clock::local_day()) { }

    // uses the default seed; key is valid for date
    explicit KeyGenerator(boost::gregorian::date date_)
      : KeyGenerator(date_, "MPSJKMDHAI") { }

    // uses specific seed; key is valid for date
    explicit KeyGenerator(boost::gregorian::date date_, std::string seed_)
      : seed(seed_), date(date_) { }

    // generates the key based on seed and date
    std::string operator()() const;

  private:
    std::string seed;
    boost::gregorian::date date;
};

}

#endif
