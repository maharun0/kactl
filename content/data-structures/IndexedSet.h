/**
 * Author: Maharun Afroz
 * Source: Codeforces, Stackoverflow
 * Time: O(log N)
 * Description: PBDS Indexed Set | Order Statistics Tree
 */

// pbds set (with comparator)
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

struct Node { ll id, score, penalty; };

// comparator
namespace std { template<> struct less<Node> {
    bool operator() (const Node& a, const Node& b) const {
        if (a.score > b.score) return true;
        if (a.score == b.score) {
            if (a.penalty == b.penalty) return a.id < b.id;
            return a.penalty < b.penalty;
        }
        return false;
    }
};}

typedef tree<Node, null_type, less<Node>,
rb_tree_tag,tree_order_statistics_node_update> pbds;
// pbds s; s.insert(x);
// int value = *s.find_by_order(index);
// int index = s.order_of_key(value);