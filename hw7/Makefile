CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++11 -pedantic

#all: CTrieTest TTrieTest wordHunt

CTrieTest : CTrieTest.o CTrie.o
	$(CXX) $(CXXFLAGS) -o CTrieTest CTrieTest.o CTrie.o

CTrieTest.o: CTrieTest.cpp CTrie.h
	$(CXX) $(CXXFLAGS) -c CTrieTest.cpp

CTrie.o : CTrie.cpp CTrie.h
	$(CXX) $(CXXFLAGS) -c CTrie.cpp

clean:
	rm -f CTrieTest tTrieTest
