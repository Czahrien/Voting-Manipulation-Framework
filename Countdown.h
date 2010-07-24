#ifndef COUNTDOWN_H_
#define COUNTDOWN_H_
#include "PositionalScoreElection.h"
using namespace std;
class Countdown : public PositionalScoreElection {
    public:
        /**
         * Default Constructor
         */
        Countdown();
        /**
         * Countdown constructor that takes the set of candidates.
         *
         * @param candidates The set of candidates.
         */
        Countdown( const set<string>& candidates );
        /**
         * Countdown constructor that takes the set of candidates and a set of votes.
         *
         * @param candidates The set of candidates.
         * @param votes The set of votes.
         */
        Countdown( const set<string>& candidates, const multiset< RationalVote >& votes );
    public:
        /**
         * Changes the countdown to count down from n.
         *
         * @param n The score of the highest ranked candidate in a vote.
         */
        void change_countdown( int n );
        /**
         * Obtains the number this Countdown election starts from.
         *
         * @return The score of the highest ranked candidate in a vote.
         */
        int get_countdown() const;
        /**
         * Obtains the score at the given position.
         * 
         * @param position The position to obtain the score of.
         * @return The score at that given position.
         */
        int position_score( int position ) const;
protected:
    int countdown_start_;
};
#endif
