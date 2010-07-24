#ifndef FRONTEND_H_
#define FRONTEND_H_
#include <iostream>
#include <stdio.h>
#include <string>
#include <set>
#include <vector>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "functions.h"
#include "PositionalScoreElection.h"
#include "Borda.h"
#include "Veto.h"
#include "Plurality.h"
#include "Countdown.h"
#include "ScoringVector.h"
#include "CondorcetElection.h"

int main( int argc, char** argv );
void print_votes( const vector<RationalVote>& votes );
void print_votes( const multiset<RationalVote>& votes );
RationalVote create_vote( set<string> candidates );

template<typename T>
T* generate_election( T* e, int num_votes, vector<int> lower_bounding_vector, vector<int> upper_bounding_vector, int max_delta = 10 ) {
    
    set<string> candidates;
    vector<RationalVote> votes;
    for( int i = 0; i < num_votes; i++ ) {
        vector<string> remaining( candidates.begin(), candidates.end() );
        vector<string> vote;
        while( remaining.size() ) {
            int index = rand() % remaining.size();
            vote.push_back( *(remaining.begin() + index) );
            remaining.erase( remaining.begin() + index );
        }
        votes.push_back( vote );
    }
    vector<RationalVote>::iterator i = votes.begin();
    cout << "The following votes were added to the election:\n";
    while ( i != votes.end() ) { 
        cout << *i << "\n";
        e->add_vote( *i );
        ++i;
    }
}

#endif