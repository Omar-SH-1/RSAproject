#include <iostream>
#include <vector>
#include <gmpxx.h>

mpz_class gcd(const mpz_class& a, const mpz_class& b) {
    mpz_class temp;
    mpz_class a_copy = a, b_copy = b;
    while (b_copy != 0) {
        temp = b_copy;
        b_copy = a_copy % b_copy;
        a_copy = temp;
    }
    return a_copy;
}

// Вычисление значения d через формулу
mpz_class calculateD(const mpz_class& e, const mpz_class& phi) {
    mpz_class k = 1;
    mpz_class candidate;
    while (true) {
        candidate = 1 + k * phi;
        if (candidate % e == 0) {
            return candidate / e;
        }
        k++;
    }
}

mpz_class modPow(const mpz_class& base, const mpz_class& exp, const mpz_class& mod) {
    mpz_class result = 1;
    mpz_class base_mod = base % mod;
    mpz_class exp_copy = exp;

    while (exp_copy > 0) {
        if (exp_copy % 2 == 1) {
            result = (result * base_mod) % mod;
        }
        exp_copy = exp_copy >> 1; // exp = exp / 2
        base_mod = (base_mod * base_mod) % mod;
    }
    return result;
}

// Функция для генерации ключей RSA
void generateRSAKeys(mpz_class& e, mpz_class& d, mpz_class& n) {
    mpz_class p = 61; // Первое простое число
    mpz_class q = 53; // Второе простое число

    n = p * q;
    mpz_class phi = (p - 1) * (q - 1);

    e = 2;
    while (gcd(e, phi) != 1) {
        e++;
    }

    d = calculateD(e, phi);
}

// Функция для шифрования сообщения
std::vector<mpz_class> encrypt(const std::string& message, const mpz_class& e, const mpz_class& n) {
    std::vector<mpz_class> encryptedMessage;
    for (char c : message) {
        encryptedMessage.push_back(modPow(c, e, n));
    }
    return encryptedMessage;
}

// Функция для расшифровки сообщения
std::string decrypt(const std::vector<mpz_class>& encryptedMessage, const mpz_class& d, const mpz_class& n) {
    std::string decryptedMessage;
    for (const auto& c : encryptedMessage) {
        // Преобразуем расшифрованное значение в символ
        decryptedMessage.push_back(static_cast<char>(modPow(c, d, n).get_si()));
    }
    return decryptedMessage;
}

int main() {
    mpz_class e, d, n;

    // Генерируем ключи
    generateRSAKeys(e, d, n);

    std::cout << "Открытый ключ: (" << e << ", " << n << ")\n";
    std::cout << "Закрытый ключ: (" << d << ", " << n << ")\n";

    std::string message;
    std::cout << "Введите сообщение для шифрования: ";
    std::getline(std::cin, message);

    std::vector<mpz_class> encryptedMessage = encrypt(message, e, n);
    std::cout << "Зашифрованное сообщение: ";
    for (const auto& c : encryptedMessage) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    std::string decryptedMessage = decrypt(encryptedMessage, d, n);
    std::cout << "Расшифрованное сообщение: " << decryptedMessage << std::endl;

    return 0;
}
