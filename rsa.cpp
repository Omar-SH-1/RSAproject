//
// Created by omar on 03.11.2024.
//

#include "rsa.h"
#include <iostream>

// Проверка, является ли число простым
bool Prost(cpp_int n) {
    if (n <= 1) return false;
    for (cpp_int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Быстрое возведение в степень по модулю
cpp_int PowMod(cpp_int base, cpp_int exp, cpp_int mod) {
    cpp_int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Генерация закрытой экспоненты d
cpp_int GenerateKey(cpp_int p, cpp_int q) {
    if (!Prost(p) || !Prost(q)) {
        std::cout << "error: p и q должны быть простыми числами." << std::endl;
        return cpp_int(0);
    }
    cpp_int phi = (p - 1) * (q - 1);
    cpp_int e = 65537;
    cpp_int d = 0;
    cpp_int k = 1;
    while (true) {
        cpp_int val = k * phi + 1;
        if (val % e == 0) {
            d = val / e;
            break;
        }
        ++k;
    }
    return d;
}

// Преобразование строки в число
cpp_int TextToNumber(const std::string &text) {
    cpp_int num = 0;
    for (char c : text) {
        num = num * 256 + static_cast<unsigned char>(c);
    }
    return num;
}

// Преобразование числа в строку
std::string NumberToText(cpp_int num) {
    std::string text;
    while (num > 0) {
        text.insert(text.begin(), static_cast<char>(num % 256));
        num /= 256;
    }
    return text;
}

// Шифрование блока текста
cpp_int EncryptBlock(cpp_int m, cpp_int e, cpp_int n) {
    return PowMod(m, e, n);
}

// Дешифрование блока текста
cpp_int DecryptBlock(cpp_int c, cpp_int d, cpp_int n) {
    return PowMod(c, d, n);
}

// Шифрование текста
std::vector<cpp_int> EncryptText(const std::string &message, cpp_int e, cpp_int n) {
    std::vector<cpp_int> encryptedBlocks;
    size_t blockSize = 3;
    for (size_t i = 0; i < message.size(); i += blockSize) {
        std::string block = message.substr(i, blockSize);
        cpp_int m = TextToNumber(block);
        encryptedBlocks.push_back(EncryptBlock(m, e, n));
    }
    return encryptedBlocks;
}

// Дешифрование текста
std::string DecryptText(const std::vector<cpp_int> &encryptedBlocks, cpp_int d, cpp_int n) {
    std::string decryptedMessage;
    for (const cpp_int &block : encryptedBlocks) {
        cpp_int decryptedBlock = DecryptBlock(block, d, n);
        decryptedMessage += NumberToText(decryptedBlock);
    }
    return decryptedMessage;
}