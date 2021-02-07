#include "../include/vigenere_cipher.h"
#include "../include/util.h"

std::string vigenereCipher::encrypt(std::string plainText, std::string key)
{
    for (int i = 0; i < plainText.size(); i++)
    {
        plainText[i] = util::numToChar((util::charToNum(plainText[i]) + util::charToNum(key[i])) % 93);
    }
    return plainText;
}

std::string vigenereCipher::decrypt(std::string cipherText, std::string key)
{
    for (int i = 0; i < cipherText.size(); i++)
    {
        int num = (util::charToNum(cipherText[i]) - util::charToNum(key[i])) % 93;
        if (num < 0)
        {
            num += 93;
        }
        cipherText[i] = util::numToChar(num);
    }
    return cipherText;
}

void vigenereCipher::handle(std::vector<std::string> keyWords) 
{
    if (keyWords.size() != 4) {
        std::cout << "\ninvalid number of arguments\n" << std::endl;
        return;
    }
    if (keyWords[2].size() != keyWords[3].size()) {
        std::cout << "\ninvalid key length\n" << std::endl;
        return;
    }
    std::string key = keyWords[3];
    if (keyWords[1] == "encrypt") {
        std::cout << "\n" << encrypt(keyWords[2], key) << "\n" << std::endl;
    } else if (keyWords[1] == "decrypt") {
        std::cout << "\n" << decrypt(keyWords[2], key) << "\n" << std::endl;
    } else {
        std::cout << "\ninvalid task\n" << std::endl;
    }
}
