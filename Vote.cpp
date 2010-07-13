#include "Vote.h"

// Vote - default constructor
Vote::Vote() {}

// Vote
Vote::Vote( const set<string>& candidates ): candidates_( candidates ) {}
set<string> Vote::get_candidates() const {
    return candidates_;
}
