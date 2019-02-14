#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdint.h>

extern "C" {
    typedef uint8_t u8;
    int omac1_aes_256(const u8 *key, const u8 *data, size_t data_len,
			       u8 *mac);
}
using namespace std;

std::vector<char> HexToBytes(const std::string& hex) {
    std::vector<char> bytes;

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = (char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

int main(int argc, char** argv)
{
    cout << "AES-256 MAC Calculator" << endl;
    cout << "===============================================" << endl;

    std::string encryptionKey, dataBytesStr;
    
    cout << "Key in HEX:" << endl;
    cin >> encryptionKey;
    std::vector<char> encKeyBytes = HexToBytes(encryptionKey);

    if (encKeyBytes.size() != (encryptionKey.length()/2))
    {
        cout << "Invalid key. Exiting..." << endl;
    }

    cout << "Data bytes in HEX:" << endl;
    cin >> dataBytesStr;
    std::vector<char> dataBytes = HexToBytes(dataBytesStr);

    cout << "Result is: " << endl;
    uint8_t mac[16];
    omac1_aes_256((uint8_t*) encKeyBytes.data(), (uint8_t*) dataBytes.data(), dataBytes.size(), mac);
    for (int i = 0; i < sizeof(mac); i++)
    {
        printf("%02X ", mac[i]);
    }
    printf("\n");
}