#include <bob/MarkovBot.h>

#include <sstream>

using namespace std;

namespace bob {

/*-------- PUBLIC --------*/

std::string MarkovBot::response(std::string input) {
  stringstream ss;
  ss << input;
  vector<string> output = this->chain.next(Bot::tokenize(ss));
  ss.clear();
  for (string s : output)
    ss << s;
  return ss.str();
}

}