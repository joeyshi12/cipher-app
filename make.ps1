g++ -c src/util.cpp -o build/util.o
g++ -c src/affine_cipher.cpp -o build/affine_cipher.o
g++ -c src/vigenere_cipher.cpp -o build/vigenere_cipher.o
g++ -c src/rsa_cipher.cpp -o build/rsa_cipher.o
g++ build/util.o build/affine_cipher.o build/vigenere_cipher.o build/rsa_cipher.o src/main.cpp -o cipher_app