#include "IrrationalVote.h"

IrrationalVote::IrrationalVote() : Vote(), candidates_(), preferences_() {}
IrrationalVote::IrrationalVote( const RationalVote& vote ) : Vote( vote.get_candidates() ), preferences_() {}
IrrationalVote::IrrationalVote( const set<string>& candidates, const map<pair<string,string>,int> preferences ) : Vote(candidates), preferences_(preferences) {}
int IrrationalVote::beats( string c1, string c2 ) const {
    pair<string,string> matchup(c1,c2);
    map<pair<string,string>,int>::const_iterator i = preferences_.find( matchup );
    if( i != preferences_.end() ) {
        return i->second;
    }
    else {
        return -1;
    }
}
map<pair<string,string>,int> IrrationalVote::get_preferences() const {
    return preferences_;
}

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
                j++;
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

/*IrrationalVote::operator RationalVote() const {
    if( is_rational() ) {
    
    }
    else {
        
    }
}*/