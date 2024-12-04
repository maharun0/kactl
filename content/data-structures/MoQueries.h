/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: Answer interval or tree path queries by finding an approximate TSP through the queries,
 * and moving from one query to the next by adding/removing points at the ends.
 * If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */
#pragma once

// mos
// pbds set // more like a indexed set
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>,
rb_tree_tag,tree_order_statistics_node_update> pbds;

void getMoAnswer(vector<int>& v, vector<array<int, 5>>& queries, vector<int>& ans) {
    pbds oset; // ordered set
    auto add = [&](int x) -> void { oset.insert(v[x]); };
    auto remove = [&](int x) -> void { oset.erase(v[x]); };
    auto get = [&](int k) -> int { return *oset.find_by_order(k-1); };

    sort(all(queries));
    int left = 0, right = -1;
    for (auto& [b, r, l, idx, k] : queries) {
        while(right < r) add(++right);  while(right > r) remove(right--);
        while(left < l) remove(left++); while(left > l) add(--left);
        ans[idx] = get(k);
    }
}
// v = main array, // N = v.size()
queries.push_back({l/sqrtN, r, l, idx, k}); // for each query
// sort quiries according to -> starting block, and then r wise sort
// gives k'th smallest number's index in [l, r) rangereturn res;

// tree
vi moTree(vector<array<int, 2>> Q, vector<vi>& ed, int root=0){
	int N = sz(ed), pos[2] = {}, blk = 350; // ~N/sqrt(Q)
	vi s(sz(Q)), res = s, I(N), L(N), R(N), in(N), par(N);
	add(0, 0), in[0] = 1;
	auto dfs = [&](int x, int p, int dep, auto& f) -> void {
		par[x] = p;
		L[x] = N;
		if (dep) I[x] = N++;
		for (int y : ed[x]) if (y != p) f(y, x, !dep, f);
		if (!dep) I[x] = N++;
		R[x] = N;
	};
	dfs(root, -1, 0, dfs);
#define K(x) pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]] / blk & 1))
	iota(all(s), 0);
	sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
	for (int qi : s) rep(end,0,2) {
		int &a = pos[end], b = Q[qi][end], i = 0;
#define step(c) { if (in[c]) { del(a, end); in[a] = 0; } \
                  else { add(c, end); in[c] = 1; } a = c; }
		while (!(L[b] <= L[a] && R[a] <= R[b]))
			I[i++] = b, b = par[b];
		while (a != b) step(par[a]);
		while (i--) step(I[i]);
		if (end) res[qi] = calc();
	}
	return res;
}
