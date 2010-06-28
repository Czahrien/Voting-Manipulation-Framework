#ifndef IRRATIONALVOTE_H_
#define IRRATIONALVOTE_H_
#include <map>
#include <set>
#include <string>
#include <vector>
#include "RationalVote.h"
using namespace std;
class IrrationalVote : public Vote {
    public:
        /**
         * Default constructor for a Vote.
         */
        IrrationalVote();
        /**
         * Constructor for an IrrationalVote which takes a RationalVote.
         *
         * @param vote The RationalVote
         */
        IrrationalVote( const RationalVote& vote );
        /**
         * Constructs an IrrationalVote from a set of candidates and an
         * (irreflexive) asymmetric matrix that is |C|*|C| in size.
         *
         * @param candidates The set of candidates.
         * @param preference The (candidates.size())^2 matrix of preferences.
         */
        IrrationalVote( const set<string>& candidates, const map<pair<string,string>,int> preferences );
        /**
         * Determines whether or not c1 is preferred over c2.
         *
         * @return 1 if c1 is preferred over c2, 0 otherwise.
         */
        int beats( string c1, string c2 ) const;
        /**
         * Obtains the preferences of the voter.
         *
         * @return a vector of vectors representing an |C|*|C| matrix which
         * show the preferences of the voter.
         */
        map<pair<string,string>,int> get_preferences() const;
        /**
         * Obtains the list of candidates this vote is over.
         *
         * @return the list of canddates represented by this vote.
         */
        int is_rational() const;
        //operator RationalVote() const
    private:
            set<string> candidates_;
            map<pair<string,string>,int> preferences_;
};

ostream& operator<<( ostream& out, const IrrationalVote& vote );
int operator==( const IrrationalVote& v1, const IrrationalVote& v2 );
int operator<( const IrrationalVote& v1, const IrrationalVote& v2 );
int operator>( const IrrationalVote& v1, const IrrationalVote& v2 );
#endif
