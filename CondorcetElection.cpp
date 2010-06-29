/*
 *  CondorcetElection.cpp
 *  VMF
 *
 *  Created by bdm on 6/22/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */

#include <iostream>
#include "CondorcetElection.h"

CondorcetElection::CondorcetElection() : RationalElection(), current_scores_() {
    init();
}
CondorcetElection::CondorcetElection( const set<string>& candidates ) : RationalElection( candidates ), current_scores_() {
    init();
}
CondorcetElection::CondorcetElection( const set<string>& candidates, const multiset< RationalVote >& votes ) : RationalElection( candidates, votes ), current_scores_() {
    init();
}
set<string> CondorcetElection::get_winners() const {
//Note that the winner in a Condorcet election is the candidate that beats all other candidates
    set<string> ret;
    set<string>::const_iterator i = candidates_.begin();
    while( i != candidates_.end() && ret.size() == 0 ) {
        if( beats( *i ).size() == candidates_.size() - 1 ) {
            ret.insert( *i );        
        }
        ++i;
    }
    return ret;
}
map<pair<string,string>,int> CondorcetElection::get_vote_count() const {
    return current_scores_;
}
set<string> CondorcetElection::beats( const string& candidate ) const {
    set<string> losers;
    if( candidates_.find( candidate ) != candidates_.end() ) {
        set<string>::const_iterator i = candidates_.begin();
        while( i != candidates_.end() ) {
            if( *i != candidate ) {
                pair<string,string> win( candidate, *i );
                pair<string,string> lose(*i, candidate );
                if( current_scores_.find(win)->second > current_scores_.find(lose)->second ) {
                    losers.insert( *i );
                }
                ++i;
            }
        }
    }
    return losers;
}
void CondorcetElection::count_vote( const RationalVote& vote ) {
    vector<string> v = vote.get_preference_order();
    vector<string>::iterator i = v.begin(), j = i;
    while( i != v.end() && ++j != v.end() ) {
        while( j != v.end() ) {
            pair<string,string> point( *i, *j );
            current_scores_[point]++;
            ++j;
        }
        ++i;
        j = i;
    }
}
void CondorcetElection::uncount_vote( const RationalVote& vote ) {
    vector<string> v = vote.get_preference_order();
    vector<string>::iterator i = v.begin(), j = i;
    while( i != v.end() && ++j != v.end() ) {
        while( j != v.end() ) {
            pair<string,string> point( *i, *j );
            current_scores_[point]--;
            ++j;
        }
        ++i;
        j = i;
    }
}
void CondorcetElection::init() {
    set<string>::iterator i = candidates_.begin(), j;
    j = i;
    while( i != candidates_.end() && ++j != candidates_.end() ) {
        while( j != candidates_.end() ) {
            pair<string,string> p(*j,*i);
            current_scores_[p] = 0;
            ++j;
        }
        ++i;
        j =i;
    }
    if( validate_votes() ) {
        //count_votes()
    }
    else {
        std::cerr << "Invalid election.";
    }
}

