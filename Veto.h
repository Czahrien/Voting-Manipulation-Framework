#ifndef VETO_H_
#define VETO_H_
#include "PositionalScoreElection.h"
using namespace std;
class Veto : public PositionalScoreElection {
    public:
        /**
         * Default constructor
         */
        Veto();
        /**
         * Constructs a Veto election from a set of candidates.
         *
         * @param candidates The set of candidates.
         */
        Veto( const set<string>& candidates );
        /**
         * Constructs a Veto election from a set of candidates and votes.
         *
         * @param candidates The set of candidates.
         * @param votes A multiset of RationalVotes
         */
        Veto( const set<string>& candidates, const multiset< RationalVote >& votes );
    public:
        /**
         * Obtains the point value of the score of the specified position.
         *
         * @param position The position.
         * @return The point value of the given position.
         */
        int position_score( int position ) const;
};
#endif
