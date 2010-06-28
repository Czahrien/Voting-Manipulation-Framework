#include "Borda.h"

Borda::Borda( const set<string>& candidates ) : PositionalScoreElection( candidates ) {}

Borda::Borda( const set<string>& candidates, const multiset< RationalVote >& votes ) : PositionalScoreElection ( candidates, votes ) {}

int Borda::position_score( int position ) const { 
    return candidates_.size() - position - 1;
}
