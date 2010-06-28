#ifndef ELECTIONREGISTRY_H_
#define ELECTIONREGISTRY_H_
#include <set>
#include <string>
#include <map>
#include "Vote.h"
#include "Election.h"
#include "Creator.h"
using namespace std;
class ElectionRegistry {
    private:
        ElectionRegistry();
    public:
        static ElectionRegistry* get();
        void* create( const string& type, const set<string>& candidates ) const;
        void* create( const string& type, const set<string>& candidates, const multiset<Vote*>& votes ) const;
        void register_election( CreatorBase* creator );
    private:
        static ElectionRegistry* instance;    
        map<string, CreatorBase*> creator_;
};
#endif
