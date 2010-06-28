#ifndef CREATOR_H_
#define CREATOR_H_
#include "CreatorBase.h"
/**
 * A Creator class for "dynamic" Election type allocation
 */
template<typename T>
class Creator : public CreatorBase {
    public:
        Creator() : CreatorBase() {}
    public:
        void* create( const set<string>& c, const multiset<Vote>& v ) const { 
            return new T( c, v );
        }

        void* create( const set<string>& c ) const {
            return new T( c );
        }
};
#endif
