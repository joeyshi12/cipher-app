#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>

namespace util {
  std::vector<std::string> splitString(std::string input);

  int charToNum(char c);

  char numToChar(int n);

  void printHelp(std::vector<std::string> keyWords);

  int totient(unsigned int n);

  int modInverse(int a, int n);
}
