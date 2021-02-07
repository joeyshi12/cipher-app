#include "../include/util.h"

std::vector<std::string> util::splitString(std::string input) {
    if (input.size() == 0) {
        return {};
    }
    std::istringstream iss(input);
    std::vector<std::string> results{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    return results;
}

int util::charToNum(char c) {
    if (c < 33 || c > 176) {
        std::cout << "INVALID LETTER: " << c << std::endl;
        return -1;
    }
    return (int) c - 33;
}

char util::numToChar(int n) {
    if (n < 0 || n >= 93) {
        std::cout << "INVALID NUMBER: " << n << std::endl;
        return (char) ' ';
    }
    return (char) (n + 33);
}

void util::printHelp(std::vector<std::string> keyWords) {
    std::string message;
    if (keyWords.size() == 2) {
        if (keyWords[1] == "affine") {
            message = "\naffine - a type of encryption with a key (a, b)\n"
                      "C = a*P + b (mod 93), where a is coprime to 93\n"
                      "affine <encrypt/decrypt> <text> <a> <b>\n";
        } else if (keyWords[1] == "rsa") {
            message = "\nrsa - a type of encryption with a key (e, n)\n"
                      "C = P^e (mod n), where e is coprime to totient(n), and n is a product of 2 primes\n"
                      "rsa <encrypt/decrypt> <text> <e> <n>\n";
        } else if (keyWords[1] == "vigenere") {
            message = "\nvigenere - a sequence of Ceasar ciphers with text key (k1,...,kn)\n"
                      "the text key must be a string of the same length as the plaintext\n"
                      "Ci = Pi + ki (mod 93)\n"
                      "vigenere <encrypt/decrypt> <text> <key>\n";
        } else {
            message = "\ninvalid input\n";
        }
    } else {
        message = "\nThe ascii characters with decimal values 33 to 126 are shifted into the range of 0 to 93\n"
                  "We use an encryption method to map each character from some plain text to a new character\n"
                  "Encryption methods: affine, vigenere, rsa (not implemented)\n"
                  "Do 'help <method>' for more information\n";
    }
    std::cout << message << std::endl;
}

int util::gcd(int a, int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int util::totient(unsigned int n) {
    int result = 1;
    for (unsigned int i = 2; i < n; i++) {
        if (gcd(i, n) == 1) {
            result++;
        }
    }
    return result;
}

int util::modInverse(int a, int n) {
    for (int i = 0; i < n; i++) {
        if ((a * i) % n == 1) {
            return i;
        }
    }
    return -1;
}
