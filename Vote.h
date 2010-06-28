#ifndef VOTE_H_
#define VOTE_H_
#include <set>
#include <string>
using namespace std;
class Vote {
    public:
        /**
         * Default constructor for a Vote.
         */
        Vote();
        Vote( const set<string>& candidates );
        /**
         * Determines whether or not c1 is preferred over c2.
         *
         * @return 1 if c1 is preferred over c2, 0 otherwise.
         */
        virtual int beats( const string& c1, const string& c2 ) const = 0; 
        /**
         * Obtains the set of candidates that this vote contains.
         *
         * @return The set of candidates in this vote.
         */
        set<string> get_candidates() const;
        //virtual static string get_identifier() const = 0;
    protected:
        set<string> candidates_;
        //virtual static string identifier = 0;
};
#endif
