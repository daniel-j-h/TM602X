#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>

#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#include <boost/date_time/gregorian/gregorian.hpp>

#include "TM602X.hpp"

using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::exception;
using std::exit;

using boost::gregorian::date;
using boost::gregorian::day_clock;
using boost::gregorian::weeks;
using boost::gregorian::months;
using boost::gregorian::years;
using boost::gregorian::day_iterator;
using boost::gregorian::to_iso_extended_string;
using boost::gregorian::from_string;


// simple key generating console application
int main(int argc, char* argv[]) {
  vector<string> params{argv, argv + argc};

  // start today and end today unless specified otherwise
  date start{day_clock::local_day()};
  date end{start};

  // time period handling
  if(params.size() == 2) {
    if(params[1] == "-week")
      end = start + weeks{1};

    else if(params[1] == "-month")
      end = start + months{1};

    else if(params[1] == "-year")
      end = start + years{1};

    else {
      cerr << "Unknown argument" << endl;
      exit(EXIT_FAILURE);
    }
  }

  // specific date handling
  else if(params.size() == 3) {
    if(params[1] == "-day") {
      try {
        date specific{from_string(params[2])};

        start = specific;
        end = specific;
      } catch(const exception& e) {
        cerr << "Not a date" << endl;
        exit(EXIT_FAILURE);
      }
    }

    else {
      cerr << "Unknown argument" << endl;
      exit(EXIT_FAILURE);
    }
  }

  // generate keys for all given dates
  for(day_iterator it{start}; it <= end; ++it) {

    // $1 = ISO 8601, $2 = key
    cout << to_iso_extended_string(*it) << " " << TM602X::generateKey() << endl;
  }
}
