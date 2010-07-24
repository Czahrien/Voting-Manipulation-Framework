#include "RationalVote.h"
#include <ostream>
using namespace std;

// RationalVote - default constructor
RationalVote::RationalVote() : Vote(), preference_order_() {}

// RationalVote
RationalVote::RationalVote( const vector<string>& preference_order ) : Vote(set<string>( preference_order.begin(), preference_order.end() ) ), preference_order_(preference_order) {
    //TODO: Some mechanism to verify that candidates_ and preference_order_ are of equal size;
}

// get_preference_order
vector<string> RationalVote::get_preference_order() const {
    return preference_order_; 
}

// win
set<string> RationalVote::win( const string& candidate ) const {
    std::vector<string>::const_iterator i = preference_order_.begin();

    while( i != preference_order_.end() && *(i++) != candidate );
    return set<string>(i, preference_order_.end());
}

// beats
int RationalVote::beats( const string& c1, const string& c2 ) const {
    vector<string>::const_iterator i = preference_order_.begin();

    while( i != preference_order_.end() ) {
        if( *i == c1 ) {
            return 1;
        }
        else if( *i == c2 ) {
            return 0;
        }
        i++;
    }
    return -1;
}

// cast to vector<string>
RationalVote::operator vector<string>() const {
    return preference_order_;
}

// cast to IrrationalVote
/*RationalVote::operator IrrationalVote() const {
    map<pair<string,string>,int> vote;
    vector<string>::const_iterator i = preference_order_.begin();
    vector<string>::const_iterator j;
    while( i != preference_order_.end() ) {
        j = i + 1;
        while( j != preference_order_.end() ) {
            vote[pair<string,string>(*i,*j)] = 1;
            vote[pair<string,string>(*j,*i)] = 0;
            j++;
        }
        i++;
    }
    IrrationalVote ret(candidates_, vote);
    return ret;
}*/

// ostream <<
ostream& operator<<( ostream& out, const RationalVote& vote ) {
    vector<string> order = vote.get_preference_order();
    if( order.size() > 0 ) {
        vector<string>::const_iterator i = order.begin();

        out << *(i++);

        while( i != order.end() ) {
            out << " > " << *(i++);
        }

    }
    return out;
}

// RationalVote < RationalVote
int operator<( const RationalVote& v1, const RationalVote& v2 ) {
    return v1.get_preference_order() < v2.get_preference_order();
}

// RationalVote > RationalVote
int operator>( const RationalVote& v1, const RationalVote& v2 ) {
    return v2 < v1;
}

// RationalVote == RationalVote
int operator==( const RationalVote& v1, const RationalVote& v2 ) {
    return v1.get_preference_order() == v2.get_preference_order();
}
