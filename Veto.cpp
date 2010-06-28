#include "Veto.h"

Veto::Veto( const set<string>& candidates ) : PositionalScoreElection( candidates ) {}

Veto::Veto( const set<string>& candidates, const multiset< RationalVote >& votes ) : PositionalScoreElection ( candidates, votes ) {}

int Veto::position_score( int position ) const {
    return (unsigned int)position != candidates_.size() - 1 ? 1 : 0;
}
