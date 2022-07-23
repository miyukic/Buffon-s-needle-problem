TARGET = bnp.out
CXX = clang++-14
OBJS = bs_needle_problems.o
CXXFLAGS = -Wall -Wextra -std=c++20 -I/usr/include/python3.10 -I$(HOME)/.local/lib/python3.10/site-packages/numpy/core/include -lpython3.10
LDFLAGS = 

#clang++-11 bs_needle_problem.cpp -I/usr/include/python3.8 -I$HOME/.local/lib/python3.8/site-packages/numpy/core/include -lpython3.8

DEBUG = -g -fsanitize=address -fsanitize=leak -O0

.PHONY: all
all: a.out Makefile

.PHONY: clean
clean:
	rm -rf *.o

.PHONY: debug
debug: Makefile
	$(CXX) $(CXXFLAGS) -O0 -g bs_needle_problem.cpp


a.out: bs_needle_problem.cpp Makefile
	$(CXX) $(CXXFLAGS) -O2 bs_needle_problem.cpp

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c bs_needle_problem.cpp
