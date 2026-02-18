#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>
#include <stdint.h>

/**
 * @brief Converts Data* to uintptr_t and back (non-instantiable class).
 */
struct Data {
    int         i;
    std::string str;
};

class Serializer {
private:
    Serializer();
    Serializer(const Serializer &);
    Serializer &operator=(const Serializer &);
    ~Serializer();

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};

#endif