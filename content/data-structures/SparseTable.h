/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Sparse Table. Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  SparseTable<int> table(v);
 *  table.query(a, b); // [a, b) // index 0 based]
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
template<class T>
struct SparseTable {
    vector<vector<T>> jmp;
    SparseTable(const vector<T>& V) {
        int n = V.size();
        int log = 32 - __builtin_clz(n); // Maximum depth
        jmp.assign(log, V);
        for (int k = 1, pw = 1; pw * 2 <= n; ++k, pw *= 2)
            for (int i = 0; i + pw * 2 <= n; ++i)
                jmp[k][i] = min(jmp[k - 1][i], jmp[k - 1][i + pw]);
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a); // log2(b - a)
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};