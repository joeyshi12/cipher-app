#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>  

using namespace std;

int charToNum(char c) {
    if (c < 33 || c > 176) {
        cout << "INVALID LETTER: " << c << endl;
        return -1;
    }
    return (int) c - 33;
}

char numToChar(int n) {
    if (n < 0 || n >= 93) {
        cout << "INVALID NUMBER: " << n << endl;
        return (char) ' ';
    }
    return (char) (n + 33);
}

void printHelp(vector<string> keyWords) {
    string message;
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
    cout << message << endl;
}

int gcd(int a, int b) { 
    if (a == 0)
        return b;
    return gcd(b % a, a); 
} 

int totient(unsigned int n) {
    int result = 1;
    for (int i = 2; i < n; i++) {
        if (gcd(i, n) == 1) {
            result++;
        }
    }
    return result;
}


int modInverse(int a, int n) {
    for (int i = 0; i < n; i++) {
        if ((a * i) % n == 1) {
            return i;
        }
    }
    return -1;
}

string affineTransform(string text, int a, int b) {
    for (int i = 0; i < text.size(); i++) {
        int n = (a * charToNum(text[i]) + b) % 93;
        text[i] = numToChar(n);
    }
    return text;
}

void handleAffine(vector<string> keyWords) {
    if (keyWords.size() != 5) {
        cout << "\ninvalid number of arguments\n" << endl;
        return;
    }
    int a; int b;
    try {
        a = stoi(keyWords[3]);
        b = stoi(keyWords[4]);
    } catch (const exception& e) {
        cout << "\ninvalid key\n" << endl;
        return;
    }    
    if (keyWords[1] == "encrypt") {
        if (gcd(a, 93) != 1) {
            cout << "WARNING: a is not coprime to 93" << endl;
        }
        string cipherText = affineTransform(keyWords[2], a, b);
        cout << "\n" << cipherText << "\n" << endl;
    } else if (keyWords[1] == "decrypt") {
        int a_inv = modInverse(stoi(keyWords[3]), 93);
        if (a_inv == -1) {
            cout << "\n'a' is not coprime to 93\n" << endl;
            return;
        }
        int b = stoi(keyWords[4]);
        string plainText = affineTransform(keyWords[2], a_inv, (-a_inv * b) % 93);
        cout << "\n" << plainText << "\n" << endl;
    } else {
        cout << "\ninvalid task\n" << endl;
    }
}

void handleRSA(vector<string> keyWords) {
    cout << "\nRSA not implemented yet\n" << endl;
}

void handleVigenere(vector<string> keyWords) {
    if (keyWords.size() != 4) {
        cout << "\ninvalid number of arguments\n" << endl;
        return;
    }
    if (keyWords[2].size() != keyWords[3].size()) {
        cout << "\ninvalid key length\n" << endl;
        return;
    }
    if (keyWords[1] == "encrypt") {
        string output = "";
        string key = keyWords[3];
        for (int i = 0; i < keyWords[2].size(); i++) {
            output = output + numToChar((charToNum(keyWords[2][i]) + charToNum(key[i])) % 93);
        }
        cout << "\n" << output << "\n" << endl;
    } else if (keyWords[1] == "decrypt") {
        string output = "";
        string key = keyWords[3];
        for (int i = 0; i < keyWords[2].size(); i++) {
            int num = (charToNum(keyWords[2][i]) - charToNum(key[i])) % 93;
            if (num < 0) {
                num += 93;
            }
            output = output + numToChar(num);
        }
        cout << "\n" << output << "\n" << endl;
    } else {
        cout << "\ninvalid task\n" << endl;
    }
}

vector<string> splitString(string input) {
    if (input.size() == 0) {
        return {};
    }
    istringstream iss(input);
    vector<string> results{istream_iterator<string>{iss}, istream_iterator<string>{}};
    return results;
}

int main(int argc, char const *argv[]) {
    while (true) {
        string input;
        cout << "cipher-app>> ";
        getline(cin, input);
        vector<string> keyWords = splitString(input);
        if (!keyWords.empty()) {
            if (keyWords[0] == "help") {
                printHelp(keyWords);
            } else if (keyWords[0] == "affine") {
                handleAffine(keyWords);
            } else if (keyWords[0] == "rsa") {
                handleRSA(keyWords);
            } else if (keyWords[0] == "vigenere") {
                handleVigenere(keyWords);
            } else  if (keyWords[0] == "exit") {
                return 0;
            }
        }
    }
    return 0;
}
