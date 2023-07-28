#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
/*
        cre: https://vnspoj.github.io/wikivn/string/string-hashing
        'a' = 1 so the 'aa' or 'aaa' is different from 0
*/
//      Bloom Filter
long long compute_hash(string const& s) 
{
    const int p = 53;               //Uppercase + Lowercase = 52 (characters) => 53 is the Prime Number
    const int m = 1e9 + 9; 
    long long hash_value = 0;       
    long long p_pow = 1;        
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;      
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}
