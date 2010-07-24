#include "Borda.h"

// Borda - default constructor
Borda::Borda() : PositionalScoreElection() {}

// Borda
Borda::Borda( const set<string>& candidates ) : PositionalScoreElection( candidates ) {}

// Borda
Borda::Borda( const set<string>& candidates, const multiset< RationalVote >& votes ) : PositionalScoreElection ( candidates, votes ) {}

// position_score
int Borda::position_score( int position ) const { 
    return candidates_.size() - position - 1;
}
