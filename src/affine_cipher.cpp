#include "../include/affine_cipher.h"
#include "../include/util.h"

string affineCipher::encrypt(string plainText, pair<int, int> key)
{
    int a = key.first;
    int b = key.second;
    for (int i = 0; i < plainText.size(); i++) {
        int n = (a * util::charToNum(plainText[i]) + b) % 93;
        plainText[i] = util::numToChar(n);
    }
    return plainText;
}

string affineCipher::decrypt(string cipherText, pair<int, int> key)
{
    int a_prime = util::modInverse(key.first, 93);
    int b_prime = (-a_prime * key.second) % 93;
    if (b_prime < 0)
    {
        b_prime += 93;
    }
    return encrypt(cipherText, make_pair(a_prime, b_prime));
}

void affineCipher::handle(vector<string> keyWords) {
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
    pair<int, int> key = make_pair(a, b);
    if (keyWords[1] == "encrypt") {
        if (util::gcd(a, 93) != 1) {
            cout << "WARNING: a is not coprime to 93" << endl;
        }
        cout << "\n" << encrypt(keyWords[2], key) << "\n" << endl;
    } else if (keyWords[1] == "decrypt") {
        if (util::gcd(a, 93) != 1) {
            cout << "\nmod inverse does not exist\n" << endl;
            return;
        }
        cout << decrypt(keyWords[2], key) << endl;
    } else {
        cout << "\ninvalid task\n" << endl;
    }
}
