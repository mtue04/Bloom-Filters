#include "lib.h"

const int BLOOM_FILTER_SIZE = 1000;
bitset<BLOOM_FILTER_SIZE> usernameBF;
bitset<BLOOM_FILTER_SIZE> weakPasswordBF;


int h1(string& key) {
    long long int hash = 0;
    for (char c : key) {
        hash += static_cast<int>(c);
    }
    return hash % BLOOM_FILTER_SIZE;
}

int h2(string& key) {
    long long int hash = 1;
    for (char c : key) {
        hash *= static_cast<int>(c);
    }
    return hash % BLOOM_FILTER_SIZE;
}

int h3(string& key) {
    long long int hash = 0;
    for (char c : key) {
        hash -= static_cast<int>(c);
    }
    return (hash % BLOOM_FILTER_SIZE + BLOOM_FILTER_SIZE) % BLOOM_FILTER_SIZE;
}

int h4(string& key) {
    long long int hash = 0;
    for (char c : key) {
        hash ^= static_cast<int>(c);
    }
    return hash % BLOOM_FILTER_SIZE;
}

int h5(string& key) {
    long long int hash = 1;
    for (char c : key) {
        hash = hash * 31 + static_cast<int>(c);
    }
    return hash % BLOOM_FILTER_SIZE;
}

void addUsernameToBloomFilter(string username) {
    int index1 = h1(username);
    int index2 = h2(username);
    int index3 = h3(username);
    int index4 = h4(username);
    int index5 = h5(username);

    usernameBF[index1] = 1;
    usernameBF[index2] = 1;
    usernameBF[index3] = 1;
    usernameBF[index4] = 1;
    usernameBF[index5] = 1;
}

bool isUserExists(string username) {
    int index1 = h1(username);
    int index2 = h2(username);
    int index3 = h3(username);
    int index4 = h4(username);
    int index5 = h5(username);

    return usernameBF[index1] && usernameBF[index2] && usernameBF[index3] && usernameBF[index4] && usernameBF[index5];
}

void addWeakPasswordToBloomFilter(string password) {
    int index1 = h1(password);
    int index2 = h2(password);
    int index3 = h3(password);
    int index4 = h4(password);
    int index5 = h5(password);

    weakPasswordBF[index1] = 1;
    weakPasswordBF[index2] = 1;
    weakPasswordBF[index3] = 1;
    weakPasswordBF[index4] = 1;
    weakPasswordBF[index5] = 1;
}

bool isWeakPassword(string password) {
    int index1 = h1(password);
    int index2 = h2(password);
    int index3 = h3(password);
    int index4 = h4(password);
    int index5 = h5(password);

    return weakPasswordBF[index1] && weakPasswordBF[index2] && weakPasswordBF[index3] && weakPasswordBF[index4] && weakPasswordBF[index5];
}