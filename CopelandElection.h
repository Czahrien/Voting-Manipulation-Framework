/*
 *  CopelandElection.h
 *  VMF
 *
 *  Created by bdm on 7/7/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */

#ifndef COPELANDELECTION_H_
#define COPELANDELECTION_H_

#include "IrrationalElection.h"

class CopelandElection : public IrrationalElection {
    public:
        /**
         * Default constructor.
         */
        CopelandElection();
        /**
         * Constructs a Copeland election with a set of candidates.
         *
         * @param candidates The candidates in the election.
         * @param tie_score  The score a tie awards candidates.
         */
        CopelandElection( const set<string>& candidates, double tie_score = 0.5 );
        /**
         * Constructs a Copeland election with a set of candidates and votes.
         *
         * @param candidates The candidates in the election.
         * @param tie_score  The score a tie awards candidates.
         */
        CopelandElection( const set<string>& candidates, const multiset<IrrationalVote>& votes, double tie_score = 0.5 );
        /**
         * Obtains the winner set of the current CopelandElection.
         */
        set<string> get_winners() const;
        /**
         * Determines if candidate c1 beats c2 in a head-to-head matchup.
         *
         * @param c1 A candidate.
         * @param c2 A candidate.
         * @return 1 if c1 beats c2 in the election, 0 otherwise.
         */
        int beats( const string& c1, const string& c2 ) const;
        /**
         * Counts a vote.
         *
         * @param vote The vote to count.
         */
        void count_vote( const IrrationalVote& vote );
        /**
         * Uncounts a vote.
         *
         * @param vote The vote to uncount.
         */    
        void uncount_vote( const IrrationalVote& vote );
    protected:
        /**
         * The score of a tie in the election.
         */
        double tie_score_;
};
#endif