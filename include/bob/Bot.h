#ifndef BOB_BOT_H
#define BOB_BOT_H

#include <istream>
#include <string>
#include <list>
#include <regex>

namespace bob {

class Bot {
 public:

  Bot() {}

  /// \param input the input to get a response for
  /// \return a response to the input string
  virtual std::string response(std::string input) = 0;

 protected:

  /// Properly tokenize the input such that it is usable for the bot.
  static std::vector<std::string> tokenize(std::istream& input) {
    std::vector<std::string> tokens = std::vector<std::string>();
    for (std::string word; !word.empty(); input >> word) {
      //we have a word, check for punctuation such as "," or ".".
      //3 groups, separating prefix punctuation, word, suffix punctuation and extra punctuation that may be considered
      //tokens in their own right, ".", ":", ";" etc..
      std::regex punctuation("([([{\"`']?)([^!?.,:;=+\\-_'`\"}\\)]*)([([{\"`']?)([!?.,:;=+\\-_])*");
      std::smatch match;
      if (std::regex_search(word, match, punctuation)) {
        for (unsigned int i = 1; i < match.size(); i++)
          tokens.push_back(match[i].str());
      } else
        tokens.push_back(word);
    }
    return tokens;
  }
};

}

#endif //BOB_BOT_H
