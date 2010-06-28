#include "ElectionRegistry.h"
ElectionRegistry* ElectionRegistry::instance = 0;

ElectionRegistry::ElectionRegistry() : creator_() {

}

ElectionRegistry* ElectionRegistry::get() {
    return instance;
}

void* ElectionRegistry::create( const string& type, const set<string>& candidates ) const {
    map<string,CreatorBase*>::const_iterator i = creator_.find( type );
    if( i != creator_.end() ) {
        return i->second->create( candidates );
    }
    else {
        return 0;
    }
}
void* ElectionRegistry::create( const string& type, const set<string>& candidates,  const multiset<Vote*>& votes ) const {
    map<string,CreatorBase*>::const_iterator i = creator_.find( type );
    if( i != creator_.end() ) {
        return i->second->create( candidates, votes );
    }
    else {
        return 0;
    }

}
void ElectionRegistry::register_election( CreatorBase* creator ) {

}
