/*
 *  frontend.cpp
 *  VMF
 *
 *  Created by bdm on 6/24/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */

#include "frontend.h"


using namespace std;

// main
int main( int argc, char** argv ) {
    srand( time(NULL) );
    set<string> candidates;
    cout << "How many candidates are in the election? ";
    int count;
    cin >> count;
    if( count <= 1 || !cin ) { 
        cerr << "Error, enter a number >= 1.\n";
        exit(1);
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
    //PositionalScoreElection* 
    RationalElection* e = new Borda( candidates );
    char c = 0;
    while( c != 'q' && c != 'Q' ) {
        cout << "\nWhat would you like to do?\n" << 
            "\t1. Add Vote\n" <<
            "\t\tV. Add Random Votes\n" <<
            "\t2. Remove Vote\n" <<
            "\t3. List Votes\n" <<
            "\t4. Add Candidate\n" <<
            "\t5. Remove Candidate\n" <<
            "\tR. Run Election\n" <<
            "\tC. Change Election\n"; 
        if( dynamic_cast<PositionalScoreElection*> (e) ) {
            cout << "\tM. Manipulate with Greedy Algorithm\n"; 
        }
        cout << "\tX. Clear the votes in the election.\n" <<
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
                    RationalVote vote = create_vote(candidates);
                    e->add_vote( vote );
                    vector<string>::iterator j;
                    cout << "The following vote was added to the election: " << vote << "\n";
                }
                
                break;
            case 'V':
            case 'v':
                {
                    int n;
                    cout << "How many random votes do you want to add: ";
                    cin >> n;
                    if ( n >= 1 ) {
                        vector<RationalVote> votes;
                        for( int i = 0; i < n; i++ ) {
                            vector<string> remaining( candidates.begin(), candidates.end() );
                            vector<string> vote;
                            while( remaining.size() ) {
                                int index = rand() % remaining.size();
                                vote.push_back( *(remaining.begin() + index) );
                                remaining.erase( remaining.begin() + index );
                            }
                            votes.push_back( vote );
                        }
                        cout << "The following votes were added to the election:\n";
                        print_votes( votes );
                        vector<RationalVote>::iterator i = votes.begin();
                        while ( i != votes.end() ) { 
                            e->add_vote( *i );
                            ++i;
                        }
                    }
                }
                break;
            case '2':
                { 
                    
                    cout << "Votes currently in the election:\n";
                    multiset<RationalVote> votes = e->get_votes();
                    print_votes( votes );
                    if( e->remove_vote( create_vote(candidates) ) ) {
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
                    print_votes( e->get_votes() );
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
                    PositionalScoreElection* p;
                    if( p = dynamic_cast<PositionalScoreElection*> (e) ) {
                        map<string, int> r = p->get_vote_count();
                        map<string,int>::iterator k = r.begin();
                
                        while( k != r.end() ) {
                            cout << k->first << ": " << k->second << " votes.\n";
                            ++k;
                        }
                    } else {
                        CondorcetElection* c = dynamic_cast<CondorcetElection*> (e);
                        if( c ) {
                            map<pair<string,string>,int> m = c->get_vote_count();
                            map<pair<string,string>,int>::iterator i = m.begin();
                            
                            while( i != m.end() ) {
                                cout << "(" << i->first.first << "," << i->first.second << "): " << i->second << endl;
                                ++i;
                            }
                        }
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
                    cout << "\t1. Plurality\n\t2. Veto\n\t3. Borda\n\t4. (n,n-1,...,1,0,...,0)\n\t5. (a1,a2,...,an,0,...,0)\n";
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
                            {
                                int n;
                                delete e;
                                e = new Countdown( candidates, v );
                                cout << "From what number do you want to count down from: ";
                                cin >> n;
                                // TODO: Error trap input.
                                if( n > 0 ) {
                                    dynamic_cast<Countdown*>(e)->change_countdown( n );
                                }
                                break;
                            }
                        case '5':
                            {
                                vector<int> scores;
                                int n;
                                delete e;
                                cout << "Enter numbers to put into the scoring vector and -1 to finish: ";
                                while ( cin >> n && n > 0 ) {
                                    scores.push_back( n );
                                }
                                e = new ScoringVector( candidates, v );
                                dynamic_cast<ScoringVector*>(e)->set_scoring_vector( scores );
                                scores = dynamic_cast<ScoringVector*>(e)->get_scoring_vector();
                                vector<int>::iterator i = scores.begin();
                                while( i != scores.end() ) {
                                    cout << *i << " ";
                                    ++i;
                                }
                                cout << "\n";
                                break;
                            }
                        case '6':
                            {
                                delete e;
                                e = new CondorcetElection( candidates, v );
                            }
                        default:
                            cout << "Invalid choice, election system unchanged.";
                            break;
                    }
                }
                break;
            case 'M':
            case 'm':
            if ( dynamic_cast<PositionalScoreElection*> (e) )
            {
                PositionalScoreElection* p = dynamic_cast<PositionalScoreElection*> (e);
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
                cout << "Enter the name of the preferred candidate: ";
                cout.flush();
                cin >> in;
                // TODO: Make this not crap out when the candidate is removed from the election.
                vector<RationalVote> manipulators;
                
                if( candidates.find( in ) != candidates.end() ) {
                    map<string, int> scores = p->get_vote_count();
                    set<string> winners = p->get_winners();
                    // This next line is kind of messy.
                    // Basically it loops while the candidate is not in the winner set (or not the unique winner if the unique flag is set) AND
                    // if the number of manipulators is less than the limit of the manipulators if such a limit was imposed.
                    while( (winners.find( in ) == winners.end() || (unique && winners.size() > 1)) && (!limit || manipulators.size() < limit ) ) {
                        set<string> remaining( candidates );
                        remaining.erase( in );
                        vector<string> vote;
                        vote.push_back( in );
                        int position = 1;
                        map<string,int>::iterator sc = scores.begin();
                        while( p->position_score( position++ ) > 0 ) {
                            map<string,int>::iterator i = scores.begin();
                            int min = -1;
                            string target_min_candidate;
                            string target_max_candidate = "";
                            while( i != scores.end() ) {
                                if( remaining.find( i->first ) != remaining.end() ) {
                                    if( i->second < min || min == -1 ) {
                                        min = i->second;
                                        target_min_candidate = i->first;
                                    }
                                }
                                ++i;
                            }
                            vote.push_back(target_min_candidate);
                            remaining.erase( target_min_candidate );                                
                        }
                        vote.insert( vote.end(), remaining.begin(), remaining.end() );
                        e->add_vote(vote);
                        manipulators.push_back( vote );
                        scores = p->get_vote_count();
                        winners = e->get_winners();
                    }
                    cout << "Manipulation used " << manipulators.size() << " manipulators.\n";
                    cout << "Added votes:\n";
                    print_votes( manipulators );
                }
                
            }
                break;
            case 'x':
            case 'X':
                cout << "Erasing all votes in the election.\n";
                e->erase_votes();
                break;
            default:
                break;
        }
    }
    return 0;
}

// print_votes
void print_votes( const vector<RationalVote>& votes ) {
    vector<RationalVote>::const_iterator i = votes.begin();
    map<RationalVote,int>::iterator j;
    map<RationalVote,int> vote_map;
    while( i != votes.end () ) {
        vote_map[*i]++;
        ++i;
    }
    j = vote_map.begin();
    while( j != vote_map.end() ) {
        cout << j->first << ": " << j->second << "\n";
        ++j;
    }
}

// print_votes
void print_votes( const multiset<RationalVote>& votes ) {
    vector<RationalVote> vect( votes.begin(), votes.end() );
    print_votes( vect );
}

// create_vote
RationalVote create_vote( set<string> candidates ) {
    #ifndef _WIN32
    reset_terminal_mode();
    #endif
    
    string in;
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
    
    #ifndef _WIN32
    set_conio_terminal_mode();
    #endif
    
    return vote;
}