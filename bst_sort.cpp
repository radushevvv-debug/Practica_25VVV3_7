#include "bst_sort.h"
#include <chrono>

// Óçåë äâîè÷íîãî äåðåâà ïîèñêà
struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

// функция берёт одно число и находит для него место в дереве(и строит его).
static void insertValue(Node*& root, int value, long long& comparisons) {
    if (root == nullptr) {
        root = new Node(value);
        return;
    }
    Node* current = root;
    while (true) {
        comparisons++;
        if (value < current->value) {
            // Ìåíüøå óçëà — èä¸ì â ëåâîå ïîääåðåâî
            if (current->left == nullptr) {
                current->left = new Node(value);
                return;
            }
            current = current->left;
        }
        else {
            // Áîëüøå èëè ðàâíî — èä¸ì â ïðàâîå ïîääåðåâî
            if (current->right == nullptr) {
                current->right = new Node(value);
                return;
            }
            current = current->right;
        }
    }
}
// Ñèììåòðè÷íûé (in-order) îáõîä äåðåâà: ëåâîå ïîääåðåâî, êîðåíü, ïðàâîå.
// Çàïîëíÿåò result çíà÷åíèÿìè â ïîðÿäêå âîçðàñòàíèÿ.
// Ðåàëèçàöèÿ èòåðàòèâíàÿ, ÷åðåç ÿâíûé ñòåê — ïî òîé æå ïðè÷èíå, ÷òî è âñòàâêà.
static void inOrderTraversal(Node* root, std::vector<int>& result) {
    std::vector<Node*> stack;
    Node* current = root;
    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push_back(current);
            current = current->left;
        }
        current = stack.back();
        stack.pop_back();
        result.push_back(current->value);
        current = current->right;
    }
}
// Îñâîáîæäåíèå ïàìÿòè, çàíÿòîé äåðåâîì (òîæå áåç ðåêóðñèè).
static void freeTree(Node* root) {
    std::vector<Node*> stack;
    if (root != nullptr) {
        stack.push_back(root);
    }
    while (!stack.empty()) {
        Node* node = stack.back();
        stack.pop_back();
        if (node->left != nullptr) {
            stack.push_back(node->left);
        }
        if (node->right != nullptr) {
            stack.push_back(node->right);
        }
        delete node;
    }
}
std::vector<int> binaryTreeSort(const std::vector<int>& data, SortStats& stats) {
    stats.comparisons = 0;
    stats.insertions = 0;

    auto start = std::chrono::high_resolution_clock::now();

    // Ýòàï 1. Ïîñòðîåíèå äâîè÷íîãî äåðåâà ïîèñêà èç ýëåìåíòîâ ìàññèâà.
    Node* root = nullptr;
    for (int value : data) {
        insertValue(root, value, stats.comparisons);
        stats.insertions++;
    }

    // Ýòàï 2. Îáõîä äåðåâà ñëåâà íàïðàâî äà¸ò îòñîðòèðîâàííûé ìàññèâ.
    std::vector<int> result;
    result.reserve(data.size());
    inOrderTraversal(root, result);
    freeTree(root);

    auto end = std::chrono::high_resolution_clock::now();
    stats.timeMs = std::chrono::duration<double, std::milli>(end - start).count();

    return result;
}
