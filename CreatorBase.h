#ifndef CREATORBASE_H_
#define CREATORBASE_H_
/**
 * CreatorBase is a non-templated pure virtual base class for the templated type Creator.
 */
class CreatorBase {
    public: 
        CreatorBase();
    public:
        virtual void* create( const set<string>& c ) const = 0;
        virtual void* create( const set<string>& c, const multiset<Vote*>& c ) const = 0;
};
#endif
