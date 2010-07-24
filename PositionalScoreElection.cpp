#include <iostream>
#include "PositionalScoreElection.h"

// PositionalScoreElection - default constructor
PositionalScoreElection::PositionalScoreElection() : RationalElection() {
    init();
}

// PositionalScoreElection
PositionalScoreElection::PositionalScoreElection( const set<string>& candidates ) : RationalElection( candidates ) {
    init();
}

// PositionalScoreElection
PositionalScoreElection::PositionalScoreElection( const set<string>& candidates, const multiset< RationalVote >& votes ) :RationalElection( candidates, votes ) {
    init();
}

// count_vote
void PositionalScoreElection::count_vote( const RationalVote& vote ) {
    vector<string> v = vote.get_preference_order();
    vector<string>::const_iterator k = v.begin();
    int n = 0;
    while( k != v.end() ) {
        const string& c = *k;
        if( candidates_.find( c ) != candidates_.end() ) {
            current_scores_[c] += position_score( n++ );
        }
        k++;
    }
}

// uncount_vote
void PositionalScoreElection::uncount_vote( const RationalVote& vote ) {
    vector<string> v = vote.get_preference_order();
    vector<string>::const_iterator k = v.begin();
    int n = 0;
    while( k != v.end() ) {
        const string& c = *k;
        if( candidates_.find( c ) != candidates_.end() ) {
            current_scores_[c] -= position_score( n++ );
        }
        k++;
    }   
}

// get_winners
set<string> PositionalScoreElection::get_winners() const {
    map<string,int>::const_iterator i = current_scores_.begin();
    int max_score = 0;
    set<string> win;

    while( i != current_scores_.end() ) {
        if( i->second > max_score ) {
            max_score = i->second;
            win.erase( win.begin(), win.end() );
            win.insert( i->first );
        }
        else if( i->second == max_score ) {
            win.insert( i->first );
        }
        i++;
    }

    return win;
}

// get_vote_count
map<string,int> PositionalScoreElection::get_vote_count() const {
    return current_scores_;
}

// beats
set<string> PositionalScoreElection::beats( const string& candidate ) const {
    map<string,int>::const_iterator i = current_scores_.find( candidate );
    if( i != current_scores_.end() ) { 
        int threshold = i->second;
        i = current_scores_.begin();
        set<string> losers;
        
        while( i != current_scores_.end() ) {
            if( i->second < threshold ) {
                losers.insert( i->first );
            }
            i++;
        }
        return losers;
    }
    else 
        return set<string>();
}

// clear_scores
void PositionalScoreElection::clear_scores() {
    current_scores_.clear();
    set<string>::iterator i = candidates_.begin();
    
    while( i != candidates_.end() ) {
        current_scores_[*i] = 0;
        ++i;
    }
}
