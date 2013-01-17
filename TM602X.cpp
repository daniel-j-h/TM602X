#include <cmath>

#include <algorithm>
#include <numeric>

#include "TM602X.hpp"

namespace TM602X {

static const Table<7, 5> firstTable = {{
  {{15, 15, 24, 20, 24}},
  {{13, 14, 27, 32, 10}},
  {{29, 14, 32, 29, 24}},
  {{23, 32, 24, 29, 29}},
  {{14, 29, 10, 21, 29}},
  {{34, 27, 16, 23, 30}},
  {{14, 22, 24, 17, 13}},
}};

static const Table<6, 10> secondTable = {{
  {{0, 1, 2, 9, 3, 4, 5, 6, 7, 8}},
  {{1, 4, 3, 9, 0, 7, 8, 2, 5, 6}},
  {{7, 2, 8, 9, 4, 1, 6, 0, 3, 5}},
  {{6, 3, 5, 9, 1, 8, 2, 7, 4, 0}},
  {{4, 7, 0, 9, 5, 2, 3, 1, 8, 6}},
  {{5, 6, 1, 9, 8, 0, 4, 3, 2, 7}},
}};

static const Alphabet<36> alphaTable = {{
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X', 'Y', 'Z',
}};

std::string KeyGenerator::operator()() const {
  // year           last two digits
  // month          Jan = 1
  // dayOfMonth     -
  // dayOfWeek      Mon = 0
  auto year = date.year() % 100;
  auto month = date.month();
  auto dayOfMonth = date.day();
  auto dayOfWeek = (date.day_of_week() == 0) ? 6 : date.day_of_week() - 1;

  // round 1
  Round<8> firstRound;

  for(auto i = 0; i <= 4; ++i)
    firstRound[i] = firstTable[dayOfWeek][i];

  firstRound[5] = dayOfMonth;

  if ((year + month - dayOfMonth) < 0)
    firstRound[6] = (year + month - dayOfMonth + 36) % 36;
  else
    firstRound[6] = (year + month - dayOfMonth) % 36;

  firstRound[7] = (((3 + ((year + month) % 12)) * dayOfMonth) % 37) % 36;

  // round 2
  Round<8> secondRound;

  for(auto i = 0; i <= 7; ++i)
    secondRound[i] = (seed.substr(0, 8).substr(i, 1)[0]) % 36;

  // round 3
  Round<10> thirdRound;

  for(auto i = 0; i <= 7; ++i)
    thirdRound[i] = (firstRound[i] + secondRound[i]) % 36;

  thirdRound[8] = std::accumulate(thirdRound.cbegin(), thirdRound.cbegin() + 8, 0) % 36;
  thirdRound[9] = std::round(std::pow(thirdRound[8] % 6, 2));

  // round 4
  Round<10> fourthRound;

  for(auto i = 0; i <= 9; ++i)
    fourthRound[i] = thirdRound[secondTable[thirdRound[8] % 6][i]];

  // round 5
  Round<10> fifthRound;

  for(auto i = 0; i <= 9; ++i)
    fifthRound[i] = (seed.substr(i, 1)[0] + fourthRound[i]) % 36;

  // finalize
  std::string key;

  for(const auto v : fifthRound)
    key += alphaTable[v];

  return key;
}

}
