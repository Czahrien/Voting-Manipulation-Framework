#include <iostream>
#include "PositionalScoreElection.h"

PositionalScoreElection::PositionalScoreElection() : RationalElection() {
    init();
}

PositionalScoreElection::PositionalScoreElection( const set<string>& candidates ) : RationalElection( candidates ) {
    init();
}

PositionalScoreElection::PositionalScoreElection( const set<string>& candidates, const multiset< RationalVote >& votes ) :RationalElection( candidates, votes ) {
    init();
}
        
void PositionalScoreElection::init() {
    is_valid_ = validate_votes();
    if( is_valid_ ) {
        //count_votes();
    }
    else {
        cerr << "Invalid election.\n";
    }
}

/*int PositionalScoreElection::add_vote( const RationalVote& vote, int revalidate ) {
    if( !revalidate || validate_vote( vote ) ) {
        votes_.insert( vote );
        count_vote( vote );
        return 1;
    }
    else {
        return 0;
    }
}

int PositionalScoreElection::remove_vote( const RationalVote& vote, int revalidate ) {
    multiset< RationalVote >::iterator i = votes_.find( vote );
    if( i != votes_.end() ) {
        // If the vote is invalid - the election may be valid
        if( revalidate && !validate_vote( vote ) ) {
            is_valid_ = validate_votes();
        }
        votes_.erase( i );
        return 1;
    }
    else {
        return 0;
    }
}*/


/*int PositionalScoreElection::add_candidate( const string& candidate ) {
    //FIND SAFE WAY TO IMPLEMENT
    //Considerations:
    // - Unique candidate names (set takes care of this, but how to notify user that they aren't doing it right?)
    // - How to handle votes not containing name of new candidate? Should the candidate be appended to the end of them? Should
    // this merely mark the election as invalid? Should there be way to remove invalid votes?
    //      - TODO: Allow new candidates to be inserted into votes. While not a fix, something good to have.
    // - Adding candidates must recount votes.
    return 0;
}

int PositionalScoreElection::remove_candidate( const string& candidate ) {
    //FIND SAFE WAY TO IMPLEMENT
    // Considerations:
    // - Find ways to count votes with extra candidates not in the election.
    //      - Efficiently.
    // - Should remove candidates be stored in a set?
    // - Removal of candidates must recount votes.
    return 0;
}*/

void PositionalScoreElection::count_votes() {
    if( !votes_.size() || !candidates_.size() ) {
        cerr << "ERROR: No votes or no candidates present in election.\n";
        return;
    }
    else if( !is_valid_ ) {
        cerr << "ERROR: Election is invalid, votes cannot be counted.\n";
        return;
    }
    else if( votes_counted_ ) { 
        return;
    }
    // initialize the score map
    current_scores_ = map<string,int>();
    set<string>::iterator j = candidates_.begin();

    while( j != candidates_.end() ) {
        current_scores_[*j] = 0;
        j++;
    }
    
    multiset< RationalVote >::iterator i = votes_.begin();

    // Iterate through every vote in the multiset and every candidate in each vote.
    // O(|V|*|C| * log|C| ) <= O(max(|V|,|C|))^3
    int n;
    vector<string>::iterator k;
    while( i != votes_.end() ) {
        RationalVote vote = *i;
        vector<string> v = vote.get_preference_order();
        vector<string>::iterator k = v.begin();
        n = 0;
        while( k != v.end() ) {
            string& name = *k;
            if( candidates_.find(name) != candidates_.end() ) {
                current_scores_[name] += position_score( n++ );
            }
            k++;
        }
        i++;
    }
    votes_counted_ = 1;
}

void PositionalScoreElection::count_vote( const RationalVote& vote ) {
    if( current_scores_.size() != candidates_.size() ) {
        // error condition.
        cerr << "Error counting the vote.\n";
    } else if ( !validate_vote( vote ) ) {
        cerr << "Vote is invalid.\n";
    } else if( !votes_counted_ ) {
        count_votes(); // TODO - Is this an issue? 
    } else {
        vector<string> v = vote.get_preference_order();
        vector<string>::const_iterator k = v.begin();
        int n = 0;
        while( k != v.end() ) {
            const string& c = *k;
            if( candidates_.find( c ) != candidates_.end() ) {
                current_scores_[c] += position_score( n++ );
            }
            k++;
        }
    }
}

void PositionalScoreElection::uncount_vote( const RationalVote& vote ) {
 //TODO: IMPLEMENT ME!   
}

set<string> PositionalScoreElection::get_winners() const {
    map<string,int>::const_iterator i = current_scores_.begin();
    int max_score = 0;
    set<string> win;

    while( i != current_scores_.end() ) {
        if( i->second > max_score ) {
            max_score = i->second;
            win.erase( win.begin(), win.end() );
            win.insert( i->first );
        }
        else if( i->second == max_score ) {
            win.insert( i->first );
        }
        i++;
    }

    return win;
}

map<string,int> PositionalScoreElection::get_vote_count() const {
    //TODO: add error checks
    return current_scores_;
}

set<string> PositionalScoreElection::beats( const string& candidate ) const {
    map<string,int>::const_iterator i = current_scores_.find( candidate );
    if( i != current_scores_.end() ) { 
        int threshold = i->second;
        i = current_scores_.begin();
        set<string> losers;
        
        while( i != current_scores_.end() ) {
            if( i->second < threshold ) {
                losers.insert( i->first );
            }
            i++;
        }
        return losers;
    }
    else 
        return set<string>();
}
