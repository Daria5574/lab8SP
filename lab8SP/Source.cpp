#include <iostream>
#include <vector>
#include <string>
#include <exception>

#include "cheese.h"

namespace cheese_shop {
    class CheeseStack {
    private:
        std::vector<Cheese> stack;

    public:
        void push(const Cheese& cheese) {
            stack.push_back(cheese);
        }

        Cheese pop() {
            if (stack.empty()) {
                throw std::out_of_range("стек пуст. Невозможно извлечь элемент.");
            }

            Cheese topCheese = stack.back();
            stack.pop_back();

            return topCheese;
        }

        Cheese getAtPosition(int position) {
            if (position >= stack.size() || position < 0) {
                throw std::out_of_range("позиция выходит за границы стека.");
            }

            return stack[position];
        }

        int countBrand(const std::string& brand) {
            int count = 0;

            for (const auto& cheese : stack) {
                if (cheese.brand == brand) {
                    count++;
                }
            }

            if (count == 0) {
                return -1;
            }

            return count;
        }

        std::vector<Cheese> getByFatPercent(float fatPercent) {
            std::vector<Cheese> result;

            for (const auto& cheese : stack) {
                if (cheese.fatPercent == fatPercent) {
                    result.push_back(cheese);
                }
            }

            return result;
        }
    };
}

int main() {
    setlocale(LC_ALL, "Russian");
    cheese_shop::CheeseStack cheeseStack;

    try {
        cheese_shop::Cheese tartar{ "тартар", "татарстан", 30.5, 1000 };
        cheese_shop::Cheese mozzarella{ "моцарелла", "великобритания", 20.0, 500 };

        cheeseStack.push(tartar);
        cheeseStack.push(mozzarella);

        cheese_shop::Cheese topCheese = cheeseStack.pop();
        std::cout << "извлеченный сыр: \nбренд: " << topCheese.brand << ", \nпроизводитель: " << topCheese.manufacturer << ", \nжирность: " << topCheese.fatPercent << ", \nцена: " << topCheese.price << "\n" << std::endl;

        cheese_shop::Cheese specificCheese = cheeseStack.getAtPosition(0);
        std::cout << "сыр на позиции 0: \nбренд: " << specificCheese.brand << ", \nпроизводитель: " << specificCheese.manufacturer << ", \nжирность: " << specificCheese.fatPercent << ", \nцена: " << specificCheese.price << "\n" << std::endl;

        int brandCount = cheeseStack.countBrand("тартар");
        std::cout << "количество сыров тартар в стеке: " << brandCount << "\n" << std::endl;

        std::vector<cheese_shop::Cheese> fatCheeses = cheeseStack.getByFatPercent(30.5);
        for (const auto& cheese : fatCheeses) {
            std::cout << "сыр с жирностью 30.5%: \nбренд: " << cheese.brand << ", \nпроизводитель: " << cheese.manufacturer << ", \nжирность: " << cheese.fatPercent << ", \nцена: " << cheese.price  << "\n" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "исключение: " << e.what() << std::endl;
    }

    return 0;
}
