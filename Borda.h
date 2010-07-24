#ifndef BORDA_H_
#define BORDA_H_
#include "PositionalScoreElection.h"
using namespace std;
class Borda : public PositionalScoreElection {
    public:
        /**
         * Default constructor
         */
        Borda();
        /**
         * Constructs a Borda election with a set of candidates.
         *
         * @param candidates The set of candidates
         */
        Borda( const set<string>& candidates );
        /**
         * Constructs a Borda election with a set of candidates and votes.
         *
         * @param candidates The set of candidates
         * @param votes A multiset of RationalVotes
         */
        Borda( const set<string>& candidates, const multiset< RationalVote >& votes );
    public:
        /**
         * Obtains the point value of the given position.
         *
         * @param position The position to obtain the point value of.
         * @return the point value of position
         */
        int position_score( int position ) const;
};
#endif
