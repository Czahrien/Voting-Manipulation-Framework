#ifndef PLURALITY_H_
#define PLURALITY_H_
#include "PositionalScoreElection.h"
using namespace std;
class Plurality : public PositionalScoreElection {
    public:
        /**
         * Default constructor
         */
        Plurality();
        /**
         * Constructs a Plurality election from a set of candidates.
         *
         * @param candidates The set of candidates.
         */
        Plurality( const set<string>& candidates );
        /**
         * Constructs a Plurality election from a set of candidates and votes.
         *
         * @param candidates The set of candidates.
         * @param votes A multiset of RationalVotes
         */
        Plurality( const set<string>& candidates, const multiset< RationalVote >& votes );
    public:
        /**
         * Obtains the point value of a candidate in the given position of a vote.
         *
         * @param position The position
         * @return The score of the given position.
         */
        int position_score( int position ) const;
};
#endif
