// Bit stuffs
#define isOdd(n) n&1
#define isEven(n) !(n&1)

#define div2pk(n, k) n>>k // n / pow(2, k)
#define mul2pk(n, k) n<<k // n * pow(2, k)

#define isDiv2pK(n, k) !(n & ((1<<k)-1)) // n % pow(2, k) == 0
#define isPowOf2(n) n && !(n&(n-1))

#define set(n, pos) (n |= (1<<pos))
#define unset(n, pos) (n &= ~(1<<pos))
#define flip(n, pos) (n ^= (1<<pos))
#define getBit(n, pos) (n & (1<<pos))

// #pragma GCC target("popcnt")

#define posL1(n) 32-__builtin_ctz(n)
#define posR1(n) __builtin_ffs(n)

#define clearL1(n) n ^= (1 << (32-__builtin_ctz(n)-1))
#define clearR1(n) n &= (n-1)

#define countSetBits(n) __builtin_popcount(n)

// bitset
bitset<64> a, b(value), c("1011");

b.test(i); b[i]; // test i'th bit

// works on i'th bit or all
b.set(i); b.set(); 
b.reset(i); b.reset();
b.flip(i);b.flip();
b.count(); // counts set bits

b.to_string();
b.to_ulong();b.to_ullong();