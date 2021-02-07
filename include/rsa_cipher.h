#include <iostream>
#include <string>
#include <vector>

namespace rsaCipher
{
    std::string encrypt(std::string plainText, std::string key);

    std::string decrypt(std::string cipherText, std::string key);

    void handle(std::vector<std::string> keyWords);
};