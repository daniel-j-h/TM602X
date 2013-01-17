#ifndef TM602X_HPP
#define TM602X_HPP

#include <cstddef>
#include <array>
#include <string>

#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace TM602X {

template<std::size_t R, std::size_t C>
using Table = std::array<std::array<int, C>, R>;

template<std::size_t N>
using Alphabet = std::array<char, N>;

template<std::size_t N>
using Round = std::array<int, N>;


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
