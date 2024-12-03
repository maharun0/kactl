// Random input generator
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);
int myrand(int mod) {
    return mt()%mod;
}
// Generates a random number within 100
// int random_num = myrand(100) + 1; 