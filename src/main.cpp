#include <bob.h>
#include <iostream>

int main(int argc, char** argv) {
  bob::Bot bot = bob::Bot();
  std::cout << bot.response("hello") << std::endl;
  exit(0);
}