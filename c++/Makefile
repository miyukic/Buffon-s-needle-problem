TARGET = bnp.out
CC = clang++-11
CXXFLAGS = -Wall -Wextra -std=c++20 -stdlib=libc++ -o bnp.out
DEBUG = -g -c -fsanitize=address -fsanitize=leak

all:
	$(CC) $(CFLAGS) ./bs_needle_problem.cpp

debug:
	$(CC) $(CFLAGS) $(DEBUG) ./bs_needle_problem.cpp
