#include <unordered_set>
#include <algorithm>
#include "lexgen/dfa_state.h"

struct DFAStateHashingFunction{
    size_t operator()(const DFAState& d) const{
        std::string s;
        for(auto n: d.get_generators()){
            s += std::to_string(n->getId());
        }
        sort(s.begin(), s.end());
        return std::hash<string>()(s);
    }
};