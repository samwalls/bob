#ifndef BOB_BOT_H
#define BOB_BOT_H

#include <string>

namespace bob {

class Bot {
 public:

  /// Constructor for a Bot
  Bot();

  /// \param input the input to get a response for
  /// \return a response to the input string
  std::string response(std::string input);
};

}

#endif //BOB_BOT_H
