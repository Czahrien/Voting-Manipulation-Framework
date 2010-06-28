#include "Plurality.h"

Plurality::Plurality( const set<string>& candidates ) : PositionalScoreElection( candidates ) {}

Plurality::Plurality( const set<string>& candidates, const multiset< RationalVote >& votes ) : PositionalScoreElection ( candidates, votes ) {}

int Plurality::position_score( int position ) const {
    return position != 0 ? 0 : 1;
}
