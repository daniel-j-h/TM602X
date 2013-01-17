TM602X
======


Description
-----------

Simple application to generate the login "password of the day" for the Arris TM602X telephony modem family.


Dependencies
------------

* Boost Date Time library for specific date handling.
* Boost Test library for unit tests.


Building
--------

Requires a decent C++11 compiler (e.g. clang-3.1 with libc++, or g++-4.7 with stdlibc++).  

    export CXX="g++-4.7" CXXFLAGS="-std=c++11"
    make


Usage
-----

For the password of the day, just run:

    ./tm602x-key

Generate keys for a specific time period:

    ./tm602x-key -week
    ./tm602x-key -month
    ./tm602x-key -year

If you want to generate passwords for a specific day, pass in the delimited date:

    ./tm602x-key -day 2013-01-13

For reasons of simple environment integration, the output is formatted as:

    <ISO 8601> <key>

    2013-01-13 XXXXXXXXXX


Notes
-----

This is only a simple command line application; for the original Javascript version by Raúl Pedro Santos see:
https://github.com/borfast/arrispwgen
