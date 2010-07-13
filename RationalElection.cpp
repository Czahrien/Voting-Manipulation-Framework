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


RationalElection::RationalElection() : Election<RationalVote>() {}
RationalElection::RationalElection( const set<string>& candidates ) : Election<RationalVote>( candidates ) {}
RationalElection::RationalElection( const set<string>& candidates, const multiset<RationalVote>& votes ) : Election<RationalVote>( candidates, votes ) {}

int RationalElection::validate_vote( const RationalVote& vote ) const {
    // Check if the candidate set is a subset of the vote set. Thank Turing that sets are sorted~
    
    // Convert the votes to a set.
    // Note that this algorithm runs O(N) instead of O(N*logN) like it would if I just looked up each candidate in the set.
    // So this SHOULD be faster.
    
    set<string> vote_set(vote.get_candidates());//vote.begin(), vote.end());
    // TODO: Determine whether or not it is actually needed to check the size of a rational
    // voter's preference order.
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

