#include "bst_sort.h"
#include <chrono>

// Узел двоичного дерева поиска
struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

// Вставка значения в дерево поиска.
// Реализация итеративная (без рекурсии), чтобы не переполнять стек
// на худшем случае, когда входной массив уже отсортирован и дерево
// вырождается в длинную цепочку.
static void insertValue(Node*& root, int value, long long& comparisons) {
    if (root == nullptr) {
        root = new Node(value);
        return;
    }
    Node* current = root;
    while (true) {
        comparisons++;
        if (value < current->value) {
            // Меньше узла — идём в левое поддерево
            if (current->left == nullptr) {
                current->left = new Node(value);
                return;
            }
            current = current->left;
        }
        else {
            // Больше или равно — идём в правое поддерево
            if (current->right == nullptr) {
                current->right = new Node(value);
                return;
            }
            current = current->right;
        }
    }
}