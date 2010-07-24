OBJS = frontend.o Borda.o Plurality.o Veto.o PositionalScoreElection.o RationalElection.o RationalVote.o Vote.o CondorcetElection.o Countdown.o ScoringVector.o functions.o
CCC=g++
DEBUG = -ggdb
CXXFLAGS=-c -Wall $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: main
main: frontend.o Borda.o Plurality.o Veto.o PositionalScoreElection.o RationalElection.o RationalVote.o Vote.o CondorcetElection.o ScoringVector.o Countdown.o functions.o
	$(CXX) $(LFLAGS) $(OBJS) -o main
psetest.o: psetest.cpp Borda.h Plurality.h Veto.h
	$(CXX) $(CXXFLAGS) psetest.cpp
Borda.o: Borda.cpp Borda.h PositionalScoreElection.h
	$(CXX) $(CXXFLAGS) Borda.cpp
Plurality.o: Plurality.cpp Plurality.h PositionalScoreElection.h
	$(CXX) $(CXXFLAGS) Plurality.cpp
Veto.o: Veto.cpp Veto.h PositionalScoreElection.h
	$(CXX) $(CXXFLAGS) Veto.cpp
PositionalScoreElection.o: PositionalScoreElection.cpp PositionalScoreElection.h RationalVote.h RationalElection.h
	$(CXX) $(CXXFLAGS) PositionalScoreElection.cpp
RationalVote.o: RationalVote.cpp RationalVote.h Vote.o
	$(CXX) $(CXXFLAGS) RationalVote.cpp
Vote.o: Vote.cpp Vote.h
	$(CXX) $(CXXFLAGS) Vote.cpp
IrrationalVote.o: IrrationalVote.cpp IrrationalVote.h Vote.o
	$(CXX) $(CXXFLAGS) IrrationalVote.cpp
RationalElection.o: RationalElection.cpp RationalElection.h Election.h
	$(CXX) $(CXXFLAGS) RationalElection.cpp
CondorcetElection.o: CondorcetElection.cpp CondorcetElection.h RationalElection.o
	$(CXX) $(CXXFLAGS) CondorcetElection.cpp
ScoringVector.o: ScoringVector.cpp ScoringVector.h PositionalScoreElection.o
	$(CXX) $(CXXFLAGS) ScoringVector.cpp
Countdown.o: Countdown.cpp Countdown.h PositionalScoreElection.o
	$(CXX) $(CXXFLAGS) Countdown.cpp
functions.o: functions.cpp functions.h
	$(CXX) $(CXXFLAGS) functions.cpp
clean: 
	rm -rf *.o
realclean: clean
	rm -rf main
