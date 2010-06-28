#ifndef VETO_H_
#define VETO_H_
#include "PositionalScoreElection.h"
using namespace std;
class Veto : public PositionalScoreElection {
    public:
        Veto( const set<string>& candidates );
        Veto( const set<string>& candidates, const multiset< vector<string> >& votes ); 
        Veto( const set<string>& candidates, const multiset< RationalVote >& votes );
        int position_score( int position ) const;
};
#endif
