TM602X
======
[![Build Status](https://secure.travis-ci.org/daniel-j-h/TM602X.png)](http://travis-ci.org/daniel-j-h/TM602X)


Description
-----------

Simple library / application to generate the login "password of the day" for the Arris TM602X telephony modem family.


Building
--------

Requires a decent C++11 compiler (e.g. clang-3.1 with libc++).  
Uses the Boost Date Time library (headers only) for specific date handling, so you have to initialize the submodule:

    git clone --recursive git://github.com/daniel-j-h/TM602X.git
    make


Usage
-----

For the password of the day, just run:

    ./tm602x-key

Generate keys for a specific time period:

    ./tm602x-key -week
    ./tm602x-key -month
    ./tm602x-key -year

For reasons of simple environment integration, the output is formatted as:

    <ISO 8601> <key>

    2013-1-13 XXXXXXXXXX

If you want to generate passwords for other days, you have two simple options:

* pass a specific boost::gregorian::date to the constructor
* build the Boost Date Time library and use boost::gregorian::from_string() to parse your input


Notes
-----

This is only a simple command line application; for the original Javascript version by Raúl Pedro Santos see:
https://github.com/borfast/arrispwgen
