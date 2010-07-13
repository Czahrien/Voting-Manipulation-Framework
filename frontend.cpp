/*
 *  frontend.cpp
 *  VMF
 *
 *  Created by bdm on 6/24/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */
#include <iostream>
#include <stdio.h>
#include <string>
#include <set>
#include <vector>
#include <cstdio>
#include <cmath>
#include "functions.h"
#include "PositionalScoreElection.h"
#include "Borda.h"
#include "Veto.h"
#include "Plurality.h"
#include "Countdown.h"


using namespace std;
int main( int argc, char** argv ) {
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
            ++count;
            cin.clear();
            cin.sync();
            //ERROR CONDITION
        } else {
            int initial = candidates.size();
            candidates.insert( in );
            int final = candidates.size();
            if( final != initial + 1 ) {
                //the user attempted to create two candidates of the same name...
                ++count;
            }
        }
    }
    if( !cin.good() ) {
        count++;
        //Error condition
        cin.clear();
        cin.sync();
    }
 
    if( candidates.size() < 2 ) {
        cerr << "ERROR: At least two candidates needed for an election.\n";
        exit(1);
    }
    //cout << "Rational systems: \n-Condorcet \n-Position Score Systems: \n\t1. Plurality\n\t2. Veto\n\t3. Borda\n";
    //cout << "Irrational systems: \n-Copeland\n";
    PositionalScoreElection* e = new Borda( candidates );
    char c = 0;
    while( c != 'q' && c != 'Q' ) {
        cout << "\nWhat would you like to do?\n" << 
            "\t1. Add Vote\n" <<
            "\t2. Remove Vote\n" <<
            "\t3. List Votes\n" <<
            "\t4. Add Candidate\n" <<
            "\t5. Remove Candidate\n" <<
            "\tR. Run Election\n" <<
            "\tC. Change Election\n" <<
            "\tQ. Quit\n" <<
            "Enter desired option: ";
        cout.flush();
        #ifndef _WIN32
        set_conio_terminal_mode();
        #endif
        while( !kbhit() ) {
            usleep(100000);
        }
        //while( kbhit() ) {
            //User entered multiple keys at once. We want to consume all the keys
            //before moving on.
            c = getch();
        //}
        #ifndef _WIN32
        reset_terminal_mode();
        #endif
        cout << "\n";
        switch (c) {
            case '1':
                {
                    set<string> remaining( candidates );
                    vector<string> vote;
                    while( remaining.size() ) {
                        cout << "Remaining candidates to place in vote: ";
                        set<string>::iterator i = remaining.begin();
                        while( i != remaining.end() ) {
                            cout << *i;
                            ++i;
                            if( i != remaining.end() ) {
                                cout << ", ";
                            }
                            else {
                                cout << "\n";
                            }
                        }
                    
                        vector<string>::iterator j;
                    
                        if( vote.size() > 0 ) {
                            j = vote.begin();
                            while( j != vote.end() ) {
                                cout << *j;
                                ++j;
                                if( j != vote.end() ) {
                                    cout << " > ";
                                }
                                else {
                                    cout << "\n";
                                }
                            }
                        }
                        
                        cout << "Select a candidate to add to the vote or a candidate in the vote to remove it: ";
                        cout.flush();
                        cin >> in;
                    
                        i = remaining.find( in );
                        if( i != remaining.end() ) {
                            remaining.erase( i );
                            vote.push_back( in );
                        }
                        else {
                        j = vote.begin();
                            while( j != vote.end() && *j != in ) {
                                ++j;
                            }
                            if( j != vote.end() ) {
                                vote.erase( j );
                                remaining.insert( in );
                            }
                        }
                    }
                    e->add_vote(vote);
                    vector<string>::iterator j;
                    cout << "The following vote was added to the election: " << vote << "\n";
                }
                
                break;
            case '2':
                { 
                    
                    cout << "Votes currently in the election:\n";
                    set<RationalVote> votes = e->get_vote_list();
                    set<RationalVote>::iterator i = votes.begin();
                    
                    while( i != votes.end() ) {
                        cout << *i << "\n";
                        ++i;
                    }
                    
                    set<string> remaining( candidates );
                    vector<string> vote;
                    while( remaining.size() ) {
                        cout << "Remaining candidates to place in vote: ";
                        set<string>::iterator i = remaining.begin();
                        while( i != remaining.end() ) {
                            cout << *i;
                            ++i;
                            if( i != remaining.end() ) {
                                cout << ", ";
                            }
                            else {
                                cout << "\n";
                            }
                        }
                        
                        vector<string>::iterator j;
                        
                        if( vote.size() > 0 ) {
                            j = vote.begin();
                            while( j != vote.end() ) {
                                cout << *j;
                                ++j;
                                if( j != vote.end() ) {
                                    cout << " > ";
                                }
                                else {
                                    cout << "\n";
                                }
                            }
                        }
                        
                        cout << "Select a candidate to add to the vote or a candidate in the vote to remove it: ";
                        cout.flush();
                        cin >> in;
                        
                        i = remaining.find( in );
                        if( i != remaining.end() ) {
                            remaining.erase( i );
                            vote.push_back( in );
                        }
                        else {
                            j = vote.begin();
                            while( j != vote.end() && *j != in ) {
                                ++j;
                            }
                            if( j != vote.end() ) {
                                vote.erase( j );
                                remaining.insert( in );
                            }
                        }
                    }
                    if( e->remove_vote( vote ) ) {
                        cout << "Vote successfully removed.\n";
                    }
                    else {
                        cerr << "ERROR: Vote could not be removed.\n";
                    }
                }
                break;
            case '3':
                {
                    cout << "Votes currently in the election:\n";
                    map<RationalVote,int> votes = e->get_vote_numbers();
                    map<RationalVote,int>::iterator i = votes.begin();
                
                    while( i != votes.end() ) {
                        cout << i->first << ": " << i->second << "\n";
                        ++i;
                    }
                }
                break;
            case '4': 
                cout << "Enter the name of a candidate previously removed from the election: ";
                cout.flush();
                cin >> in;
                e->add_candidate( in );
                break;
            case '5':
                cout << "Enter the name of a candidate in the election to remove them or anything else to go back: ";
                cout.flush();
                cin >> in;
                e->remove_candidate( in );
                break;
            case 'R':
            case 'r':
                {
                    if( !e->votes_counted() ) {
                        e->count_votes();
                    }
                    map<string, int> r = e->get_vote_count();
                    map<string,int>::iterator k = r.begin();
                
                    while( k != r.end() ) {
                        cout << k->first << ": " << k->second << " votes.\n";
                        ++k;
                    }
                    set<string> winners = e->get_winners();
                
                    set<string>::iterator l = winners.begin();
                    cout<< "\nWinners:";
                    while( l != winners.end() ) {
                        cout << " " << *l;
                        l++;
                    }
                    cout << endl;
                }
                    break;
            case 'C':
            case 'c':
                {
                    cout << "Which election type would you like to change the election to?\n";
                    cout << "\t1. Plurality\n\t2. Veto\n\t3. Borda\n\t4. (2,1,0,...,0)\n\t5. (3,2,1,0,...,0)\n";
                    cout << "Enter the number corresponding to the desired election.";
                    //TODO: Error check input
                    #ifndef _WIN32
                    set_conio_terminal_mode();
                    #endif
                    while( !kbhit() ) {
                        usleep( 100000 );
                    }
                    char k = getch(); 
                    #ifndef _WIN32
                    reset_terminal_mode();
                    #endif
                    multiset<RationalVote> v = e->get_votes();
                    switch( k ) {
                        case '1':
                            delete e;
                            e = new Plurality( candidates, v );
                            break;
                        case '2':
                            delete e;
                            e = new Veto( candidates, v );
                            break;
                        case '3':
                            delete e;
                            e = new Borda( candidates, v );
                            break;
                        case '4':
                            delete e;
                            e = new Countdown( candidates, v );
                            dynamic_cast<Countdown*>(e)->change_countdown( 2 );
                            break;
                        case '5':
                            delete e;
                            e = new Countdown( candidates, v );
                            dynamic_cast<Countdown*>(e)->change_countdown( 3 );
                            break;
                        default:
                            cout << "Invalid choice, election system unchanged.";
                            break;
                    }
                }
                break;
            case 'M':
            case 'm':
            {
                cout << "Unique winner problem [Y/n]: ";
                cout.flush();
                // unique winner problem
                #ifndef _WIN32
                set_conio_terminal_mode();
                #endif
                while( !kbhit ) {
                    usleep( 100000 );
                }
                char k = getch();
                cout << "\n";

                int unique = ( k != 'n' || k != 'N' );
                cout << "Would you like to limit the number of manipulators [y/N]: ";
                cout.flush();
                
                while( !kbhit ) {
                    usleep( 100000 );
                }
                k = getch();
                cout << "\n";
                #ifndef _WIN32
                reset_terminal_mode();
                #endif
                int limit = 0;
                if( k == 'y' || k  == 'Y' ) {
                    while( limit < 1 ) {
                        cout << "Enter the number of manipulators: ";
                        cout.flush();
                        if( !( cin >> limit ) || limit < 1 ) {
                            cerr << "ERROR: A positive integer is needed.\n";
                            if( !cin ) {
                                cin.clear();
                                cin.sync();
                            }
                        }
                    }
                    
                }
                // Single winner manipulation tests.
                //Temporary Manipulation test.
                //P Algorithm for (2,1,0,...0):
                // Determine how many votes of weight two the preferred candidate, c, needs to win.
                // Assume this takes n votes. That means that n votes must be distributed among the other candidates.
                // for all c` in C where c`!= c, sum up (votes(c) - votes( c`)).
                // If this is greater than n, determine the difference, divide the difference by 2, round up.
                // Add this many more 2 point votes to c and add the difference to n.
                // Greedily distribute the n 1-votes among each of the non-preferred candidates such that c is a winner.
                //This should cover all bases.
                cout << "Enter the name of the preferred candidate: ";
                cout.flush();
                cin >> in;
                // TODO: Make this not crap out when the candidate is removed from the election.
                vector<RationalVote> manipulators;
                
                if( candidates.find( in ) != candidates.end() ) {
                    map<string, int> scores = e->get_vote_count();
                    set<string> winners = e->get_winners();
                    // This next line is kind of messy.
                    // Basically it loops while the candidate is not in the winner set (or not the unique winner if the unique flag is set) AND
                    // if the number of manipulators is less than the limit of the manipulators if such a limit was imposed.
                    while( (winners.find( in ) == winners.end() || (unique && winners.size() > 1)) && (!limit || manipulators.size() < limit ) ) {
                        set<string> remaining( candidates );
                        remaining.erase( in );
                        vector<string> vote;
                        vote.push_back( in );
                        int position = 1;
                        while( e->position_score( position++ ) > 0 ) {
                            map<string,int>::iterator i = scores.begin();
                            int min = -1;
                            string min_candidate;
                            while( i != scores.end() ) {
                                if( remaining.find( i->first ) != remaining.end() ) {
                                    if( i->second < min || min == -1 ) {
                                        min = i->second;
                                        min_candidate = i->first;
                                    }
                                }
                                ++i;
                            }
                            vote.push_back(min_candidate);
                            remaining.erase( min_candidate );
                        }
                        cout << vote << " was obtained.\n";
                        vote.insert( vote.end(), remaining.begin(), remaining.end() );
                        e->add_vote(vote);
                        manipulators.push_back( vote );
                        scores = e->get_vote_count();
                        winners = e->get_winners();
                    }
                    /*int max = 0, sum = 0;
                    map<string,int>::iterator i = scores.begin();
                    while( i != scores.end() ) {
                        if( i->first != in ) {
                            sum += i->second;
                            if( i->second > max ) {
                                max = i->second;
                            }
                        }
                        ++i;
                    }
                    int votes_needed = max - scores[in];
                    votes_needed = ceil( votes_needed / 2.0 );
                    int final_score = scores[in] + 2 * votes_needed;
                    int bins = candidates.size() * final_score - sum;
                
                    while( bins < votes_needed ) {
                        votes_needed++;
                        bins += candidates.size() * 2;
                        final_score += 2;
                    }
                    // Let's get greedy!
                    scores[in] = final_score;
                    for( int i = 0; i < votes_needed; i++ ) {
                        set<string> remaining(candidates);
                        remaining.erase(in);
                        vector<string> vote;
                        vote.push_back(in);
                        
                        map<string,int>::iterator j = scores.begin();
                        while( j != scores.end() && j->second >= final_score ) {
                            ++j;
                        }
                        
                        if( j == scores.end() ) {
                            cerr << "ERROR: This shouldn't have happened.\n";
                        }
                        string c = j->first;
                        scores[c]++;
                        remaining.erase(c);
                        vote.push_back(c);
                        vote.insert(vote.end(), remaining.begin(), remaining.end());
                        manipulators.push_back( RationalVote(vote) );
                    }*/
                    
                    cout << "Manipulation used " << manipulators.size() << " manipulators.\n";
                    cout << "Added votes:\n";
                    vector<RationalVote>::iterator j = manipulators.begin();
                    while( j != manipulators.end() ) {
                        cout<< *j << "\n";
                        //e->add_vote( *j );
                        ++j;
                    }
                    
                }
                
                // P(?) Algorithm (idea) for (3,2,1,0,...,0)
                // Determine how many votes of weight three the preferred candidate, c, needs to win.
                //
                // completely distribute 2 votes to even "bins".
                // completely distribute 2 votes to odd "bins" and top off the "bins" with single votes from even bins or other odd bins.
                // as long as there are remaning bins it is trivial to distribute one votes.
                // If bins run out of space the addition of a single vote complete vote adds three to the size of all bins.
                
                // (2,2,1,0,...,0) would take a similar approach to the one above.
                
                // That is probably P, but what about (4,3,2,1,0,...,0)?
                
            }
                break;
            default:
                break;
        }
    }
    return 0;
}