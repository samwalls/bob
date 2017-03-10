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
    std::string word;
    //[^!?.,:;=+\-_'`"}\)]
    const std::regex punctuation(R"(^([([{"`'])?(\w*)([)\]}"`'])?([!?.,:;=+\-_]*)$)");
    for (input >> word; !input.eof(); input >> word) {
      //we have a word, check for punctuation such as "," or ".".
      //3 groups, separating prefix punctuation, word, suffix punctuation and extra punctuation that may be considered
      //tokens in their own right, ".", ":", ";" etc..
      std::smatch match;
      if (std::regex_search(word, match, punctuation)) {
        if (match[1].str() != "") {
          std::string m = match[1].str();
          tokens.push_back(m);
        } if (match[2].str() != "") {
          std::string m = match[2].str();
          tokens.push_back(m);
        } if (match[1].str() != "" && match[3].str() != "") {
          std::string m = match[3].str();
          tokens.push_back(m);
        } if (match[4].str() != "") {
          std::string m = match[4].str();
          tokens.push_back(m);
        }
      } else
        tokens.push_back(word);
    }
    return tokens;
  }
};

}

#endif //BOB_BOT_H
