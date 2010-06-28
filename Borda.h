#ifndef BORDA_H_
#define BORDA_H_
#include "PositionalScoreElection.h"
using namespace std;
class Borda : public PositionalScoreElection {
    public:
        Borda( const set<string>& candidates );
        Borda( const set<string>& candidates, const multiset< vector<string> >& votes ); 
        Borda( const set<string>& candidates, const multiset< RationalVote >& votes );
        int position_score( int position ) const;
};
#endif
