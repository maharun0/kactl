/**
 * Author: Maharun Afroz
 * Time: n log n + (log n)^2
 * Description: Merge Sort Tree (w point update)
 */
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class T>
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

using T = long long;
int N;
vector<T> vec;
vector<_multiset<ll>> segtree;

void buildTree(int node, int b, int e){ //n log n
    for (int i = b; i <= e; i++) {
        segtree[node].insert(vec[i]);
    }
    if(b==e)return;
    int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
    buildTree(ln, b, mid);
    buildTree(rn, mid+1, e);
}

T query(int node, int b, int e, int l, int r, T val){ //(log n)^2
    if(l > e or r < b) return 0;
    if(l<=b and r>=e) return segtree[node].order_of_key(val);
    int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
    T c1 = query(ln, b, mid, l, r, val);
    T c2 = query(rn, mid+1, e, l, r, val);
    return c1 + c2;
}

void setValue(int node, int b, int e, int ind, T val){
    segtree[node].erase(vec[ind]);
    segtree[node].insert(val);

    if(b==e)return;

    int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
    if (ind <= mid) setValue(ln, b, mid, ind, val);
    else setValue(rn, mid+1, e, ind, val);
}

void buildTree(vector<T>& input) {
    N = input.size();vec = input;
    int sz = N<<2; // 4n
    segtree.resize(sz);
    buildTree(1, 0, N-1);
}
T query(int l, int r, T val){return query(1, 0, N-1, l, r, val);}
void setValue(int ind, T val){
    setValue(1, 0, N-1, ind, val);
    vec[ind] = val;
}

/*
    vector<int> v(n); input(v);
    buildTree(v); // All 0 based index

    query(left-1, right-1, value);
    set(index-1, value);
*/