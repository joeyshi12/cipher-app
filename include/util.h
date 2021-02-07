#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

namespace util {
  vector<string> splitString(string input);

  int charToNum(char c);

  char numToChar(int n);

  void printHelp(vector<string> keyWords);

  int gcd(int a, int b);

  int totient(unsigned int n);

  int modInverse(int a, int n);
}
