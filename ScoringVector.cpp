#include "ScoringVector.h"

// ScoringVector - default constructor
ScoringVector::ScoringVector() : PositionalScoreElection() {}

// ScoringVector
ScoringVector::ScoringVector( const set<string>& candidates ) : PositionalScoreElection( candidates ) {}

// ScoringVector
ScoringVector::ScoringVector( const set<string>& candidates, const multiset< RationalVote >& votes ) : PositionalScoreElection ( candidates, votes ) {}

// set_scoring_vector
void ScoringVector::set_scoring_vector( vector<int> scoring_vector ) {
    // sort the numbers
    multiset<int> temp( scoring_vector.begin(), scoring_vector.end() );
    scoring_vector_.clear();
    // reverse the sort
    scoring_vector_ = vector<int>( temp.rbegin(), temp.rend() );
    clear_scores();
}

// get_scoring_vector
vector<int> ScoringVector::get_scoring_vector() const {
    return scoring_vector_;
}

// position_score
int ScoringVector::position_score( int position ) const {
    if( position >= scoring_vector_.size() || position < 0 ) {
        return 0;
    } else {
        return scoring_vector_[position];
    }
}

