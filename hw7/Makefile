CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++11 -pedantic

#all: CTrieTest TTrieTest wordHunt

CTrieTest : CTrieTest.o CTrie.o
	$(CXX) $(CXXFLAGS) -o CTrieTest CTrieTest.o CTrie.o

CTrieTest.o: CTrieTest.cpp CTrie.h
	$(CXX) $(CXXFLAGS) -c CTrieTest.cpp

CTrie.o : CTrie.cpp CTrie.h 
	$(CXX) $(CXXFLAGS) -c CTrie.cpp

TTrieTest : TTrieTest.o
	$(CSS) $(CXXFLAGS) -o TTrieTest TTrieTest.o

TTrieTest.o : TTrieTest.cpp TTrie.h TTrie.inc
	$(CSS) $(CXXFLAGS) -c TTrieTest.cpp

clean:
	rm -f CTrieTest TTrieTest *.o
