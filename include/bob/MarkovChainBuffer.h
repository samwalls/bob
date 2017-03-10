#ifndef BOB_MARKOVCHAINKEY_H
#define BOB_MARKOVCHAINKEY_H

#include <string>
#include <functional>

namespace bob {

template<unsigned long SIZE>
struct MarkovChainBuffer {
  std::string data[SIZE];

  bool operator==(const MarkovChainBuffer<SIZE> &other) const {
    return data == other.data;
  }
};

}

namespace std {

template<unsigned long SIZE>
struct hash<bob::MarkovChainBuffer<SIZE>> {

  /// hash function for struct, allows use of type as a key in an unordered_map
  /// \cite copied and adapted directly from answer to StackOverflow question by user 'HolKann'
  /// http://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
  size_t operator()(const bob::MarkovChainBuffer<SIZE> &other) const {
    size_t seed = SIZE;
    hash<string> strHash;
    for (unsigned long i = 0; i < SIZE; i++) {
      seed ^= strHash(other.data[i]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

}

#endif //BOB_MARKOVCHAINKEY_H
