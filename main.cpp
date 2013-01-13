#include <iostream>
#include <string>
#include <vector>

#include "TM602X.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;

using TM602X::KeyGenerator;

using boost::gregorian::date;
using boost::gregorian::day_clock;
using boost::gregorian::weeks;
using boost::gregorian::months;
using boost::gregorian::years;
using boost::gregorian::day_iterator;


// simple key generating console application
int main(int argc, char* argv[]) {
  vector<string> params{argv, argv + argc};

  // start today and end today ..
  date start{day_clock::local_day()};
  date end{start};

  // .. unless specified otherwise
  if(params.size() == 2) {
    if(params[1] == "-week")
      end = start + weeks{1};

    else if(params[1] == "-month")
      end = start + months{1};

    else if(params[1] == "-year")
      end = start + years{1};
  }

  day_iterator it{start};

  for(; it <= end; ++it) {
    KeyGenerator g{*it};

    // $1 = ISO 8601, $2 = key
    cout << it->year() << "-" << it->month() << "-" << it->day() << " " << g() << endl;
  }
}
