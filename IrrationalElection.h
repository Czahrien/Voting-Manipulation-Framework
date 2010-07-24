/*
 *  IrrationalElection.h
 *  VMF
 *
 *  Created by bdm on 6/23/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */

#ifndef IRRATIONALELECTION_H_
#define IRRATIONALELECTION_H_
#include <set>
#include <map>
#include <string>
#include "Election.h"
#include "IrrationalVote.h"

using namespace std;
class IrrationalElection : public Election<IrrationalVote> {
public:
    /**
     * Default Constructor
     */
    IrrationalElection();
    /**
     * Constructs an IrrationalElection from a set of candidates.
     *
     * @param candidates The set of candidates.
     */
    IrrationalElection( const set<string>& candidates );
    /**
     * Constrcuts an IrrationalElection from a set of candidates and a set of votes.
     *
     * @param candidates The set of candidates.
     */
    IrrationalElection( const set<string>& candidates, const multiset< IrrationalVote >& votes );
    /**
     * Validates vote. Determines whether or not the vote is of the appropriate
     * format and a subset of its candidates are equal to the candidates in this
     * election.
     *
     * @param vote The vote to be validated.
     * @return 1 if the vote is valid, 0 otherwise.
     */
    int validate_vote( const IrrationalVote& vote ) const;
    /**
     * Clears the score within the election.
     */
    void clear_scores();
protected:
    /**
     * The map containing the scores.
     */
    map<pair<string,string>,int> scores_;
};
#endif
