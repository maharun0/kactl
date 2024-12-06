/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * Description: Pre-computation of modular inverses. Assumes LIM $\le$ mod and that mod is a prime.
 * Status: Works
 */
#pragma once
// Method 1
// const ll m = 1000000007, N = 200000; ///include-line
ll inv[N]; inv[1] = 1;
for (ll i=2; i<N; ++i) inv[i] = m - (m/i) * inv[m%i] % m;

// Method 2
const ll m = (ll)1e9+7;
ll binpow(ll a, ll b) { // log b
    a %= m; ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m; b >>= 1;
    }
    return res;
}
ll mod_inv(ll a) { return binpow(a, m-2); } // 1 / a
vector<ll> invOf = {0, mod_inv(1), mod_inv(2)};
