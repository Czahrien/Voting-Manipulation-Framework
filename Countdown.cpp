#include "Countdown.h"

Countdown::Countdown( const set<string>& candidates ) : PositionalScoreElection( candidates ) {}

Countdown::Countdown( const set<string>& candidates, const multiset< RationalVote >& votes ) : PositionalScoreElection ( candidates, votes ) {}

void Countdown::change_countdown( int n ) {
    if( n >= 1 ) { 
        countdown_start_ = n;
    }
}

int Countdown::get_countdown( int n ) const {
    return countdown_start_;
}


int Countdown::position_score( int position ) const {
    if( position < countdown_start_ ) {
        return countdown_start_ - position;
    }
    else {
        return 0;
    }
}

