#ifndef CHEESE_H
#define CHEESE_H

#include <string>

namespace cheese_shop
{
    struct Cheese
    {
        std::string brand;
        std::string manufacturer;
        float fatPercent;
        float price;
    };
}

#endif // CHEESE_H