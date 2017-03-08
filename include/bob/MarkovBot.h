#ifndef BOB_MARKOVBOT_H
#define BOB_MARKOVBOT_H

#include "bob/Bot.h"
#include "bob/MarkovChain.h"

namespace bob {

class MarkovBot : public Bot {
 public:

  /// Constructor for a markov bot
  /// \param input an initial file to train the markov chain on
  MarkovBot(std::istream& input) : Bot(), chain(Bot::tokenize(input)) {}

  /// \param input the input to get a response for
  /// \return a response to the input string
  std::string response(std::string input);

 private:

  MarkovChain chain;
};

}

#endif //BOB_MARKOVBOT_H
