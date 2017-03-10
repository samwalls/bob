#include "bob/MarkovChain.h"
#include "bob/MarkovChainBuffer.h"
#include <iostream>

using namespace std;

namespace bob {

/*-------- PUBLIC --------*/

MarkovChain::MarkovChain(vector<string> tokens, size_t keyBufferSize, size_t valBufferSize) {
  this->tokens = tokens;
  this->frequencies = unordered_map<MarkovChainBuffer<DEFAULT_KEY_BUFFER_SIZE>, std::unordered_map<MarkovChainBuffer<DEFAULT_VAL_BUFFER_SIZE>, unsigned long>>();
  this->keyBufferSize = keyBufferSize;
  this->valBufferSize = valBufferSize;
  computeFrequency(tokens, keyBufferSize, valBufferSize);
}

unsigned long MarkovChain::update(MarkovChainBuffer<DEFAULT_KEY_BUFFER_SIZE> tokens, MarkovChainBuffer<DEFAULT_VAL_BUFFER_SIZE> nextTokens) {
  if (frequencies.count(tokens) > 0)
    frequencies[tokens][nextTokens]++;
  else
    frequencies[tokens][nextTokens] = 1;
  unsigned long f = frequencies[tokens][nextTokens];
  return f;
}

vector<string> MarkovChain::next(vector<string> tokenSeeds) {
  unsigned long seedLength = tokenSeeds.size();
  unsigned long position = 0;
  //if (seedLength < this->keyBufferSize)
  //  throw invalid_argument("the list of seed tokens should be at least the length the key buffer size");
  //auto key = MarkovChain::slice<DEFAULT_KEY_BUFFER_SIZE>(tokenSeeds, position);
  auto it = frequencies.begin();
  advance(it, rand() % frequencies.size());
  auto key = it->first;
  //TODO use frequency to determine the probability of choosing the next set of tokens
  auto values = frequencies[key];
  while (values.size() != 0) {
    //randomly choose from the map obtained from the key
    auto it = values.begin();
    advance(it, rand() % values.size());
    auto nextTokens = it->first;
    //add the set of obtained values to the buffer
    for (string s : nextTokens.data)
      tokenSeeds.push_back(s);
    //take a new slice of the buffer for the key
    key = MarkovChain::slice<DEFAULT_KEY_BUFFER_SIZE>(tokenSeeds, ++position);
  }
  //remove the initial tokens
  auto rangeEnd = tokenSeeds.begin();
  advance(rangeEnd, seedLength);
  tokenSeeds.erase(tokenSeeds.begin(), rangeEnd);
  return tokenSeeds;
}

/*-------- PRIVATE --------*/

void MarkovChain::computeFrequency(vector<string> tokens, size_t keyBufferSize, size_t valBufferSize) {
  //we need at least keyBufferSize elements before we can create a map entry
  unsigned long tokenSize = tokens.size();
  for (unsigned int i = 0; i < tokenSize && i + keyBufferSize + valBufferSize < tokenSize; i++) {
    auto keyBuffer = MarkovChain::slice<DEFAULT_KEY_BUFFER_SIZE>(tokens, i);
    auto valBuffer = MarkovChain::slice<DEFAULT_VAL_BUFFER_SIZE>(tokens, i + keyBufferSize);
    update(keyBuffer, valBuffer);
    std::cout << i;
    std::cout << " / " << tokens.size() << std::endl;
  }
}

void MarkovChain::computeFrequency(vector<string> tokens) {
  computeFrequency(tokens, DEFAULT_KEY_BUFFER_SIZE, DEFAULT_VAL_BUFFER_SIZE);
}

}