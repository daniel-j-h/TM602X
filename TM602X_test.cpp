#include <string>
#include <map>

#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#include <boost/date_time/gregorian/gregorian.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TM602X
#include <boost/test/unit_test.hpp>

#include "TM602X.hpp"

using std::string;
using std::map;

using boost::gregorian::date;
using boost::gregorian::Jan;
using boost::gregorian::Feb;


BOOST_AUTO_TEST_CASE(test_working) {
  map<date, string> kv{
    {date{2013, Jan, 11}, "4VRB4QHIPK"},
    {date{2013, Jan, 12}, "M6ARK8TPKO"},
    {date{2013, Jan, 13}, "O2A2MLEXLJ"},
  };

  for(auto p : kv)
    BOOST_CHECK_EQUAL(TM602X::generateKey(p.first), p.second);
}

BOOST_AUTO_TEST_CASE(test_past) {
  map<date, string> kv{
    {date{2010, Jan, 01}, "JTP6Z62JG7"},
    {date{2010, Feb, 01}, "BFYR2PNMS4"},
    {date{2012, Feb, 29}, "3F16URDYOZ"},
  };

  for(auto p : kv)
    BOOST_CHECK_EQUAL(TM602X::generateKey(p.first), p.second);
}

BOOST_AUTO_TEST_CASE(test_future) {
  map<date, string> kv{
    {date{2014, Jan, 01}, "BIXR23NV07"},
    {date{2015, Feb, 28}, "2TAR28TPK3"},
    {date{2016, Feb, 29}, "WAVI14INXM"},
  };

  for(auto p : kv)
    BOOST_CHECK_EQUAL(TM602X::generateKey(p.first), p.second);
}
