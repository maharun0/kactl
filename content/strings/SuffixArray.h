/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

// #pragma once
struct SuffixArray {
	vector<int> sa, lcp;

	SuffixArray(string& s, int lim = 256) {
		int n = s.size() + 1, k = 0, a, b;
		vector<int> x(s.begin(), s.end()), y(n), ws(max(n, lim));
		x.push_back(0), sa = lcp = y;
		iota(sa.begin(), sa.end(), 0);

		// Build suffix array using doubling approach
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j;
			iota(y.begin(), y.end(), n - j);  // Initialize y with indices from n-j to n-1
			for (int i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(ws.begin(), ws.end(), 0);  // Reset counting array
			for (int i = 0; i < n; i++) ws[x[i]]++;  // Count occurrences of ranks
			for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];  // Convert counts to positions
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];  // Sorting suffixes based on 1st part
			swap(x, y);
			p = 1, x[sa[0]] = 0;
			for (int i = 1; i < n; i++) {
				a = sa[i - 1], b = sa[i];
				x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;  // Compare suffixes
			}
		}

		// Compute LCP array
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1]; s[i + k] == s[j + k]; k++);
	}
};

void printSA(SuffixArray& sufa, string& s) {
	auto& lcp = sufa.lcp, sa = sufa.sa;
	for (int i = 1; i <= s.size(); i++)
		cout << lcp[i] << ' ' << sa[i] << ' ' << s.substr(sa[i]) << endl;
	cout << endl;
}

// // Create a SuffixArray object
// SuffixArray sufa(s);
// sufa.sa; // Suffix array 1 based
// sufa.lcp; // LCP array 1 based
// printSA(sufa, s); // prints SA, LCP, and substrings