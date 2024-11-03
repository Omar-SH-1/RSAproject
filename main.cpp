#include "rsa.h"
#include <iostream>

int main() {
    cpp_int p = 9999999967;
    cpp_int q = 16769023;

    cpp_int d = GenerateKey(p, q);
    cpp_int e = 65537;
    cpp_int n = p * q;

    std::string message = "Hello, RSA!";
    std::cout << "Оригинальное сообщение: " << message << std::endl;

    // Шифрование
    std::vector<cpp_int> encryptedMessage = EncryptText(message, e, n);
    std::cout << "Зашифрованное сообщение: ";
    for (const auto &block : encryptedMessage) {
        std::cout << block << " ";
    }
    std::cout << std::endl;

    // Дешифрование
    std::string decryptedMessage = DecryptText(encryptedMessage, d, n);
    std::cout << "Расшифрованное сообщение: " << decryptedMessage << std::endl;

    return 0;
}
