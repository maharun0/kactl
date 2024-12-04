/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
#pragma once

class HashedString {
  private:
	// change M and B if you want
	static const long long M = 1e9 + 9;
	static const long long B = 9973;

	// pow[i] contains B^i % M
	static std::vector<long long> pow;

	// p_hash[i] is the hash of the first i characters of the given string
	std::vector<long long> p_hash;
	std::vector<long long> s_hash;

  public:
	HashedString(const std::string &s) : p_hash(s.size() + 1) {
		// Ensure pow has enough elements to handle the string size
		while (pow.size() < s.size()) {
			pow.push_back((pow.back() * B) % M);
		}

		// Compute forward hash
		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}

		// Compute backward hash
		s_hash.resize(s.size() + 1);
		s_hash[s.size()] = 0;
		for (int i = s.size() - 1; i >= 0; --i) {
			s_hash[i] = ((s_hash[i + 1] * B) % M + s[i]) % M;
		}
	}

	long long fwd_hash(int start, int end) {
		long long raw_val = (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]) % M);
		return (raw_val % M + M) % M;
	}

	long long bwd_hash(int start, int end) {
		long long raw_val = (s_hash[start] - (s_hash[end + 1] * pow[end - start + 1]) % M);
		return (raw_val % M + M) % M;
	}

	bool isPalindrome(int start, int end) {
		return fwd_hash(start, end) == bwd_hash(start, end);
	}
};

std::vector<long long> HashedString::pow = {1};

