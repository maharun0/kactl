/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Lazy Segment Tree
 * Time: O(\log N).
 */
template <class T>
struct LazySegtree{
private:
	int n;
	vector<T> tree;
	vector<T> addTree, setTree;
	
	void buildTree(const vector<T>& v, int node, int b, int e){
		if(b==e){tree[node] = v[b];return;}
		int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
		buildTree(v, ln, b, mid);
		buildTree(v, rn, mid+1, e);
		tree[node] = merge(tree[ln],tree[rn]);
	}
	
	void propagate(int node, int b, int e){
		int ln = node<<1, rn = ln+1;
		if(setTree[node]!=set_identity){
			addTree[node]=add_identity;
			tree[node] = setTree[node]*(e-b+1);
			if(b!=e){
				setTree[ln]=setTree[node];
				setTree[rn]=setTree[node];
			}
			setTree[node]=set_identity;
		}
		else{
			if(addTree[node]==add_identity) return;
			tree[node]+=addTree[node]*(e-b+1);
			if(b!=e){
				if(setTree[ln]==set_identity){
					addTree[ln]+=addTree[node];
				}
				else{
					setTree[ln]+=addTree[node];
					addTree[ln]=0;
				}
				if(setTree[rn]==set_identity){
					addTree[rn]+=addTree[node];
				}
				else{
					setTree[rn]+=addTree[node];
					addTree[rn]=0;
				}
				
			}
			addTree[node]=add_identity;
		}
	}

	T query(int node, int b, int e, int l, int r){
		propagate(node, b, e);
		if(l > e or r < b) return identity;
		if(l<=b and r>=e) return tree[node];
		int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
		T c1 = query(ln, b, mid, l, r);
		T c2 = query(rn, mid+1, e, l, r);
		return merge(c1,c2);
	}

	void range_set(int node, int b, int e, int l, int r, T val){
		propagate(node, b, e);
		if(l > e or r < b) return;
		if(l<=b and r>=e){
			setTree[node]=val;
			propagate(node, b, e);
			return;
		}
		int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
		range_set(ln, b, mid, l, r, val);
		range_set(rn, mid+1, e, l, r, val);

		tree[node]=merge(tree[ln],tree[rn]);
	}

	void range_update(int node, int b, int e, int l, int r, T val){
		propagate(node, b, e);
		if(l > e or r < b) return;
		if(l<=b and r>=e){
			addTree[node]+=val;
			propagate(node, b, e);
			return;
		}
		int mid = (b+e)>>1, ln = node<<1, rn = ln+1;
		range_update(ln, b, mid, l, r, val);
		range_update(rn, mid+1, e, l, r, val);

		tree[node]=merge(tree[ln],tree[rn]);
		return;
	}
	
public:
	T query(int l, int r){return query(1, 0, n-1, l, r);}
	void range_set(int l, int r, T value){ range_set(1, 0, n-1, l, r, value);}
	void range_update(int l, int r, T value){range_update(1, 0, n-1, l, r, value);}

	LazySegtree(const vector<T>& input) {
		n = input.size();
		int sz = n<<2; // 4n
		tree.resize(sz);
		addTree.resize(sz, add_identity);
		setTree.resize(sz, set_identity);
		buildTree(input, 1, 0, n-1);
	}
	
	T add_identity = 0;
	T set_identity = 0;
	T identity = 0;
	T merge(const T& a, const T& b) { return a + b; }
};

/* LazySegtree<int> segTree(v);
segTree.query(left-1, right-1);
segTree.range_set(left-1, right-1, value);
segTree.range_update(left-1, right-1, value); */