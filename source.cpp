#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <string>
#include <getopt.h>

int main(int argc, char* argv[]) {
    std::string line;
    if (!std::getline(std::cin, line) || line.empty()) {
        return 1;
    }

    CryptoPP::SHA256 hash;
    std::string digest;

    bool useUppercase = false;

    struct option long_options[] = {
        {"letter_case", required_argument, 0, 'l'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "l:", long_options, &option_index)) != -1) {
        if (opt == 'l') {
            if (std::string(optarg) == "upper") {
                useUppercase = true;
            } else if (std::string(optarg) == "lower") {
                useUppercase = false;
            } else {
                std::cerr << "Invalid argument for --letter_case: " << optarg << std::endl;
                return 1;
            }
        }
    }

    CryptoPP::StringSource s(line, true, 
        new CryptoPP::HashFilter(hash, 
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(digest), useUppercase)));

    std::cout << digest << std::endl;

    return 0;
}