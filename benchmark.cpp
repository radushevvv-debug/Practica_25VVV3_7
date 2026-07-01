#include "benchmark.h"
#include "bst_sort.h"
#include "io.h"
#include <iostream>
#include <vector>

// Вспомогательная функция: запускает сортировку на наборе data и печатает
// строку результатов с названием набора.
static void measureCase(const std::string& caseName, const std::vector<int>& data) {
    SortStats stats;
    std::vector<int> sorted = binaryTreeSort(data, stats);

    std::cout << "  " << caseName << ":\n";
    std::cout << "    время        : " << stats.timeMs << " мс\n";
    std::cout << "    сравнений    : " << stats.comparisons << "\n";
    std::cout << "    вставок      : " << stats.insertions << "\n";
}

void runBenchmark(int size) {
    if (size <= 0) {
        std::cout << "Размер набора должен быть больше нуля.\n";
        return;
    }

    std::cout << "\nАнализ производительности, размер набора = " << size << "\n";

    // Уже отсортированный набор: 0, 1, 2, ..., size-1
    std::vector<int> ascending;
    ascending.reserve(size);
    for (int i = 0; i < size; i++) {
        ascending.push_back(i);
    }

    // Инвертированный набор: size-1, ..., 2, 1, 0
    std::vector<int> descending;
    descending.reserve(size);
    for (int i = size - 1; i >= 0; i--) {
        descending.push_back(i);
    }

    // Случайный набор
    std::vector<int> randomData = generateRandomArray(size, 0, size);

    measureCase("отсортированный", ascending);
    measureCase("инвертированный", descending);
    measureCase("случайный      ", randomData);
    std::cout << "\n";
}
