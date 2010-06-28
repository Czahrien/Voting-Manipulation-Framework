#ifndef PLURALITY_H_
#define PLURALITY_H_
#include "PositionalScoreElection.h"
using namespace std;
class Plurality : public PositionalScoreElection {
    public:
        Plurality( const set<string>& candidates );
        Plurality( const set<string>& candidates, const multiset< vector<string> >& votes ); 
        Plurality( const set<string>& candidates, const multiset< RationalVote >& votes );
        int position_score( int position ) const;
};
#endif
