#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <string>

int main() {
    std::string line;
    if (!std::getline(std::cin, line) || line.empty()) {
        return 1;
    }

    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::StringSource s(line, true, 
        new CryptoPP::HashFilter(hash, 
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(digest))));

    std::cout << digest << std::endl;

    return 0;
}