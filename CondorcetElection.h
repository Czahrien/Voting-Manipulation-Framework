/**
 * @file PositionalScoreElection.h
 * @author Benjamin Mayes <bdm8233@rit.edu>
 * @version 0.5
 *
 * @section LICENSE
 *
 * To Be Determined...
 * 
 * @section DESCRIPTION
 *
 * This is the header file of the PositionalScoreElection class. The PositionalScoreElection class represents an election consisting of rational votes which counts the votes with a rule that awards points based on the position of the candidate within the votes. This type of voting system is a generalization of several Borda counts, Plurality systems(with any constant number of candidates being voted for by each voter, and Veto systems. 
 */

#ifndef CONDORCETELECTION_H_
#define CONDORCETELECTION_H_
#include <map>
#include <set>
#include <vector>
#include <string>
#include "RationalVote.h"
#include "RationalElection.h"
using namespace std;
class CondorcetElection : public RationalElection {
public:
    /**
     * The default constructor.
     *
     * Initializes all of the private members to default values and initializes the candidates and votes to empty lists.
     */
    CondorcetElection();
    /**
     * The candidate constructor.
     *
     * Constructs an Election conisting of the candidates specified.
     *
     * @param candidates The candidates in the slection.
     */
    CondorcetElection( const set<string>& candidates );
    /**
     * The candidate and RationalVote constructor
     *
     * Constructs an Election consisting of the candidates and votes specified.
     *
     * @param candidates The candidates in the election.
     * @param votes The set of votes in the election.
     */
    CondorcetElection( const set<string>& candidates, const multiset< RationalVote >& votes );
public:
    /**
     * Adds a vote to the election.
     *
     * Adds a vote to the election and adds the score for the vote to the current score of the election.
     *
     * @param vote The vote to add to the election.
     * @return 0 if the addition of the vote fails because the vote is invalid, 1 if the addition succeeds.
     */
    int add_vote( const RationalVote& vote, int revalidate = 1 );
    /**
     * Removes a vote from the election.
     *
     * Removes the first instance of vote and subtracts the score of the vote from the current score of the election.
     *
     * @param vote The vote to remove from the election.
     * @return 0 if the vote is not in the election, 1 if the vote is found and successfully removed.
     */
    int remove_vote( const RationalVote& vote, int revalidate = 1 );
    /**
     * Adds a candidate to the election.
     *
     * @param candidate The candidate to add.
     * @return TODO - determine this.
     */
    int add_candidate( const string& candidate );
    /**
     * Removes a candidate from the election.
     *
     * @param candidate The candidate to remove.
     * @return TODO - determine this.
     */
    int remove_candidate( const string& candidate );
public:
    /**
     * Obtains a set of all the winners of this election.
     *
     * @return A set of all winners of this election or an empty set if the votes are uncounted.
     */
    set<string> get_winners() const;
    /**
     * Obtains the vote count.
     *
     * @return A map containing all of the candidates within the election and the number of votes they possess or an empty map if the votes are uncounted..
     */
    map<pair<string,string>,int> get_vote_count() const;
    /**
     * Used by subclasses to generate a vector used to determine positional scores.
     */
    set<string> beats( const string& candidate ) const;
protected:
    /**
     * Adds the specified vote to the total count based on the positional scoring rule.
     * 
     * @param vote The vote to add to the count.
     */
    void count_vote( const RationalVote& vote );
    /**
     * Adds the specified vote to the total count based on the positional scoring rule. 
     * 
     * @param vote The vote to add to the count .
     */
    void uncount_vote( const RationalVote& vote );
    
    /**
     * Initializes the PositionalScoreElection.
     */
    void init();
    /**
     * The scores in the current election.
     */
    map< pair<string,string>, int > current_scores_;
};
#endif
