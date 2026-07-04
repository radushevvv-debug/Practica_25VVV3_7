#include "bst_sort.h"
#include <chrono>

struct Node { //создание узла дерева
    int value; //рассматриваемое число в массиве
    Node* left; //создание левого и правого дочерних узлов
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {} //сборка узла
};

// функция берёт одно число и находит для него место в дереве(и строит его).
static void insertValue(Node*& root, int value, long long& comparisons) { //root - корень дерева
    if (root == nullptr) {  // создаем дерево если его ещё нет
        root = new Node(value);
        return;
    }
    Node* current = root; // указатель на корень дерева
    while (true) { // цикл для поиска в дереве пустого места для числа
        comparisons++;
        if (value < current->value) { //сравнение
            if (current->left == nullptr) { //если value < current идём на лево, условие left == nullptr
                current->left = new Node(value); //если left == nullptr то ставим наше число
                return;
            }
            current = current->left; // если left не == nullptr, то переходим к левому числу, и повторяем цикл сравнения
        }
        else { //иначе идём направо
            if (current->right == nullptr) { //проверяем условие right == nullptr
                current->right = new Node(value); //если да - ставим наше число
                return;
            }
            current = current->right; //если нет - повторяем цикл
        }
    }
}
//наполнение сортировки
static void inOrderTraversal(Node* root, std::vector<int>& result) { /*result - пустой список, в который будут
    складываться сортированные числа */
    std::vector<Node*> stack; //создание стека для узлов, к которым возможно надо будет возвращаться
    Node* current = root; //начинаем с корня дерева
    while (current != nullptr || !stack.empty()) { //проверяет либо число на равенство нулю, либо стек на наличие узлов
        while (current != nullptr) { //повторяем цикл пока current != nullptr
            stack.push_back(current); //кладем текущий узел в стек
            current = current->left; //идем влево
        }
        current = stack.back(); //переходим к последнему сохраненному узлу
        stack.pop_back(); //убираем его из стека
        result.push_back(current->value); //записываем число из этого узла в список (result) 
        current = current->right; //теперь идем не влево а направо от данного узла
    }
}
//очистка памяти(предотвращение утечки памяти)
static void freeTree(Node* root) { //функция принимает корень дерева
    std::vector<Node*> stack; //создаем стек
    if (root != nullptr) { //проверка на существование корня
        stack.push_back(root); //если существует кладём в стек
    }
    while (!stack.empty()) { //пока в стеке есть хоть один узел повторяем цикл
        Node* node = stack.back(); //достаем из стека последний узел
        stack.pop_back(); //удаляем его из стека
        if (node->left != nullptr) { //проверяем на наличие дочернего узла
            stack.push_back(node->left); //если он есть - кладём в стен
        }
        if (node->right != nullptr) { //тоже самое для правого
            stack.push_back(node->right);
        }
        delete node; //удаляет узел и освобождает память
    }
}
//главная функция сортировки - превращает несортированный массив в отсортированный и замеряет сколько времени это заняло
std::vector<int> binaryTreeSort(const std::vector<int>& data, SortStats& stats) { /*принимает исходный массив и 
    структуру для статистики */
    stats.comparisons = 0; //обнуление счетчиков
    stats.insertions = 0;

    auto start = std::chrono::high_resolution_clock::now(); //начало работы секундомера (запоминает точное время)
//построение дерева
    Node* root = nullptr; //указатель на корень дерева (пустой)
    for (int value : data) { //берем каждое число из массива по очереди
        insertValue(root, value, stats.comparisons); //вызываем функцию insertValue
        stats.insertions++; //увеличиваем счетчик узлов в дереве
    }

    std::vector<int> result; //создание result
    result.reserve(data.size()); //резервируем память под result (столько же сколько было в исходном массиве)
    inOrderTraversal(root, result); //вызов inOrderTraversal
    freeTree(root); //вызов freeTree

    auto end = std::chrono::high_resolution_clock::now(); //остановка секундомера и фиксация времени
    stats.timeMs = std::chrono::duration<double, std::milli>(end - start).count(); /*считаем разницу между временем 
    конца и временем начала, переводим в милисекунды и записываем в stats.timeMs */

    return result; //возвращаем готовый массив
}
