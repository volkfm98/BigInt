#include <iostream>

#include "BigInt.h"

int main() {
    BigInt a;
    BigInt *res = new BigInt;

    long long c = 1e9;

    a = c;
    a = a + a;

    std::cout << a.begin;
}
