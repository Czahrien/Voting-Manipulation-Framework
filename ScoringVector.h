/*
 *  ScoringVector.h
 *  VMF
 *
 *  Created by bdm on 7/18/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */


#ifndef SCORINGVECTOR_H_
#define SCORINGVECTOR_H_
#include "PositionalScoreElection.h"
using namespace std;
class ScoringVector : public PositionalScoreElection {
    public:
        /**
         * Default constructor.
         */
        ScoringVector();
        /**
         * ScoringVector constructor that takes the set of candidates.
         *
         * @param candidates The set of candidates.
         */
        ScoringVector( const set<string>& candidates );
        /**
         * ScoringVector constructor that takes a set of candidates and votes.
         *
         * @param candidates The set of candidates
         * @param votes A multiset of RationalVotes.
         */
        ScoringVector( const set<string>& candidates, const multiset< RationalVote >& votes );
    public:
        /**
         * Sets the scoring vector to the vector given.
         * 
         * @param scoring_vector The vector to set the scores to.
         */
        void set_scoring_vector( vector<int> scoring_vector );
        /**
         * Obtains the scoring vector.
         *
         * @return The scoring vector.
         */
        vector<int> get_scoring_vector() const;
        /** 
         * Obtains the score given to a candidate placed at position.
         *
         * @param position The position to get the score of.
         * @return The number of points awarded to a candidate placed in position.
         */
        int position_score( int position ) const;
    protected:
        /**
         * The underlying scoring vector.
         */
        vector<int> scoring_vector_;
};
#endif