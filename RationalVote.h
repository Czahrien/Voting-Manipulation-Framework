#ifndef RATIONALVOTE_H_
#define RATIONALVOTE_H_
#include <vector>
#include <set>
#include <string>
#include "Vote.h"
using namespace std;
class RationalVote : public Vote {
    public:
        RationalVote();
        RationalVote( const vector<string>& preference_list );
        vector<string> get_preference_order() const;
        set<string> win( const string& candidate ) const;
        int beats( const string& c1, const string& c2 ) const;    
        operator vector<string>() const;
        //operator IrrationalVote() const;
        //vector< vector<int> > get_preferences() const;
    private:
        vector<string> preference_order_;
};

ostream& operator<<( ostream& out, const RationalVote& vote );
int operator<( const RationalVote& v1, const RationalVote& v2 );
int operator>( const RationalVote& v1, const RationalVote& v2 );
int operator==( const RationalVote& v1, const RationalVote& v2 );
#endif
