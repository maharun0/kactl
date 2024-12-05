/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting. Given is an oriented graph.
 * Output is an ordering of vertices, such that there are edges only from left to right.
 * If there are cycles, the returned list will have size smaller than $n$ -- nodes reachable
 * from cycles will not be returned.
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
#pragma once

vi topoSort(const vector<vi>& gr) {
	vi indeg(sz(gr)), q;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	rep(i,0,sz(gr)) if (indeg[i] == 0) q.push_back(i);
	rep(j,0,sz(q)) for (int x : gr[q[j]])
		if (--indeg[x] == 0) q.push_back(x);
	return q;
}
// Method 2 (my method)
// Topological sort in DAG (using DFS)
#define clear_graph(n) for(int i=0;i<=n;i++){g[i].clear(),vis[i]=false;} path.clear(); nodes = set<int>();
const int N = 1e5+10;
vector<int> g[N];
bool vis[N];

deque<int> path; // path in assending order
set<int> nodes; // all distinct nodes

void dfs(int vertex){
	vis[vertex] = true;
	for (int child : g[vertex]) if(!vis[child]) dfs(child);
	path.push_front(vertex);
}
// run dfs from each node
void TopSort() { for (auto& i : nodes) if (!vis[i]) dfs(i); }
// print(path);

