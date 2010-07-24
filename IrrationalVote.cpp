#include <iomanip>
#include "IrrationalVote.h"

// IrrationalVote - default constructor
IrrationalVote::IrrationalVote() : Vote(), candidates_(), preferences_() {}

// IrrationalVote
IrrationalVote::IrrationalVote( const RationalVote& vote ) : Vote( vote.get_candidates() ), preferences_() {

}

// IrrationalVote
IrrationalVote::IrrationalVote( const set<string>& candidates, const map<pair<string,string>,int>& preferences ) : Vote(candidates), preferences_(preferences) {}
int IrrationalVote::beats( const string& c1, const string& c2 ) const {
    pair<string,string> matchup(c1,c2);
    map<pair<string,string>,int>::const_iterator i = preferences_.find( matchup );
    if( i != preferences_.end() ) {
        return i->second;
    }
    else {
        return -1;
    }
}

// get_preferences
map<pair<string,string>,int> IrrationalVote::get_preferences() const {
    return preferences_;
}

// is_rational
int IrrationalVote::is_rational() const {
    set<int> ints;
    for (int i = 0; i < candidates_.size() - 1; i++) {
        ints.insert( i );
    }
    
    int j = 0;
    set<string>::iterator i = candidates_.begin();
    set<string>::iterator c;
    
    while (i != candidates_.end()) {
        c = candidates_.begin();
        while( c != candidates_.end() ) {
            if( *c != *i ) { // this may be able to be removed in the future if
                             // vote verification allows for this to be checked sooner.
                pair<string,string> m1(*i,*c);
                pair<string,string> m2(*c,*i);
                if( preferences_.at(m1) == preferences_.at(m2) ) {
                    return 0;
                }
                else if( preferences_.at( m1 ) == 0 || preferences_.at( m1 ) == 1 ) {
                    j++;
                }
                else {
                    return 0;
                }
                //j++;
            }
            else {
                return 0;
            }
            c++;
        }
        if( !ints.erase( j ) ) {
            return 0;
        }
        j = 0;
        i++;
    }
    
    return 1;
}

// Cast to a rational vote.
IrrationalVote::operator RationalVote() const {
    if( is_rational() ) {
        set<string> candidates = candidates_;
        vector<string> vote;
        while( candidates.size() ) {
            set<string>::iterator s = candidates_.begin();
            string greatest_candidate = *s;
            while( s != candidates.end() ) {
                if( *s != greatest_candidate ) {
                    if( beats( *s, greatest_candidate ) ) {
                        greatest_candidate = *s;
                    }
                }
                ++s;
            }
            vote.push_back( greatest_candidate );
            candidates.erase( greatest_candidate );
        }
        return RationalVote( vote );
    }
    else {
        // No use in trying to make a vote if the vote isn't even rational.
        return RationalVote();
    }
}

// ostream <<
ostream& operator<<( ostream& out, const IrrationalVote& vote ) {
    map<pair<string,string>,int> scores = vote.get_preferences();
    set<string> candidates = vote.get_candidates();
    
    out << setw(10) << " ";
    set<string>::iterator i = candidates.begin(), j = i;
    while( j != candidates.end() ) {
        out << setw(10) << *j;
        j++;
    }
    out << "\n";
    while( i != candidates.end() ){
        j = candidates.begin();
        out << setw(10) << *i;
        while( j != candidates.end() ) {
            if( *i != *j ) {
                out << setw(10) << scores[pair<string,string>(*i,*j)];
            }
            else {
                out << setw(10) << "-";
            }
            ++j;
        }
        out << "\n";
        ++i;
    }    
    return out;
}

// IrrationalVote == IrrationalVote
int operator==( const IrrationalVote& v1, const IrrationalVote& v2 ) {
    return v1.get_candidates() == v2.get_candidates() && v1.get_preferences() == v2.get_preferences(); 
}

// IrrationalVote < IrrationalVote
int operator<( const IrrationalVote& v1, const IrrationalVote& v2 ) {
    set<string> c1(v1.get_candidates()), c2(v2.get_candidates());
    if( c1 == c2 ) {
        return v1.get_preferences() < v2.get_preferences();
    }
    else {
        return c1 < c2;
    }
}

// IrrationalVote > IrrationalVote
int operator>( const IrrationalVote& v1, const IrrationalVote& v2 ) {
    return v2 < v1;
}