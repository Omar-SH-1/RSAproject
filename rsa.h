#ifndef RSA_H
#define RSA_H

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <string>

using namespace boost::multiprecision;

bool Prost(cpp_int n);
cpp_int PowMod(cpp_int base, cpp_int exp, cpp_int mod);
cpp_int GenerateKey(cpp_int p, cpp_int q);
cpp_int TextToNumber(const std::string &text);
std::string NumberToText(cpp_int num);
cpp_int EncryptBlock(cpp_int m, cpp_int e, cpp_int n);
cpp_int DecryptBlock(cpp_int c, cpp_int d, cpp_int n);
std::vector<cpp_int> EncryptText(const std::string &message, cpp_int e, cpp_int n,cpp_int s);
std::string DecryptText(const std::vector<cpp_int> &encryptedBlocks, cpp_int d, cpp_int n);

#endif // RSA_H
