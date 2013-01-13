# TM602X password of the day generator.
# Requires decent C++11 compiler support.
# Feel free to adapt this Makefile to your needs.
CXX        ?= clang++
CXXFLAGS   ?= -std=c++11 -stdlib=libc++ -fcatch-undefined-behavior -Wall -Wextra -O2
LDFLAGS    = -lboost_date_time
TARGET     = tm602x-key


$(TARGET): main.o TM602X.o
	$(CXX) $(LDFLAGS) $(CXXFLAGS) main.o TM602X.o -o $(TARGET)

main.o: main.cpp TM602X.cpp TM602X.hpp
	$(CXX) $(CXXFLAGS) -c $<

TM602X.o: TM602X.cpp TM602X.hpp
	$(CXX) $(CXXFLAGS) -c $<


clean:
	rm -f *.o $(TARGET)
