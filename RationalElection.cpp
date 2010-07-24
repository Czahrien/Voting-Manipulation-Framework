/*
 *  RationalElection.cpp
 *  VMF
 *
 *  Created by bdm on 6/24/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */

#include <iostream>
#include "RationalElection.h"

// RationalElection - default constructor
RationalElection::RationalElection() : Election<RationalVote>() {}

// RationalElection
RationalElection::RationalElection( const set<string>& candidates ) : Election<RationalVote>( candidates ) {}

// RationalElection
RationalElection::RationalElection( const set<string>& candidates, const multiset<RationalVote>& votes ) : Election<RationalVote>( candidates, votes ) {}

// validate_vote
int RationalElection::validate_vote( const RationalVote& vote ) const {
    // Check if the candidate set is a subset of the vote set.
    set<string> vote_set(vote.get_candidates());
    if( vote_set.size() == vote.get_preference_order().size() && vote_set.size() >= candidates_.size() ) {
        set<string>::const_iterator i = vote_set.begin();
        set<string>::const_iterator j = candidates_.begin();
        while( i != vote_set.end() && j != candidates_.end() ) {
            if( *j == *i ) {
                ++j;
            }
            ++i;
        }
        return j == candidates_.end();
    }
    else {
        return 0;
    }
}

