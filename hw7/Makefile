CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++11 -pedantic

#all: CTrieTest TTrieTest wordHunt

wordHunt : wordHuntMain.o CTrie.o WordHunt.o
	$(CXX) $(CXXFLAGS) -o wordHunt wordHuntMain.o CTrie.o WordHunt.o

wordHunt.o : wordHunt.cpp WordHunt.h
	$(CXX) $(CXXFLAGS) -c wordHunt.cpp

wordHuntMain.o : wordHuntMain.cpp WordHunt.h CTrie.h
	$(CXX) $(CXXFLAGS) -c wordHuntMain.cpp

CTrieTest : CTrieTest.o CTrie.o
	$(CXX) $(CXXFLAGS) -o CTrieTest CTrieTest.o CTrie.o

CTrieTest.o: CTrieTest.cpp CTrie.h
	$(CXX) $(CXXFLAGS) -c CTrieTest.cpp

CTrie.o : CTrie.cpp CTrie.h 
	$(CXX) $(CXXFLAGS) -c CTrie.cpp

TTrieTest : TTrieTest.o
	$(CXX) $(CXXFLAGS) -o TTrieTest TTrieTest.o

TTrieTest.o : TTrieTest.cpp TTrie.h TTrie.inc
	$(CXX) $(CXXFLAGS) -c TTrieTest.cpp

clean:
	rm -f CTrieTest TTrieTest wordHunt *.o
