#include "Countdown.h"

// Countdown - default constructor
Countdown::Countdown() : PositionalScoreElection() {}

// Countdown
Countdown::Countdown( const set<string>& candidates ) : PositionalScoreElection( candidates ) {}

// Countdown
Countdown::Countdown( const set<string>& candidates, const multiset< RationalVote >& votes ) : PositionalScoreElection ( candidates, votes ) {}

// change_countdown
void Countdown::change_countdown( int n ) {
    if( n >= 1 ) { 
        countdown_start_ = n;
        clear_scores();
    }
}

// get_countdown
int Countdown::get_countdown() const {
    return countdown_start_;
}

// position_score
int Countdown::position_score( int position ) const {
    if( position < countdown_start_ ) {
        return countdown_start_ - position;
    }
    else {
        return 0;
    }
}

