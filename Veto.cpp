#include "Veto.h"

// Veto - default constructor
Veto::Veto() : PositionalScoreElection() {}

// Veto
Veto::Veto( const set<string>& candidates ) : PositionalScoreElection( candidates ) {}

// Veto
Veto::Veto( const set<string>& candidates, const multiset< RationalVote >& votes ) : PositionalScoreElection ( candidates, votes ) {}

// position_score
int Veto::position_score( int position ) const {
    return (unsigned int)position != candidates_.size() - 1 ? 1 : 0;
}
