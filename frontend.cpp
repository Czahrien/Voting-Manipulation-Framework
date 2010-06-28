/*
 *  frontend.cpp
 *  VMF
 *
 *  Created by bdm on 6/24/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */

#include "frontend.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <set>
#include <vector>
#include "PositionalScoreElection.h"

using namespace std;
int main2( int argc, char** argv ) {
    set<string> candidates;
    cout << "How many candidates are in the election? ";
    int count;
    cin >> count;
    if( count < 1 ) { // TODO: Determine whether or not a single candidate should be allowed.
        //Error condition.
    }
    cout << "Enter a candidate's name, hit enter. Do this " << count << " time(s).\n";
    string in;
    while( count-- > 0 ) {
        cin >> in;
        if( !cin.good() ) {
            count++;
            cin.clear();
            cin.sync();
            //ERROR CONDITION
        } else {
            candidates.insert( in );
        }
    }
    if( !cin.good() ) {
        count++;
        //Error condition
    }
    //cin.clear();
    //cin.sync();
    if( !candidates.size() ) {
        cerr << "No candidates entered.\n";
        exit(1);
    }
    cout << "\nWhat would you like to do?\n" << 
    "\t1. Add Vote\n" <<
    "\t2. Remove Vote\n" <<
    "\t3. Add Candidate\n" <<
    "\t4. Remove Candidate\n" <<
    "\tR. Run Election\n" <<
    "\tQ. Quit\n" <<
    "Enter desired option: ";
    //cin >> in;
    char c = 0;
    
    while( ( c = cin.get() ) != 'q' || c != 'Q' ) {
        cout << c << endl;
    }
    return 0;
    
}