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
                throw std::out_of_range("���� ����. ���������� ������� �������.");
            }

            Cheese topCheese = stack.back();
            stack.pop_back();

            return topCheese;
        }

        Cheese getAtPosition(int position) {
            if (position >= stack.size() || position < 0) {
                throw std::out_of_range("������� ������� �� ������� �����.");
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
        cheese_shop::Cheese tartar{ "������", "���������", 30.5, 1000 };
        cheese_shop::Cheese mozzarella{ "���������", "��������������", 20.0, 500 };

        cheeseStack.push(tartar);
        cheeseStack.push(mozzarella);

        cheese_shop::Cheese topCheese = cheeseStack.pop();
        std::cout << "����������� ���: \n�����: " << topCheese.brand << ", \n�������������: " << topCheese.manufacturer << ", \n��������: " << topCheese.fatPercent << ", \n����: " << topCheese.price << "\n" << std::endl;

        cheese_shop::Cheese specificCheese = cheeseStack.getAtPosition(0);
        std::cout << "��� �� ������� 0: \n�����: " << specificCheese.brand << ", \n�������������: " << specificCheese.manufacturer << ", \n��������: " << specificCheese.fatPercent << ", \n����: " << specificCheese.price << "\n" << std::endl;

        int brandCount = cheeseStack.countBrand("������");
        std::cout << "���������� ����� ������ � �����: " << brandCount << "\n" << std::endl;

        std::vector<cheese_shop::Cheese> fatCheeses = cheeseStack.getByFatPercent(30.5);
        for (const auto& cheese : fatCheeses) {
            std::cout << "��� � ��������� 30.5%: \n�����: " << cheese.brand << ", \n�������������: " << cheese.manufacturer << ", \n��������: " << cheese.fatPercent << ", \n����: " << cheese.price  << "\n" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "����������: " << e.what() << std::endl;
    }

    return 0;
}
