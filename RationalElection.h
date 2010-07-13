/*
 *  RationalElection.h
 *  VMF
 *
 *  Created by bdm on 6/23/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */
#ifndef RATIONALELECTION_H_
#define RATIONALELECTION_H_
#include <set>
#include <string>
#include "Election.h"
#include "RationalVote.h"

using namespace std;
class RationalElection : public Election<RationalVote> {
    public:
        RationalElection();
        RationalElection( const set<string>& candidates );
        RationalElection( const set<string>& candidates, const multiset< RationalVote >& votes );
        /**
         * Checks a vote for validity.
         *
         * Assures that vote contains a complete ordering over the set of candidates - other candidates are allowed to be in the ordering provided that all of the candidates from the election are there.
         *
         * @param vote The vote to validate.
         * @return 0 if at least one candidate from this election's candidate set are missing - 1 otherwise.
         */
        int validate_vote( const RationalVote& vote ) const;
};
#endif