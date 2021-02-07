#include "../include/affine_cipher.h"
#include "../include/util.h"

std::string affineCipher::encrypt(std::string plainText, std::pair<int, int> key)
{
    int a = key.first;
    int b = key.second;
    for (int i = 0; i < plainText.size(); i++) {
        int n = (a * util::charToNum(plainText[i]) + b) % 93;
        plainText[i] = util::numToChar(n);
    }
    return plainText;
}

std::string affineCipher::decrypt(std::string cipherText, std::pair<int, int> key)
{
    int a_prime = util::modInverse(key.first, 93);
    int b_prime = (-a_prime * key.second) % 93;
    if (b_prime < 0)
    {
        b_prime += 93;
    }
    return encrypt(cipherText, std::make_pair(a_prime, b_prime));
}

void affineCipher::handle(std::vector<std::string> keyWords) {
    if (keyWords.size() != 5) {
        std::cout << "\ninvalid number of arguments\n" << std::endl;
        return;
    }
    int a; int b;
    try {
        a = stoi(keyWords[3]);
        b = stoi(keyWords[4]);
    } catch (const std::exception& e) {
        std::cout << "\ninvalid key\n" << std::endl;
        return;
    }
    std::pair<int, int> key = std::make_pair(a, b);
    if (keyWords[1] == "encrypt") {
        if (util::gcd(a, 93) != 1) {
            std::cout << "WARNING: a is not coprime to 93" << std::endl;
        }
        std::cout << "\n" << encrypt(keyWords[2], key) << "\n" << std::endl;
    } else if (keyWords[1] == "decrypt") {
        if (util::gcd(a, 93) != 1) {
            std::cout << "\nmod inverse does not exist\n" << std::endl;
            return;
        }
        std::cout << decrypt(keyWords[2], key) << std::endl;
    } else {
        std::cout << "\ninvalid task\n" << std::endl;
    }
}
