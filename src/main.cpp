#include "../include/util.h"
#include "../include/affine_cipher.h"
#include "../include/vigenere_cipher.h"
#include "../include/rsa_cipher.h"

int main() {
    util::printHelp({"help"});
    while (true) {
        std::string input;
        std::cout << "cipher-app> ";
        std::getline(std::cin, input);
        std::vector<std::string> keyWords = util::splitString(input);
        if (!keyWords.empty()) {
            if (keyWords[0] == "help") {
                util::printHelp(keyWords);
            } else if (keyWords[0] == "affine") {
                affineCipher::handle(keyWords);
            } else if (keyWords[0] == "rsa") {
                rsaCipher::handle(keyWords);
            } else if (keyWords[0] == "vigenere") {
                vigenereCipher::handle(keyWords);
            } else  if (keyWords[0] == "exit") {
                return 0;
            }
        }
    }
    return 0;
}
