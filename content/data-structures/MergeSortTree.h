/**
 * Author: Maharun Afroz
 * Time: n log n + (log n)2
 * Description: Merge Sort Tree
 */
template <class T>
struct SegmentTree{
private:
    int n;
    vector<vector<T>> tree;
    
    // Build Tree n log n
    void buildTree(const vector<T>& v, int node, int b, int e){
        if(b==e){tree[node] = {v[b]};return;}
        int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
        buildTree(v, ln, b, mid);
        buildTree(v, rn, mid+1, e);
        tree[node] = merge(tree[ln],tree[rn]);
    }

    // Merge Nodes (just sort two nodes or vectors)
    vector<int> merge(vector<int> &a, vector<int> &b) {
        vector<int> c;
        int i = 0, j = 0;
        while (i < a.size() and j < b.size()) {
            if (a[i] < b[j]) c.push_back(a[i++]);
            else c.push_back(b[j++]);
        }
        while (i < a.size()) c.push_back(a[i++]);
        while (j < b.size()) c.push_back(b[j++]);
        return c;
    }

    // do binary search on the sorted node array(ofc if in range)
    int get(vector<int> &v, int k){
        auto it = upper_bound(v.begin(), v.end(), k) - v.begin();
        // return it;   //number of elements strictly less than k in the range
        return v.size() - it;   //number of elements strictly greater than k in the range
        // return v.size() - it - 1;   //number of elements strictly greater than or equal to k in the range
    }

    int query(int node, int tL, int tR, int qL, int qR, int k) { (log n)^2
        if (tL >= qL && tR <= qR) {
            return get(tree[node], k);
        }
        if (tR < qL || tL > qR) {
            return 0;
        }
        int mid = (tL + tR) / 2;
        int QL = query(2 * node, tL, mid, qL, qR, k);
        int QR = query(2 * node + 1, mid + 1, tR, qL, qR, k);
        return QL + QR;
    }

public:
    int query(int l, int r, int k){return query(1, 0, n-1, l, r, k);}
    
    SegmentTree(const vector<T>& input) {
        n = input.size();
        int sz = n<<2; // 4n
        // tree.assign(vector<T>());
        tree.resize(sz);
        buildTree(input, 1, 0, n-1);
    }
};
// vector<int> v(n); cin >> v;
// SegmentTree<int> segTree(v); // All 0 based index
// segTree.query(left - 1, right - 1, k);