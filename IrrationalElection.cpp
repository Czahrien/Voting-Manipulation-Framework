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

IrrationalElection::IrrationalElection() : Election<IrrationalVote>(), scores_() {

}
IrrationalElection::IrrationalElection( const set<string>& candidates ) : Election<IrrationalVote>( candidates ), scores_() {
    
}
IrrationalElection::IrrationalElection( const set<string>& candidates, const multiset< IrrationalVote >& votes ) : Election<IrrationalVote>( candidates, votes ), scores_()
{

}

int IrrationalElection::validate_vote( const IrrationalVote& vote ) const {
    map<pair<string,string>,double> prefs = vote.get_preferences();
    pair<string,string> p;
    set<string>::iterator i = candidates_.begin(), j = i;
    while( i != candidates_.end() ) {
        ++j;
        while( j != candidates_.end() ) {
            p.first = *i;
            p.second = *j;
            if( i != j ) {
                if( prefs.find( p ) != prefs.end() ) {
                    double n = prefs.at( p );    
                    if( fabs(n) > EPSILON || fabs(n - 1) > EPSILON ) {
                        return 0;
                    }
                    //if( n == 1 && !ties_allowed() ) {
                    // check if the reveresed pair == 1
                    //}
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

void IrrationalElection::init() {
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
    if( validate_votes() ) {
        is_valid_ = 1;
    }
    else {
        cerr << "Invalid votes within Copeland Election.\n";
    }
}