/**
 * @file Election.h
 * @author Benjamin Mayes <bdm8233@rit.edu>
 * @version 0.5
 *
 * @section LICENSE
 *
 * To Be Determined...
 * 
 * @section DESCRIPTION
 *
 * This is the header file of the Election class. The Election class represents an election that is as general as possible (i.e. a very large number of systems can be built on top of it). 
 */

#ifndef ELECTION_H_
#define ELECEION_H_
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
template <typename T>
class Election {
    public:
        /**
         * The default constructor.
         *
         * Initializes all of the private members to default values and initializes the candidates and votes to empty lists.
        */
    Election() : candidates_(), votes_(), is_valid_(0), votes_counted_(1) { }
        /**
         * The candidate constructor.
         *
         * Constructs an Election conisting of the candidates specified.
         *
         * @param candidates The candidates in the slection.
         */
    Election( const set<string>& candidates ) : candidates_(candidates), votes_(), is_valid_(0), votes_counted_(1) { }
        /**
         * The candidate and Vote constructor
         *
         * Constructs an Election consisting of the candidates and votes specified.
         *
         * @param candidates The candidates in the election.
         * @param votes The set of votes in the election.
         */
    Election( const set<string>& candidates, const multiset<T>& votes ) : candidates_(candidates), votes_(votes), is_valid_(0), votes_counted_(0) { }
    public:
        /**
         * Adds a vote to the election.
         *
         * Adds a vote to the election and adds the score for the vote to the current score of the election.
         *
         * @param vote The vote to add to the election.
         * @return 0 if the addition of the vote fails because the vote is invalid, 1 if the addition succeeds.
         */
        int add_vote( const T& vote, int revalidate = 1 ) {
            if( !revalidate || validate_vote( vote ) ) {
                votes_.insert( vote );
                count_vote( vote );
                return 1;
            }
            else {
                return 0;
            }
        }
         
