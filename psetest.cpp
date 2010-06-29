#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <string>
#include <map>
#include "Borda.h"
#include "Plurality.h"
#include "Veto.h"
#include "CondorcetElection.h"

using namespace std;
int main() {
    set<string> C;
    C.insert( "Bill" );
    C.insert( "Bob" );
    C.insert( "Jane" );

    vector<string> v1,v2,v3,v4;

    v1.push_back( "Bill" );
    v1.push_back( "Hwharrrgharrble" );
    v1.push_back( "Bob" );
    v1.push_back( "Jane" );
    v2.push_back( "Bob" );
    v2.push_back( "Bill" );
    v2.push_back( "Jane" );
    v3.push_back( "Jane" );
    v3.push_back( "Bob" );
    v3.push_back( "Bill" );
    v4.push_back( "Jane" );
    v4.push_back( "Bill" );
    v4.push_back( "Bob" );
    RationalVote rv1(v1);
    RationalVote rv2(v2);
    RationalVote rv3(v3);
    RationalVote rv4(v4);
    cout << "Votes:\n" << rv1 << "\n" << rv2 << "\n" << rv3 << "\n" << rv4 << "\n\n";

    multiset< RationalVote > V;
    V.insert( rv1 );
    V.insert( rv2 );
    V.insert( rv3 );
    V.insert( rv4 );
    V.insert( rv4 );
    

    Borda* e1 = new Borda( C, V );
    Plurality* e2 = new Plurality( C, V );
    Veto* e3 = new Veto( C, V );
    vector< PositionalScoreElection* > systems;
    systems.push_back( e1 );
    systems.push_back( e2 );
    systems.push_back( e3 );

    vector< PositionalScoreElection* >::iterator sys = systems.begin();

    while( sys != systems.end() ) {
        PositionalScoreElection* b = *sys;
        sys++;

        b->count_votes();
        map<string, int> E = b->get_vote_count();
        map<string,int>::iterator i = E.begin();

        while( i != E.end() ) {
            cout << i->first << ": " << i->second << " votes.\n";
            i++;
        }
        set<string> winners = b->get_winners();

        set<string>::iterator j = winners.begin();
        cout<< "\nWinners:";
        while( j != winners.end() ) {
            cout << " " << *j;
            j++;
        }
        cout << endl;
        set<string>::iterator k = C.begin();

        while( k != C.end() ) {
            winners = b->beats( *k );
            j = winners.begin();
            cout<< "\n" << *k << " beats:";
            while( j != winners.end() ) {
                cout << " " << *j;
                j++;
            }
            k++;
        }
        cout << endl << endl;

    }
    delete e1;
    delete e2;
    delete e3;
    CondorcetElection con(C,V);
    con.count_votes();
    set<string> winners = con.get_winners();
    if( winners.size() ) {
        cout << "Winner: " << *(winners.begin()) << endl << endl;
    }
    else {
        cout << "No condorcet winner present.\n\n";
    }    
    cout << "(r,c) corresponds to the number of votes in which the row candidate beat the column candidate in a head-to-head matchup.\n\n";

    map<pair<string,string>,int> scores = con.get_vote_count();
    
    cout << setw(10) << " ";
    set<string>::iterator i = C.begin(), j = i;
    while( j != C.end() ) {
        cout << setw(10) << *j;
        j++;
    }
    cout << "\n";
    while( i != C.end() ){
        j = C.begin();
        cout << setw(10) << *i;
        while( j != C.end() ) {
            if( *i != *j ) {
                cout << setw(10) << scores[pair<string,string>(*i,*j)];
            }
            else {
                cout << setw(10) << "-";
            }
            ++j;
        }
        cout << endl;
        ++i;
    }
}
