/*
 *  IrrationalElection.cpp
 *  VMF
 *
 *  Created by bdm on 7/2/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */

#include "IrrationalElection.h"
#include <cmath>

// IrrationalElection - default constructor
IrrationalElection::IrrationalElection() : Election<IrrationalVote>(), scores_() {}

// IrrationalElection
IrrationalElection::IrrationalElection( const set<string>& candidates ) : Election<IrrationalVote>( candidates ), scores_() {}

// IrrationalElection
IrrationalElection::IrrationalElection( const set<string>& candidates, const multiset< IrrationalVote >& votes ) : Election<IrrationalVote>( candidates, votes ), scores_() {}

// validate_vote
int IrrationalElection::validate_vote( const IrrationalVote& vote ) const {
    map<pair<string,string>,int> prefs = vote.get_preferences();
    pair<string,string> p;
    set<string>::iterator i = candidates_.begin(), j = i;
    while( i != candidates_.end() ) {
        ++j;
        while( j != candidates_.end() ) {
            p.first = *i;
            p.second = *j;
            if( *i != *j ) {
                if( prefs.find( p ) != prefs.end() ) {
                    int n = prefs.at( p );    
                    if( n < 0 || n > 1 ) {
                        return 0;
                    }
                }
                else {
                    return 0;
                }
            }
            else {
                if( prefs.find( p ) != prefs.end() )
                    return 0;
            }
            ++j;
        }
        j = ++i;
    }
    return 1;
}

// clear_scores
void IrrationalElection::clear_scores() {
    scores_.clear();
    pair<string,string> p;
    set<string>::iterator i = candidates_.begin(), j = i;
    while( i != candidates_.end() ) {
        ++j;
        while( j != candidates_.end() ) {
            if( i != j ) {
                p.first = *i;
                p.second = *j;
                scores_[p] = 0;
            }
            ++j;
        }
        j = ++i;
    }
}