        /**
         * Removes a vote from the election.
         *
         * Removes the first instance of vote and subtracts the score of the vote from the current score of the election.
         *
         * @param vote The vote to remove from the election.
         * @return 0 if the vote is not in the election, 1 if the vote is found and successfully removed.
         */
    int remove_vote( const T& vote, int revalidate = 1 ) {
        typename multiset<T>::iterator i = votes_.find( vote );
        cout << (i != votes_.end()) << "\n";
        if( i != votes_.end() ) {
            // If the vote is invalid - the election may be valid
            if( revalidate && !validate_vote( vote ) ) {
                is_valid_ = validate_votes();
            }
            votes_.erase( i );
            uncount_vote( vote );
            return 1;
        }
        else {
            return 0;
        }
    }
        /**
         * Adds a candidate to the election.
         *
         * @param candidate The candidate to add.
         * @return TODO - determine this.
         */
        int add_candidate( const string& candidate ) {
            set<string>::iterator i = removed_candidates_.find( candidate );
            if( i != removed_candidates_.end() ) {
                candidates_.insert( candidate );
                removed_candidates_.erase( i );
                votes_counted_ = 0;
                count_votes();
            }
            return i != removed_candidates_.end();
        }
        /**
         * Removes a candidate from the election.
         *
         * @param candidate The candidate to remove.
         * @return TODO - determine this.
         */
        int remove_candidate( const string& candidate ) {
            set<string>::iterator i = candidates_.find( candidate );
            if( i != candidates_.end() ) {
                removed_candidates_.insert( candidate );
                candidates_.erase( i );
                votes_counted_ = 0;
                count_votes();
            }
            return i != candidates_.end();
        }
    public:
        /**
         * Counts all votes based on the positional scoring rule.
         */
        void count_votes() {
            if( !votes_.size() || !candidates_.size() ) {
                cerr << "ERROR: No votes or no candidates present in election.\n";
                return;
            }
            else if( !is_valid_ ) {
                return;
            }
            else if( votes_counted_ ) { 
                return;
            }
            else if( !votes_counted_ ) {
                clear_scores();
                set<string>::iterator j = candidates_.begin();
        
                typename multiset< T >::iterator i = votes_.begin();
                // Iterate through every vote in the multiset.
                while( i != votes_.end() ) {
                    count_vote( *i );
                    ++i;
                }
                votes_counted_ = 1;
            }
        }
       /**
         * Obtains a set of all the winners of this election.
         *
         * @return A set of all winners of this election or an empty set if the votes are uncounted.
         */
        virtual set<string> get_winners() const = 0;
        /**
         * Obtains a set of all the candidates that the chosen candidate has more votes than.
         *
         * @param The candidate to compare to all candidates.
         * @return A set containing all candidates that the chosen candidate has more votes than.
         */
        virtual set<string> beats( const string& candidate ) const = 0;
        /**
         * Checks a vote for validity.
         *
         * Assures that vote contains a complete ordering over the set of candidates - other candidates are allowed to be in the ordering provided that all of the candidates from the election are there.
         *
         * @param vote The vote to validate.
         * @return 0 if at least one candidate from this election's candidate set are missing - 1 otherwise.
         */
        virtual int validate_vote( const T& vote ) const = 0;
        /**
         * Validates all the votes in the election.
         *
         * Checks to see if all the votes in the election are a complete ordering of the candidates in the election.
         *
         * @return 0 if there is at least one invalid vote in the election - 1 otherwise
         */
        int validate_votes() const {
            typename multiset< T >::const_iterator i = votes_.begin();
            while( i != votes_.end() ) {
                if( !validate_vote( *i ) ) {
                    return 0;
                }
                i++;
            }
            return 1;
        }
        /**
         * Checks to see whether or not the election is valid.
         *
         * @return 1 if the election is valid, 0 otherwise.
         */
        int is_valid() const {
            return is_valid_;
        }
        int votes_counted() const {
            return votes_counted_;
        }
        /**
         * Obtains a list of the votes present in this election.
         */
        multiset<T> get_votes() {
            return votes_;
        }
        /**
         * Obtains a list of votes present in this election without repeated votes being shown.
         */
        set<T> get_vote_list() {
            set<T> ret( votes_.begin(), votes_.end() );
            return ret;
        }
        /**
         * Obtains a listing a votes mapping a vote to the number of times that it appears in
         * the election.
         */
        map<T,int> get_vote_numbers() {
            map<T,int> ret;
            typename multiset<T>::iterator i = votes_.begin();
            
            while( i != votes_.end() ) {
                ret[*i]++;
                ++i;
            }
            return ret;
        }
        /**
         * Erases all the votes within the Election.
         */
        void erase_votes() {
            clear_scores();
            votes_.clear();
        }
    protected:
        /**
        * Initializes the Election in a constructor independent manner.
        */
        void init() {
            clear_scores();
            if( validate_votes() ) {
                is_valid_ = 1;
                //TODO: Find a way to count votes here.
            } else {
                cerr << "At least one of the votes in this election are invalid.";
            }
        }
        /**
         * Adds the specified vote to the total count based on the positional scoring rule.
         * 
         * @param vote The vote to add to the count.
         */
        virtual void count_vote( const T& vote ) = 0;
        /**
         * Uncounts the first instance of the specified vote if it is
         * present in the election.
         */
        virtual void uncount_vote( const T& vote) = 0;
        /**
         * Erases the score-keeping data structure and recreates it from scratch.
         *
         * This function doubles as an initialization procedure.
         */
        virtual void clear_scores() = 0;
    protected:
        /**
         * The candidate set.
         */
        set<string> candidates_;
        /**
         * The removed candidate set.
         */
        set<string> removed_candidates_;
         /**
         * the set containing all votes
         */
        multiset<T> votes_;
         /**
         * boolean type variable used for determining whether the votes in the election are valid.
         */
        int is_valid_;
      /**
         * boolean type variable used for determining whether or not votes are counted.
         */
        int votes_counted_;
};
#endif
