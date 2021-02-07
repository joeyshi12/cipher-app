#include <string>
#include <vector>

using namespace std;

namespace affineCipher 
{
    std::string encrypt(std::string plainText, std::pair<int, int> key);

    std::string decrypt(std::string cipherText, std::pair<int, int> key);

    void handle(std::vector<std::string> keyWords);
};