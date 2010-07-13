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

// CondorcetElection - default constructor
CondorcetElection::CondorcetElection() : RationalElection(), current_scores_() {
    init();
}

// CondorcetElection
CondorcetElection::CondorcetElection( const set<string>& candidates ) : RationalElection( candidates ), current_scores_() {
    init();
}

// CondorcetElection
CondorcetElection::CondorcetElection( const set<string>& candidates, const multiset< RationalVote >& votes ) : RationalElection( candidates, votes ), current_scores_() {
    init();
}

// get_winners
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

// CondorcetElection
map<pair<string,string>,int> CondorcetElection::get_vote_count() const {
    return current_scores_;
}

// beats
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
            }
            ++i;
        }
    }
    return losers;
}

// count_vote
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

// uncount_vote
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

// init
/*void CondorcetElection::init() {
    set<string>::iterator i = candidates_.begin(), j;
    j = i;
    while( i != candidates_.end() ) {
        while( j != candidates_.end() ) {
            if( *i != *j ) {
                pair<string,string> p(*j,*i);
                current_scores_[p] = 0;
            }
            ++j;
        }
        ++i;
        j =i;
    }
    if( validate_votes() ) {
        is_valid_ = 1;
        //count_votes()
    }
    else {
        std::cerr << "Invalid election.";
    }
}*/

void CondorcetElection::clear_scores() {
    current_scores_.clear();
    set<string>::iterator i = candidates_.begin(), j;
    pair<string,string> m;
    while( i != candidates_.end() ) {
        j = candidates_.begin();
        m.first = *i;
        while( j != candidates_.end() ) {
            if( *i != *j ) {
                m.second = *j;
                current_scores_[m] = 0;
            }
            ++j;
        }
        ++i;
    }
}