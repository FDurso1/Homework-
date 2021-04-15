CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++11

cTrieTest : CTrieTest.o CTrie.o
	$(CXX) -o CTrieTest CTrie.o

CTrie.o : CTrie.cpp CTrie.h
	$(CXX) $(CXXFLAGS) -c CTrie.cpp -o CTrie.o
