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
    int current_max_wins = 0;
    set<string>::iterator s = candidates_.begin(), t = s;
    set<string> winners;
    map<string,double> win_count;
    
    // Compute the map containing the number of wins of each candidate:
    pair<string,string> m1, m2;
    while( s != candidates_.end() ) {
        t = s;
        ++t;
        m1.first = *s;
        m2.second = *s;
        while( t != candidates_.end() ) {
            m1.second = *t;
            m2.first = *t;
            if( t != s ) {
                if( scores_.at(m1) > scores_.at(m2) ) {
                    win_count[*s] += 1;
                }
                else if(scores_.at(m1) == scores_.at(m2)) {
                    win_count[*s] += tie_score_;
                    win_count[*t] += tie_score_;
                } 
                else {
                    win_count[*t] += 1;
                }
            }
            ++t;
        }
        ++s;
    }
    
    // Select the greatest number of wins in the map and the candidate(s) that
    //go(es) with it:
    map<string,double>::iterator i = win_count.begin();
    while( i != win_count.end() ) {
        if( i->second > current_max_wins ) {
            winners.clear();
            winners.insert( i->first );
        } else if( i->second == current_max_wins ) {
            winners.insert( i->first );
        }
        ++i;
    }
    return winners;
}

// beats
int CopelandElection::beats( const string& c1, const string& c2 ) const {
    pair<string,string> p1(c1,c2);
    pair<string,string> p2(c2,c1);
    map<pair<string,string>,int>::const_iterator m1 = scores_.find(p1), m2 = scores_.find(p2);
    if( m1 != scores_.end() && m2 != scores_.end() ) {
        return m1->second > m2->second;
    }
    return 0;
}

// count_vote
void CopelandElection::count_vote( const IrrationalVote& vote ) {
    set<string>::iterator s = candidates_.begin(), t = s;
    map<pair<string,string>,int> v( vote.get_preferences() );
    // vote has already been verified...
    double score;
    pair<string,string> m, m2;
    while( s != candidates_.end() ) { 
        m.first = *s;
        m2.second = *s;
        while( t != candidates_.end() ) {
            m.second = *t;
            m2.first = *t;
            score = v[m];
            if( score == 1.0 ) {
                scores_[m] += 1.0;
                assert(v[m2] == 0);
                
            }
            else {
                assert( v[m] == 0 );
                assert( v[m2] == 1 );
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
    map<pair<string,string>,int> v( vote.get_preferences() );
    // vote has already been verified...
    double score;
    pair<string,string> m, m2;
    while( s != candidates_.end() ) {
        m.first = *s;
        m2.second = *s;
        while( t != candidates_.end() ) {
            m.second = *t;
            m2.first = *t;
            score = v[m];
            if( score == 1.0 ) {
                scores_[m] -= 1.0;
                assert(v[m2] == 0);
                
            }
            else {
                assert( v[m] == 0 );
                assert( v[m2] == 1 );
            }
            ++t;
        }
        ++s;        
        t = candidates_.begin();
    }
}