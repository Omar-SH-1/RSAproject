#include "rsa.h"
#include <iostream>

int main() {
    cpp_int p = 2305843009213693951;
    cpp_int q = 18014398241046527;

    cpp_int d = GenerateKey(p, q);
    cpp_int e = 65537;
    cpp_int n = p * q;
    cpp_int s = 0;

    std::string message = "12345678";
    s= message.length();
    std::cout << s <<std::endl;
    std::cout << "Оригинальное сообщение: " << message << std::endl;

    // Шифрование
    std::vector<cpp_int> encryptedMessage = EncryptText(message, e, n, s);
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


