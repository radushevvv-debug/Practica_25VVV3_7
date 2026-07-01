#ifndef BST_SORT_H
#define BST_SORT_H

#include <vector>

// Статистика работы алгоритма. Нужна для анализа в отчёте.
struct SortStats {
    long long comparisons; // Число сравнений ключей при построении дерева
    long long insertions;  // Число вставленных в дерево узлов
    double timeMs;         // Время работы алгоритма в миллисекундах
};

// Двоичная сортировка (сортировка с помощью двоичного дерева поиска).
// Принимает исходный массив, возвращает новый отсортированный массив.
// Через параметр stats возвращает статистику работы алгоритма.
std::vector<int> binaryTreeSort(const std::vector<int>& data, SortStats& stats);

#endif