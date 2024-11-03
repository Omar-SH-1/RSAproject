#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

using namespace boost::multiprecision;

// Проверка, является ли число простым
bool Prost(cpp_int n) {
    if (n <= 1) {
        return false;
    }
    for (cpp_int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Быстрое возведение в степень по модулю
cpp_int PowMod(cpp_int base, cpp_int exp, cpp_int mod) {
    cpp_int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) { // Если exp нечетное
            result = (result * base) % mod;
        }
        exp = exp >> 1; // Делим exp на 2
        base = (base * base) % mod; // Увеличиваем степень
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
    cpp_int e = 65537; // Используем стандартное значение для открытой экспоненты

    // Нахождение d с использованием расширенного алгоритма Евклида
    cpp_int d = 0;
    cpp_int k = 1; // Начинаем с k = 1
    while (true) {
        cpp_int val = k * phi + 1;
        if (val % e == 0) {
            d = val / e; // Находим d
            break;
        }
        ++k;
    }
    return d;
}

// Шифрование сообщения
cpp_int ScryptedMessage(cpp_int m, cpp_int e, cpp_int n) {
    cpp_int SM = PowMod(m, e, n);
    return SM;
}

// Дешифрование сообщения
cpp_int DescryptedMessage(cpp_int SM, cpp_int d, cpp_int n) {
    cpp_int DSM = PowMod(SM, d, n);
    return DSM;
}

int main() {
    cpp_int p =  4398042316799;
    cpp_int q =  274876858367;

    cpp_int d = GenerateKey(p, q);
    std::cout << "Закрытая экспонента d: " << d << std::endl;

    cpp_int e = 65537; // Открытая экспонента
    cpp_int m = 42;
    cpp_int n = p * q;

    cpp_int SM = ScryptedMessage(m, e, n);
    std::cout << "Зашифрованное сообщение: " << SM << std::endl;

    cpp_int DSM = DescryptedMessage(SM, d, n);
    std::cout << "Расшифрованное сообщение: " << DSM << std::endl;

    return 0;
}
