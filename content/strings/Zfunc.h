/**
 * Author: chilli
 * License: CC0
 * Description: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

// Z-algorithm to compute the Z-array
vector<int> Z(const string& S) {
	int n = S.size(); 
	vector<int> z(n);
	int l = -1, r = -1;
	
	// Loop to compute the Z-array in linear time
	for (int i = 1; i < n; ++i) {
		z[i] = (i >= r) ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < n && S[i + z[i]] == S[z[i]]) z[i]++;
		if (i + z[i] > r) { l = i; r = i + z[i]; }
	}
	return z;
}

// Time complexity of Z function: O(n), where n is the length of string S

vector<int> pattern_matching(const string& pattern, const string& text) {
	string combined = pattern + "#" + text; // Concatenate pattern, delimiter, and text
	vector<int> z = Z(combined); // Z-function on combined string
	vector<int> occurrences;
	int p_len = pattern.size();
	
	// Loop to find all occurrences of the pattern in the text
	for (int i = p_len + 1; i < combined.size(); ++i) {
		if (z[i] >= p_len) occurrences.push_back(i - p_len - 1);
	}
	return occurrences;
}

// Time complexity of pattern_matching function:
// The Z-function runs in, where p_len is the length of the pattern and t_len is the length of the text.
// Iterating through the Z-array to find occurrences takes O(p_len + t_len) time.
// Overall time complexity: O(p_len + t_len)
vector<int> occ = pattern_matching(pattern, text);