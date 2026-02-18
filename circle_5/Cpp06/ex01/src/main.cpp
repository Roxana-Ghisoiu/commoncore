#include "../inc/Serializer.hpp"
#include <iostream>

int main() {
    Data d;
    d.i = 42;
    d.str = "Hello";

    std::cout << "Original pointer: " << &d << std::endl;

    uintptr_t raw = Serializer::serialize(&d);
    std::cout << "Serialized value: " << raw << std::endl;

    Data* restored = Serializer::deserialize(raw);
    std::cout << "Restored pointer: " << restored << std::endl;

    if (restored == &d)
        std::cout << "OK: Same address" << std::endl;
    else
        std::cout << "ERROR: Different address" << std::endl;

    return 0;
}