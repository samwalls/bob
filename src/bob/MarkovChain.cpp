#include "bob/MarkovChain.h"

using namespace std;

namespace bob {

/*-------- PUBLIC --------*/

MarkovChain::MarkovChain(vector<string> tokens, size_t keyBufferSize, size_t valBufferSize) {
  this->tokens = tokens;
  this->frequencies = map<std::vector<string>, map<std::vector<string>, unsigned long>>();
  this->keyBufferSize = keyBufferSize;
  this->valBufferSize = valBufferSize;
  computeFrequency(tokens, keyBufferSize, valBufferSize);
}

unsigned long MarkovChain::update(vector<string> tokens, vector<string> nextTokens) {
  this->frequencies[tokens][nextTokens]++;
  return frequencies[tokens][nextTokens];
}

vector<string> MarkovChain::next(vector<string> tokenSeeds) {
  unsigned long seedLength = tokenSeeds.size();
  unsigned long position = 0;
  if (seedLength < this->keyBufferSize)
    throw invalid_argument("the list of seed tokens should be at least the length the key buffer size");
  vector<string> key = MarkovChain::slice(tokenSeeds, position, keyBufferSize);
  //TODO use frequency to determine the probability of choosing the next set of tokens
  map<vector<string>, unsigned long> values = this->frequencies[key];
  while (values.size() != 0) {
    //randomly choose from the map obtained from the key
    auto it = values.begin();
    advance(it, rand() % values.size());
    pair<vector<string>, unsigned long> entry = *it;
    vector<string> nextTokens = entry.first;
    //add the set of obtained values to the buffer
    for (string s : nextTokens)
      tokenSeeds.push_back(s);
    //take a new slice of the buffer for the key
    position++;
    key = MarkovChain::slice(tokenSeeds, position, keyBufferSize);
  }
  //remove the initial tokens
  auto rangeEnd = tokenSeeds.begin();
  advance(rangeEnd, seedLength);
  tokenSeeds.erase(tokenSeeds.begin(), rangeEnd);
  return tokenSeeds;
}

/*-------- PRIVATE --------*/

void MarkovChain::computeFrequency(vector<string> tokens, size_t keyBufferSize, size_t valBufferSize) {
  vector<string> keyBuffer;
  vector<string> valBuffer;
  //we need at least keyBufferSize elements before we can create a map entry
  for (unsigned int i = keyBufferSize; i < tokens.size() && i + keyBufferSize + valBufferSize < tokens.size(); i++) {
    keyBuffer = MarkovChain::slice(tokens, i, keyBufferSize);
    valBuffer = MarkovChain::slice(tokens, i + keyBufferSize, valBufferSize);
    update(keyBuffer, valBuffer);
  }
}

void MarkovChain::computeFrequency(vector<string> tokens) {
  computeFrequency(tokens, DEFAULT_KEY_BUFFER_SIZE, DEFAULT_VAL_BUFFER_SIZE);
}

}