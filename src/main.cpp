#include <bob.h>
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
  std::ifstream trainingFile(argv[1]);
  bob::Bot *bot = new bob::MarkovBot(trainingFile);
  std::string input;
  while (getline(std::cin, input) && input != "quit") {
    std::cout << bot->response(input) << std::endl;
  }
  std::cout << "bye" << std::endl;
  exit(0);
}