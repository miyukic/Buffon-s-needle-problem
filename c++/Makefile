TARGET = bnp.out
CC = clang++-11
CXXFLAGS = -Wall -Wextra -std=c++20 -stdlib=libc++ -I/usr/include/python3.8 -I$HOME/.local/lib/python3.8/site-packages/numpy/core/include -lpython3.8

#clang++-11 bs_needle_problem.cpp -I/usr/include/python3.8 -I$HOME/.local/lib/python3.8/site-packages/numpy/core/include -lpython3.8

DEBUG = -g -c -fsanitize=address -fsanitize=leak

all:
	$(CC) $(CXXFLAGS) ./bs_needle_problem.cpp -o $(TARGET)

debug:
	$(CC) $(CXXFLAGS) $(DEBUG) ./bs_needle_problem.cpp
