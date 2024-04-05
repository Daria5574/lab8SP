#include <iostream>
#include <list>
#include <string>
#include <exception>
#include "cheese.h"

using namespace std;

namespace cheese_shop {
    class CheeseStack {
    private:
        list<Cheese*> stack;

    public:
        void push(const Cheese& cheese) {
            stack.push_back(new Cheese(cheese));
        }

        Cheese pop() {
            if (stack.empty()) {
                throw out_of_range("Стек пуст. Невозможно извлечь элемент.");
            }
            Cheese* topCheese = stack.back();
            stack.pop_back();
            Cheese result = *topCheese;
            delete topCheese;
            return result;
        }

        Cheese getAtPosition(int position) {
            if (position < 0 || static_cast<size_t>(position) >= stack.size()) {
                throw out_of_range("Позиция вне диапазона стека.");
            }
            auto it = next(stack.begin(), position);
            return **it;
        }

        int countBrand(const string& brand) {
            int count = 0;
            for (const auto& cheesePtr : stack) {
                if (cheesePtr->brand == brand) {
                    count++;
                }
            }

            if (count == 0) {
                return -1;
            }
            return count;
        }

        list<Cheese> getByFatPercent(float fatPercent) {
            list<Cheese> result;
            for (const auto& cheesePtr : stack) {
                if (cheesePtr->fatPercent == fatPercent) {
                    result.push_back(*cheesePtr);
                }
            }
            return result;
        }

        ~CheeseStack() {
            for (const auto& cheesePtr : stack) {
                delete cheesePtr;
            }
            stack.clear();
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
        cout << "Извлеченный сыр: \nБренд: " << topCheese.brand << ", \nПроизводитель: " << topCheese.manufacturer << ", \nЖирность: " << topCheese.fatPercent << ", \nЦена: " << topCheese.price << "\n" << endl;

        cheese_shop::Cheese specificCheese = cheeseStack.getAtPosition(0);
        cout << "Сыр на позиции 0: \nБренд: " << specificCheese.brand << ", \nПроизводитель: " << specificCheese.manufacturer << ", \nЖирность: " << specificCheese.fatPercent << ", \nЦена: " << specificCheese.price << "\n" << endl;

        int brandCount = cheeseStack.countBrand("тартар");
        cout << "Количество сыров тартар в стеке: " << brandCount << "\n" << endl;

        list<cheese_shop::Cheese> fatCheeses = cheeseStack.getByFatPercent(30.5);
        for (const auto& cheese : fatCheeses) {
            cout << "Сыр с жирностью 30.5%: \nБренд: " << cheese.brand << ", \nПроизводитель: " << cheese.manufacturer << ", \nЖирность: " << cheese.fatPercent << ", \nЦена: " << cheese.price << "\n" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Исключение: " << e.what() << endl;
    }

    return 0;
}
