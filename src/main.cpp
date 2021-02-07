#include "../include/util.h"
#include "../include/affine_cipher.h"
#include "../include/vigenere_cipher.h"
#include "../include/rsa_cipher.h"

int main(int argc, char const *argv[]) {
    while (true) {
        string input;
        cout << "cipher-app> ";
        getline(cin, input);
        vector<string> keyWords = util::splitString(input);
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
