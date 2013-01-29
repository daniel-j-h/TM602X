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


// uses the default seed; key is valid for today
std::string generateKey();

// uses the default seed; key is valid for date
std::string generateKey(boost::gregorian::date);

// uses specific seed; key is valid for date
std::string generateKey(boost::gregorian::date, std::string);

}

#endif
