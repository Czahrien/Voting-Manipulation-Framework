#ifndef RATIONALVOTE_H_
#define RATIONALVOTE_H_
#include <vector>
#include <set>
#include <string>
#include "Vote.h"
//#include "IrrationalVote.h"
using namespace std;
class RationalVote : public Vote {
    public:
        /**
         * Default Constructor
         */
        RationalVote();
        /**
         * Constructor that builds a vote from a vector.
         *
         * @param preference_list A total ordering of the candidates of the candidates.
         */
        RationalVote( const vector<string>& preference_list );
    public:
        /**
         * Obtains the preference order of the candidates in this election.
         *
         * @returns The preference order of the candidates.
         */
        vector<string> get_preference_order() const;
        /**
         * Returns the set of candidates ranked lower than candidate.
         * 
         * @param candidate The candidate.
         * @return A set containing all candidates ranked lower than candidate.
         */
        set<string> win( const string& candidate ) const;
        /**
         * Determines whether c1 beats c2 in the vote.
         *
         * @param c1 The preferred candidate.
         * @param c2 Another candidate.
         * @return 1 if c1 beats c2, 0 otherwise.
         */
        int beats( const string& c1, const string& c2 ) const;
        /**
         * Casts the vote to its underlying preference order in the form of a 
         * vector of strings.
         */
        operator vector<string>() const;
        //operator IrrationalVote() const;
    private:
        vector<string> preference_order_;
};

/**
 * Writes the RationalVote to an output stream.
 * 
 * @param out The output stream to write to.
 * @param vote The RationalVote to write to out.
 * @return a reference to out to allow "chaining" of the << operator.
 */
ostream& operator<<( ostream& out, const RationalVote& vote );
/**
 * Orders votes based on their candidate set then their preference order. This
 * ordering is guaranteed to be transitive, irreflexive, and asymmetric.
 *
 * @param v1 An RationalVote
 * @param v2 An RationalVote
 * @return 1 if v1 < v2 by the ordering scheme, 0 otherwise.
 */
int operator<( const RationalVote& v1, const RationalVote& v2 );
/**
 * Orders votes based on their candidate set then their preference order. This
 * ordering is guaranteed to be transitive, irreflexive, and asymmetric.
 *
 * @param v1 A RationalVote
 * @param v2 A RationalVote
 * @return The value obtained by v2 < v1.
 */
int operator>( const RationalVote& v1, const RationalVote& v2 );
/**
 * Checks two RationalVotes for equality.
 *
 * @param v1 A RationalVote
 * @param v2 A RationalVote
 * @return 1 if they are equal, 0 otherwise.
 */
int operator==( const RationalVote& v1, const RationalVote& v2 );
#endif
