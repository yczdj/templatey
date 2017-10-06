#include <functional>

template <typename T>
struct SegmentTree {
	static const int maxn = 1e6;
	T tree[maxn * 2];
	int n;
	std::function<T(T, T)> op;

	void init(int n_, const std::function<T(T, T)> &op_) { n = n_, op = op_; }
	T& operator[] (int idx) { return tree[idx + n]; }//[0, n)

	void build() {
		for(int i = n - 1; i > 0; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
	}

	void update(int p, T val) {
		tree[p += n] = val;
		for(p >>= 1; p > 0; p >>= 1) tree[p] = op(tree[p << 1], tree[p << 1 | 1]);
	}
	T query(int l, int r) {//[l, r]
		int res = tree[l += n];
		for(++l, r += n + 1; l < r; l >>= 1, r >>= 1) {
			if(l & 1) res = op(res, tree[l++]);
			if(r & 1) res = op(res, tree[--r]);
		}
		return res;
	}
};

