/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * Description: For each position in a string, computes p[0][i] = half length of
 *  longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

struct Manacher {
	array<vector<int>, 2> p;

	Manacher(const string& s) {
		int n = s.size();
		p = {vector<int>(n+1), vector<int>(n)};
		for (int z = 0; z < 2; z++) {
			int l = 0, r = 0;
			for (int i = 0; i < n; i++) {
				// use previous value if mirror value already calculated
				if (i < r) {
					int dist_from_r = r - i + !z;
					int mirror_idx = l + dist_from_r;
					p[z][i] = min(dist_from_r, p[z][mirror_idx]);
				}
				// expand palindrome around i
				int L = i - p[z][i], R = i + p[z][i] - !z;
				while (L > 0 and R < n-1 and s[L-1] != s[R+1]) { p[z][i]++; L--; R++; }
				if (R > r) { l = L; r = R; }
			}
		}
	}
	bool isPalindrome(int l, int r) {
		int len = r - l + 1;
		int mid_idx = (l + r + 1) / 2;
		int radius = p[(len & 1)][mid_idx];
		return (radius * 2 + 1 >= len);
	}
};
// Manacher mana(s);
// radius of palindrome at index i is p[i]
// print(mana.p[0]); // even len palindromes
// print(mana.p[1]);// odd len palindromes