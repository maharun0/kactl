/**
 * Author: Maharun Afroz
 * Source: Codeforces
 * Time: O(log N)
 * Description: PBDS Indexed Multiset
 */

// pbds multiset // more like a indexed multiset
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T>
class _multiset{
	using MS = tree<T, null_type, less_equal<T>, 
	rb_tree_tag, tree_order_statistics_node_update>;
	MS s;
public:
	_multiset(){s.clear();}
	void erase(T xx){s.erase(s.upper_bound(xx));}
	typename MS::iterator lower_bound(T xx){return s.upper_bound(xx);}
	typename MS::iterator upper_bound(T xx){return s.lower_bound(xx);}
	// same
	size_t size(){return s.size();}
	void insert(T xx){s.insert(xx);}
	T find_by_order(int xx){return s.find_by_order(xx);}
	int order_of_key(T xx){return s.order_of_key(xx);}
	void erase(typename MS::iterator xx){s.erase(xx);}
};