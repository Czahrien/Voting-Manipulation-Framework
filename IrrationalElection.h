/*
 *  IrrationalElection.h
 *  VMF
 *
 *  Created by bdm on 6/23/10.
 *  Copyright 2010 Rochester Institute of Technology. All rights reserved.
 *
 */

#ifndef IRRATIONALELECTION_H_
#define IRRATIONALELECTION_H_
#include <set>
#include <map>
#include <string>
#include "Election.h"
#include "IrrationalVote.h"

using namespace std;
class IrrationalElection : public Election<IrrationalVote> {
public:
    IrrationalElection();
    IrrationalElection( const set<string>& candidates );
    IrrationalElection( const set<string>& candidates, const multiset< IrrationalVote >& votes );
    int validate_vote( const IrrationalVote& vote ) const;
    void init();
protected:
    map<pair<string,string>,double> scores_;
};
#endif
