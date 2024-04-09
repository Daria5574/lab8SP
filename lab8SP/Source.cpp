#include <iostream>
#include <string>
#include <list>
#include <stdexcept>
#include "cheese.h"

using namespace std;

namespace cheese_shop {
    struct Node {
        Cheese data;
        Node* left;
        Node* right;

        Node(const Cheese& cheese) : data(cheese), left(nullptr), right(nullptr) {}
    };

    class CheeseBinarySearchTree {
    private:
        Node* root;

    public:
        CheeseBinarySearchTree() : root(nullptr) {}

        Node* insertRecursive(Node* currentNode, const Cheese& cheese) {
            if (currentNode == nullptr) {
                return new Node(cheese);
            }

            if (cheese.brand < currentNode->data.brand) {
                currentNode->left = insertRecursive(currentNode->left, cheese);
            }
            else {
                currentNode->right = insertRecursive(currentNode->right, cheese);
            }

            return currentNode;
        }

        void insert(const Cheese& cheese) {
            root = insertRecursive(root, cheese);
        }
        Cheese extractCheese() {
            if (root == nullptr) {
                throw runtime_error("������ ����� ������.");
            }
            Node* extractedNode = findMin(root);
            Cheese extractedCheese = extractedNode->data;
            root = deleteRecursive(root, extractedCheese.brand);
            return extractedCheese;
        }

        Node* findMin(Node* currentNode) {
            while (currentNode->left != nullptr) {
                currentNode = currentNode->left;
            }
            return currentNode;
        }

        Node* deleteRecursive(Node* currentNode, const string& brand) {
            if (currentNode == nullptr) return currentNode;

            if (brand < currentNode->data.brand) {
                currentNode->left = deleteRecursive(currentNode->left, brand);
            }
            else if (brand > currentNode->data.brand) {
                currentNode->right = deleteRecursive(currentNode->right, brand);
            }
            else {
                if (currentNode->left == nullptr) {
                    Node* temp = currentNode->right;
                    delete currentNode;
                    return temp;
                }
                else if (currentNode->right == nullptr) {
                    Node* temp = currentNode->left;
                    delete currentNode;
                    return temp;
                }
                Node* minRight = findMin(currentNode->right);
                currentNode->data = minRight->data;
                currentNode->right = deleteRecursive(currentNode->right, minRight->data.brand);
            }

            return currentNode;
        }

        void remove(const string& brand) {
            root = deleteRecursive(root, brand);
        }

        Node* search(Node* currentNode, const string& brand) {
            if (currentNode == nullptr || currentNode->data.brand == brand) {
                return currentNode;
            }

            if (brand < currentNode->data.brand) {
                return search(currentNode->left, brand);
            }
            else {
                return search(currentNode->right, brand);
            }
        }

        Cheese searchCheese(const string& brand) {
            Node* resultNode = search(root, brand);
            if (resultNode == nullptr) {
                throw runtime_error("��� � ����� ������� �� ������ � ������.");
            }

            return resultNode->data;
        }

        int countBrand(const string& brand) {
            int count = 0;
            countBrandHelper(root, brand, count);
            return count;
        }

        void countBrandHelper(Node* currentNode, const string& brand, int& count) {
            if (currentNode == nullptr) {
                return;
            }

            countBrandHelper(currentNode->left, brand, count);
            if (currentNode->data.brand == brand) {
                count++;
            }
            countBrandHelper(currentNode->right, brand, count);
        }

        list<Cheese> getByFatPercent(float fatPercent) {
            list<Cheese> result;
            getByFatPercentHelper(root, fatPercent, result);
            return result;
        }

        Cheese getAtPosition(int position) {
            list<Cheese> cheeseList = inorderTraversal();
            if (position < 0 || position >= cheeseList.size()) {
                throw out_of_range("������� ������� �� ������� ������ �����.");
            }
            auto it = cheeseList.begin();
            advance(it, position);
            return *it;
        }
        list<Cheese> inorderTraversal() {
            list<Cheese> result;
            inorderTraversalHelper(root, result);
            return result;
        }
        void inorderTraversalHelper(Node* currentNode, list<Cheese>& result) {
            if (currentNode == nullptr) {
                return;
            }
            inorderTraversalHelper(currentNode->left, result);
            result.push_back(currentNode->data);
            inorderTraversalHelper(currentNode->right, result);
        }

        void getByFatPercentHelper(Node* currentNode, float fatPercent, list<Cheese>& result) {
            if (currentNode == nullptr) {
                return;
            }

            getByFatPercentHelper(currentNode->left, fatPercent, result);
            if (currentNode->data.fatPercent == fatPercent) {
                result.push_back(currentNode->data);
            }
            getByFatPercentHelper(currentNode->right, fatPercent, result);
        }

        ~CheeseBinarySearchTree() {
            deleteEntireTree(root);
        }

        void deleteEntireTree(Node* currentNode) {
            if (currentNode == nullptr) {
                return;
            }

            deleteEntireTree(currentNode->left);
            deleteEntireTree(currentNode->right);
            delete currentNode;
        }
    };
}

int main() {
    setlocale(LC_ALL, "Russian");

    cheese_shop::CheeseBinarySearchTree cheeseTree;

    cheese_shop::Cheese tartar{ "������", "���������", 30.5, 1000 };
    cheese_shop::Cheese mozzarella{ "���������", "��������������", 20.0, 500 };

    cheeseTree.insert(tartar);
    cheeseTree.insert(mozzarella);

    try {

        list<cheese_shop::Cheese> fatCheeses = cheeseTree.getByFatPercent(30.5);
        cout << "���� � ��������� 30.5%: " << endl;
        for (const auto& cheese : fatCheeses) {
            cout << "�����: " << cheese.brand << ", �������������: " << cheese.manufacturer << ", ��������: " << cheese.fatPercent << ", ����: " << cheese.price << endl;
        }

        cout << "\n���������� ������� �������� �� ������:" << endl;
        cheese_shop::Cheese extractedCheese = cheeseTree.extractCheese();
        cout << "����������� ���: " << extractedCheese.brand << ", �������������: " << extractedCheese.manufacturer << ", ��������: " << extractedCheese.fatPercent << ", ����: " << extractedCheese.price << endl;

        cout << "\n��������� �������� �� ������� 0:" << endl;
        cheese_shop::Cheese positionCheese = cheeseTree.getAtPosition(0);
        cout << "������� 0: " << positionCheese.brand << ", �������������: " << positionCheese.manufacturer << ", ��������: " << positionCheese.fatPercent << ", ����: " << positionCheese.price << endl;
 
        cout << "\n" << "�������� ����� ���� '������' �� ������" << endl;
        cheeseTree.remove("������");

        cout << "����� ���������� ����� ���� '������' ����� ��������" << endl;
        cheeseTree.searchCheese("������");

        int brandCount = cheeseTree.countBrand("��������"); // �������� �� ����� ����, ������� ��� � ������
        if (brandCount == 0) {
            cout << "���������� ����� '��������' � ������: " << -1 << endl;
        }
        else {
            cout << "���������� ����� '��������' � ������: " << brandCount << endl;
        }


    }
    catch (const exception& e) {
        cerr << "����������: " << e.what() << endl;
    }

    return 0;
}