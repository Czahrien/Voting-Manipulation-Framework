/*
 *  CopelandElection.cpp
 *  VMF
 *
 *  Created by bdm on 7/7/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */

#include "CopelandElection.h"
#include <cassert>
#include <cmath>

// CopelandElection - default constructor
CopelandElection::CopelandElection() : IrrationalElection(), tie_score_(0.5) {}

// CopelandElection
CopelandElection::CopelandElection( const set<string>& candidates, double tie_score ) : IrrationalElection(candidates), tie_score_(tie_score) {}

// CopelandElection
CopelandElection::CopelandElection( const set<string>& candidates, const multiset<IrrationalVote>& votes, double tie_score ) : IrrationalElection(candidates, votes), tie_score_(tie_score) {}

// get_winners
set<string> CopelandElection::get_winners() const {
    double current_max_score = 0.0;
    set<string>::iterator s = candidates_.begin(), t = s;
    set<string> winners;
    
    pair<string,string> m;
    while( s != candidates_.end() ) {
        double score;
        while( t != candidates_.end() ) {
            m.first = *s;
            if( t != s ) {
                m.second = *t;
                score += scores_.at(m);
            }
            ++t;
        }
        
        if( current_max_score < score ) {
            winners.clear();
            current_max_score = score;
            winners.insert( *s );
        } else if( current_max_score == score ) {
            winners.insert( *s );
        }
        
        ++s;
        t = candidates_.begin();
    }
    
    return winners;
}

// beats
int CopelandElection::beats( const string& c1, const string& c2 ) const {
    pair<string,string> p1(c1,c2);
    pair<string,string> p2(c2,c1);
    map<pair<string,string>,double>::const_iterator m1 = scores_.find(p1), m2 = scores_.find(p2);
    if( m1 != scores_.end() && m2 != scores_.end() ) {
        return *m1 > *m2;
    }
    return 0;
}

// count_vote
void CopelandElection::count_vote( const IrrationalVote& vote ) {
    set<string>::iterator s = candidates_.begin(), t = s;
    map<pair<string,string>,double> v( vote.get_preferences() );
    // vote has already been verified...
    double score;
    pair<string,string> m;
    while( s != candidates_.end() ) { 
        m.first = *s;
        while( t != candidates_.end() ) {
            m.second = *t;
            score = v[m];
            if( fabs(v[m] - 1.0) < EPSILON ) {
                scores_[m] += 1.0;
            }
            else if( fabs(v[m] - 0.5) < EPSILON ) {
                scores_[m] += tie_score_;
            }
            else {
                assert( fabs(v[m]) < EPSILON );
            }
            ++t;
        }
        ++s;
        t = candidates_.begin();
    } 
}

// uncount_vote
void CopelandElection::uncount_vote( const IrrationalVote& vote ) {
    set<string>::iterator s = candidates_.begin(), t = s;
    map<pair<string,string>,double> v( vote.get_preferences() );
    // vote has already been verified...
    double score;
    pair<string,string> m;
    while( s != candidates_.end() ) {
        m.first = *s;
        while( t != candidates_.end() ) {
            m.second = *t;
            score = v[m];
            if( fabs(v[m] - 1.0) < EPSILON ) {
                scores_[m] -= 1.0;
            }
            else if( fabs(v[m] - 0.5) < EPSILON ) {
                scores_[m] -= tie_score_;
            }
            else {
                assert( fabs(v[m]) < EPSILON );
            }
            ++t;
        }
        ++s;
        t = candidates_.begin();
    }
}