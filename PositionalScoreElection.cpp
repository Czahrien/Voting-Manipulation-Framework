#include <iostream>
#include "PositionalScoreElection.h"

PositionalScoreElection::PositionalScoreElection() : RationalElection() {
    init();
}

PositionalScoreElection::PositionalScoreElection( const set<string>& candidates ) : RationalElection( candidates ) {
    init();
}

PositionalScoreElection::PositionalScoreElection( const set<string>& candidates, const multiset< RationalVote >& votes ) :RationalElection( candidates, votes ) {
    init();
}
        
/*void PositionalScoreElection::init() {
    
    is_valid_ = validate_votes();
    if( is_valid_ ) {
        //count_votes();
    }
    else {
        cerr << "Invalid election.\n";
    }
}*/

void PositionalScoreElection::count_vote( const RationalVote& vote ) {
    //if( current_scores_.size() != candidates_.size() ) {
        // error condition.
    //    cerr << "Error counting the vote.\n";
    //} else if ( !validate_vote( vote ) ) {
    //    cerr << "Vote is invalid.\n";
    //} else if( !votes_counted_ ) {
    //    count_votes(); // TODO - Is this an issue? 
    //} else {
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

map<string,int> PositionalScoreElection::get_vote_count() const {
    //TODO: add error checks
    return current_scores_;
}

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

void PositionalScoreElection::clear_scores() {
    current_scores_.clear();
    set<string>::iterator i = candidates_.begin();
    
    while( i != candidates_.end() ) {
        current_scores_[*i] = 0;
        ++i;
    }
}
