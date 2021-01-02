#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>  

using namespace std;

int charToNum(char c) 
{
    if (c < 33 || c > 176) {
        cout << "INVALID LETTER" << endl;
        return -1;
    }
    return c - 33;
}

char numToChar(int n) 
{
    if (n < 0 || n >= 93) {
        return (char) ' ';
    }
    return (char) (n + 33);
}

void printHelp(vector<string> keyWords) 
{
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
        } else {
            message = "\ninvalid input\n";
        }
    } else {
        message = "\nThe ascii characters with decimal values 33 to 126 are shifted into the range of 0 to 93\n"
                  "We use an encryption method to map each character from some plain text to a new character\n"
                  "Encryption methods: affine, rsa\n"
                  "Do 'help <method>' for more information\n";
    }
    cout << message << endl;
}

int gcd(int a, int b) 
{ 
    if (a == 0)
        return b;
    return gcd(b % a, a); 
} 

int totient(unsigned int n) 
{
    int result = 1;
    for (int i = 2; i < n; i++) {
        if (gcd(i, n) == 1) {
            result++;
        }
    }
    return result;
}


int getInverse(int a, int n) 
{
    if (gcd(a, n) != 1) {
        return -1;
    } else {
        for (int i = 0; i < n; i++) {
            if ((a * i) % n == 1) {
                return i;
            }
        }
        return -1;
    }
}

string affineTransform(string text, int a, int b) 
{
    for (int i = 0; i < text.size(); i++) {
        int n = (a * charToNum(text[i]) + b) % 93;
        text[i] = numToChar(n);
    }
    return text;
}

void handleAffine(vector<string> keyWords) 
{
    if (keyWords.size() != 5) {
        cout << "invalid input\n" << endl;
    } else if (keyWords[1] == "encrypt") {
        int a = stoi(keyWords[3]);
        int b = stoi(keyWords[4]);
        if (gcd(a, 93) != 1) {
            cout << "WARNING: a is not coprime to 93" << endl;
        }
        string cipherText = affineTransform(keyWords[2], a, b);
        cout << "\n" << keyWords[2] << " -> " << cipherText << "\n" << endl;
    } else if (keyWords[1] == "decrypt") {
        int a_inv = getInverse(stoi(keyWords[3]), 93);
        if (a_inv == -1) {
            cout << "invalid 'a' value" << endl;
            return;
        }
        int b = stoi(keyWords[4]);
        string plainText = affineTransform(keyWords[2], a_inv, (-a_inv * b) % 93);
        cout << "\n" << keyWords[2] << " -> " << plainText << "\n" << endl;
    } else {
        cout << "invalid input" << endl;
    }
}

void handleRSA(vector<string> keyWords) 
{
    cout << "RSA not implemented yet" << endl;
}

vector<string> splitString(string input) 
{
    if (input.size() == 0) {
        return {};
    }
    istringstream iss(input);
    vector<string> results{istream_iterator<string>{iss}, istream_iterator<string>{}};
    return results;
}

int main(int argc, char const *argv[])
{
    while (true) {
        string input;
        cout << "cipher-app: ";
        getline(cin, input);
        vector<string> keyWords = splitString(input);
        if (!keyWords.empty()) {
            if (keyWords[0] == "help") {
                printHelp(keyWords);
            } else if (keyWords[0] == "affine") {
                handleAffine(keyWords);
            } else if (keyWords[0] == "rsa") {
                handleRSA(keyWords);
            } else  if (keyWords[0] == "exit") {
                return 0;
            }
        }
    }
    return 0;
}
