CXX = g++
CXXFLAGS = -std=c++17
BUILD_DIR = ./build
SRC_DIR = ./src

all: dirs cipher_app

dirs:
	mkdir -p $(BUILD_DIR)

cipher_app: util.o affine_cipher.o vigenere_cipher.o rsa_cipher.o $(SRC_DIR)/main.cpp
	$(CXX) $(BUILD_DIR)/util.o\
		$(BUILD_DIR)/affine_cipher.o\
		$(BUILD_DIR)/vigenere_cipher.o\
		$(BUILD_DIR)/rsa_cipher.o\
		$(SRC_DIR)/main.cpp\
		-o $(BUILD_DIR)/$@

rsa_cipher.o: $(SRC_DIR)/rsa_cipher.cpp
	$(CXX) -c $(SRC_DIR)/rsa_cipher.cpp -o $(BUILD_DIR)/$@

vigenere_cipher.o: $(SRC_DIR)/vigenere_cipher.cpp
	$(CXX) -c $(SRC_DIR)/vigenere_cipher.cpp -o $(BUILD_DIR)/$@

affine_cipher.o: $(SRC_DIR)/affine_cipher.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/affine_cipher.cpp -o $(BUILD_DIR)/$@

util.o: $(SRC_DIR)/util.cpp
	$(CC) $(CXXFLAGS) -c $(SRC_DIR)/util.cpp  -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)
