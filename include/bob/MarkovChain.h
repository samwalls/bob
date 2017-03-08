#ifndef BOB_MARKOVCHAIN_H
#define BOB_MARKOVCHAIN_H

#include <map>
#include <vector>
#include <string>

namespace bob {

/// A representation of the Markov chain required for a MarkovBot.
class MarkovChain {
 public:

  /// The default number of tokens to use as a key.
  static const size_t DEFAULT_KEY_BUFFER_SIZE = 2;

  /// The default number of tokens to use in the list of values mapped to by a key.
  static const size_t DEFAULT_VAL_BUFFER_SIZE = 1;

  /// Create a markov chain based on the passed tokens. The key buffer size determines how many tokens constitute a
  /// single key in the mapping of tokens to others; the value buffer size determines how many tokens constitute a
  /// mapped-to value.
  MarkovChain(std::vector<std::string> tokens, std::size_t keyBufferSize, std::size_t valBufferSize);

  /// Create a markov chain based on the passed tokens. Key and value buffer sizes are the defaults
  /// (DEFAULT_KEY_BUFFER_SIZE and DEFAULT_VAL_BUFFER_SIZE).
  MarkovChain(std::vector<std::string> tokens) : MarkovChain(tokens, DEFAULT_KEY_BUFFER_SIZE, DEFAULT_VAL_BUFFER_SIZE) {}

  /// Update the coincidental frequency between tokens and nextTokens.
  /// \return the coincidental frequency between tokens and nextTokens
  unsigned long update(std::vector<std::string> tokens, std::vector<std::string> nextTokens);

  /// \return the next tokens probabilistically likely to be seen next the seed tokens
  std::vector<std::string> next(std::vector<std::string> tokenSeeds);

 private:

  /// The number of tokens to use as a key.
  std::size_t keyBufferSize;

  /// The number of tokens to use in the list of values mapped to by a key.
  std::size_t valBufferSize;

  /// list of tokens
  std::vector<std::string> tokens;

  /// Analogous to "adjacency matrix": maps tokens -> token -> the frequency of the second token appearing directly
  /// after the first.
  std::map<std::vector<std::string>, std::map<std::vector<std::string>, unsigned long>> frequencies;

  /// Compute the coincidental frequency between tokens.
  /// \param keyBufferSize number of tokens to use as a key
  /// \param valBufferSize number of tokens to use in the list of values mapped to by a key
  void computeFrequency(std::vector<std::string> tokens, std::size_t keyBufferSize, std::size_t valBufferSize);

  /// Compute the coincidental frequency between tokens.
  void computeFrequency(std::vector<std::string> tokens);

  /// helper function to get a list, sliced from another list
  static std::vector<std::string> slice(std::vector<std::string> tokens, unsigned long position, unsigned long size) {
    std::vector<std::string> l = std::vector<std::string>();
    if (size > tokens.size() || position + size > tokens.size())
      throw std::invalid_argument("to slice, the size must fit within the input list");
    for (unsigned long i = 0; i < size; i++)
      l.push_back(tokens[position + i]);
    return l;
  }
};

}

#endif //BOB_MARKOVCHAIN_H
