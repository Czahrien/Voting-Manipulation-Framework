#ifndef IRRATIONALVOTE_H_
#define IRRATIONALVOTE_H_
#include <map>
#include <set>
#include <string>
#include <vector>
#include "RationalVote.h"
// EPSILON is used in floating point number comparison.
#define EPSILON 0.001f
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
        IrrationalVote( const set<string>& candidates, const map<pair<string,string>,double> preferences );
        /**
         * Determines whether or not c1 is preferred over c2.
         *
         * @return 1 if c1 is preferred over c2, 0 otherwise.
         */
        int beats( const string& c1, const string& c2 ) const;
        /**
         * Obtains the preferences of the voter.
         *
         * @return a vector of vectors representing an |C|*|C| matrix which
         * show the preferences of the voter.
         */
        map<pair<string,string>,double> get_preferences() const;
        /**
         * Obtains the list of candidates this vote is over.
         *
         * @return the list of canddates represented by this vote.
         */
        int is_rational() const;
        //operator RationalVote() const
    private:
            set<string> candidates_;
            map<pair<string,string>,double> preferences_;
};

/**
 * Writes the IrrationalVote to an output stream.
 * 
 * @param out The output stream to write to.
 * @param vote The IrrationalVote to write to out.
 * @return a reference to out to allow "chaining" of the << operator.
 */
ostream& operator<<( ostream& out, const IrrationalVote& vote );
/**
 * Checks two IrrationalVotes for equality.
 *
 * @param v1 An IrrationalVote
 * @param v2 An IrrationalVote
 * @return 1 if they are equal, 0 otherwise.
 */
int operator==( const IrrationalVote& v1, const IrrationalVote& v2 );
/**
 * Orders votes based on their candidate set then their preference order. This
 * ordering is guaranteed to be transitive, irreflexive, and asymmetric.
 *
 * @param v1 An IrrationalVote
 * @param v2 An IrrationalVote
 * @return 1 if v1 < v2 by the ordering scheme, 0 otherwise.
 */
int operator<( const IrrationalVote& v1, const IrrationalVote& v2 );
/**
 * Orders votes based on their candidate set then their preference order. This
 * ordering is guaranteed to be transitive, irreflexive, and asymmetric.
 *
 * @param v1 An IrrationalVote
 * @param v2 An IrrationalVote
 * @return The value obtained by v2 < v1.
 */
int operator>( const IrrationalVote& v1, const IrrationalVote& v2 );
#endif
