/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
template <typename T>
struct SegmentTree {
    static constexpr T identity = INT_MIN;
    T f(T a, T b) { return max(a, b); }
    int n; vector<T> s;
    SegmentTree(int n = 0, T def = identity) : n(n), s(2*n, def),  {}
    SegmentTree(const vector<T>& v) : n(n), s(2*n, identity),
        { for (int i = 0; i < n; i++) { set(i, v[i]); } }
    void set(int pos, T val) {
        for (s[pos += n] = val; pos >>= 1;)
            s[pos] = f(s[pos<<1], s[pos<<1 | 1]);
    }
    void update(int pos, T val) {
        for (s[pos += n] += val; pos >>= 1;)
            s[pos] = f(s[pos<<1], s[pos<<1 | 1]);
    }
    T query(int b, int e) {
        T ra = identity, rb = identity;
        for (b += n, e += n; b < e; b >>= 1, e >>= 1) {
            if (b & 1) ra = f(ra, s[b++]);
            if (e & 1) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};
// SegmentTree<int> segTree(v);
// segTree.query(left-1, right); [l, r)
// segTree.set(index-1, increasingValue);

template <class T>
struct SegmentTree{
private:
    int n;
    vector<T> tree;
    
    void buildTree(const vector<T>& v, int node, int b, int e){
        if(b==e){tree[node] = v[b];return;}
        int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
        buildTree(v, ln, b, mid);
        buildTree(v, rn, mid+1, e);
        tree[node] = merge(tree[ln],tree[rn]);
    }

    T query(int node, int b, int e, int l, int r){
        if(l > e or r < b) return identity;
        if(l<=b and r>=e) return tree[node];
        int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
        T c1 = query(ln, b, mid, l, r);
        T c2 = query(rn, mid+1, e, l, r);
        return merge(c1,c2);
    }
    
    void set(int node, int b, int e, int ind, T val){
        if(ind > e or ind < b) return;
        if(ind<=b and ind>=e){
            tree[node] = val; 
            return;
        }
        int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
        if (ind <= mid) set(ln, b, mid, ind, val);
        else set(rn, mid+1, e, ind, val);
        tree[node] = merge(tree[ln],tree[rn]);
    }

    void update(int node, int b, int e, int ind, T val){
        if(ind > e or ind < b) return;
        if(ind<=b and ind>=e){
            tree[node] = merge(tree[node], val);
            return;
        }
        int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
        if (ind <= mid) update(ln, b, mid, ind, val);
        else update(rn, mid+1, e, ind, val);
        tree[node] = merge(tree[ln],tree[rn]);
    }

public:
    T query(int l, int r){return query(1, 0, n-1, l, r);}
    void set(int ind, T val){set(1, 0, n-1, ind, val);}
    void update(int ind, T val){update(1, 0, n-1, ind, val);}
    
    SegmentTree(const vector<T>& input) {
        n = input.size();
        int sz = n<<2; // 4n
        tree.resize(sz);
        buildTree(input, 1, 0, n-1);
    }

    T merge(const T& a, const T& b) { return a + b; }
    T identity = 0;
};

/*
    vector<int> v(n); cin >> v;

    SegmentTree<int> segTree(v); // All 0 based index

    segTree.query(left-1, right-1);
    segTree.set(index-1, value);
    segTree.update(index-1, increasingValue);
*/
