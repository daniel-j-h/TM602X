#include <cmath>

#include <algorithm>
#include <numeric>

#include "TM602X.hpp"

namespace TM602X {

std::string KeyGenerator::operator()() {
  // round 1
  Round<int, 8> firstRound;

  for(auto i = 0; i <= 4; ++i)
    firstRound[i] = firstTable[date.dayOfWeek][i];

  firstRound[5] = date.dayOfMonth;

  if ((date.year + date.month - date.dayOfMonth) < 0)
    firstRound[6] = (date.year + date.month - date.dayOfMonth + 36) % 36;
  else
    firstRound[6] = (date.year + date.month - date.dayOfMonth) % 36;

  firstRound[7] = (((3 + ((date.year + date.month) % 12)) * date.dayOfMonth) % 37) % 36;

  // round 2
  Round<int, 8> secondRound;

  for(auto i = 0; i <= 7; ++i)
    secondRound[i] = (seed.substr(0, 8).substr(i, 1)[0]) % 36;

  // round 3
  Round<int, 10> thirdRound;

  for(auto i = 0; i <= 7; ++i)
    thirdRound[i] = (firstRound[i] + secondRound[i]) % 36;

  thirdRound[8] = std::accumulate(thirdRound.cbegin(), thirdRound.cbegin() + 8 , 0) % 36;
  thirdRound[9] = std::round(std::pow(thirdRound[8] % 6, 2));

  // round 4
  Round<int, 10> fourthRound;

  for(auto i = 0; i <= 9; ++i)
    fourthRound[i] = thirdRound[secondTable[thirdRound[8] % 6][i]];

  // round 5
  Round<int, 10> fifthRound;

  for(auto i = 0; i <= 9; ++i)
    fifthRound[i] = (seed.substr(i, 1)[0] + fourthRound[i]) % 36;

  // finalize
  std::string key;

  std::for_each(fifthRound.cbegin(), fifthRound.cend(), [&key](const int v){
    key += alphaTable[v];
  });

  return key;
}

}
