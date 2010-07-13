#ifndef COUNTDOWN_H_
#define COUNTDOWN_H_
#include "PositionalScoreElection.h"
using namespace std;
class Countdown : public PositionalScoreElection {
public:
    Countdown( const set<string>& candidates );
    Countdown( const set<string>& candidates, const multiset< vector<string> >& votes ); 
    Countdown( const set<string>& candidates, const multiset< RationalVote >& votes );
    void change_countdown( int n );
    int get_countdown( int n ) const;
    int position_score( int position ) const;
protected:
    int countdown_start_;
};
#endif
