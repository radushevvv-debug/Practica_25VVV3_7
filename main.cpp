#include "bst_sort.h"
#include "io.h"
#include "benchmark.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

// Безопасный ввод целого числа: повторяет запрос, пока не введут число.
static int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: введите целое число.\n";
    }
}

// Ввод имени файла (одно слово без пробелов).
static std::string readFileName(const std::string& prompt) {
    std::cout << prompt;
    std::string name;
    std::cin >> name;
    return name;
}

// Вывод массива на экран. Если он большой, печатаем только начало и конец.
static void printArray(const std::vector<int>& data) {
    if (data.empty()) {
        std::cout << "Массив пуст.\n";
        return;
    }
    const size_t limit = 50;
    std::cout << "Элементов: " << data.size() << "\n";
    if (data.size() <= limit) {
        for (size_t i = 0; i < data.size(); i++) {
            std::cout << data[i];
            if (i + 1 < data.size()) std::cout << ", ";
        }
    } else {
        for (size_t i = 0; i < 25; i++) std::cout << data[i] << ", ";
        std::cout << "... ";
        for (size_t i = data.size() - 25; i < data.size(); i++) {
            std::cout << data[i];
            if (i + 1 < data.size()) std::cout << ", ";
        }
    }
    std::cout << "\n";
}

static void printMenu() {
    std::cout << "\n===== Двоичная сортировка (binary tree sort) — вариант 7 =====\n";
    std::cout << "1. Загрузить массив из файла\n";
    std::cout << "2. Сгенерировать случайный массив\n";
    std::cout << "3. Показать текущий массив\n";
    std::cout << "4. Отсортировать и показать результат\n";
    std::cout << "5. Сохранить отсортированный массив в файл\n";
    std::cout << "6. Анализ производительности\n";
    std::cout << "0. Выход\n";
}

int main() {
#ifdef _WIN32
    // Включаем UTF-8 в консоли Windows, чтобы корректно отображалась кириллица.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::vector<int> current;  // Текущий (исходный) массив
    std::vector<int> sorted;   // Результат сортировки
    bool hasSorted = false;

    while (true) {
        printMenu();
        int choice = readInt("Выберите пункт меню: ");

        if (choice == 0) {
            std::cout << "Выход из программы.\n";
            break;
        }
        else if (choice == 1) {
            std::string fileName = readFileName("Введите имя исходного файла: ");
            std::string error;
            std::vector<int> loaded;
            if (readArrayFromFile(fileName, loaded, error)) {
                current = loaded;
                hasSorted = false;
                std::cout << "Массив загружен. ";
                printArray(current);
            } else {
                std::cout << "Ошибка чтения: " << error << "\n";
            }
        }
        else if (choice == 2) {
            int count = readInt("Сколько элементов сгенерировать: ");
            if (count <= 0) {
                std::cout << "Количество должно быть больше нуля.\n";
                continue;
            }
            int minValue = readInt("Минимальное значение диапазона: ");
            int maxValue = readInt("Максимальное значение диапазона: ");
            current = generateRandomArray(count, minValue, maxValue);
            hasSorted = false;
            std::cout << "Массив сгенерирован. ";
            printArray(current);
        }
        else if (choice == 3) {
            std::cout << "Текущий массив: ";
            printArray(current);
        }
        else if (choice == 4) {
            if (current.empty()) {
                std::cout << "Сначала загрузите или сгенерируйте массив.\n";
                continue;
            }
            SortStats stats;
            sorted = binaryTreeSort(current, stats);
            hasSorted = true;
            std::cout << "Отсортированный массив: ";
            printArray(sorted);
            std::cout << "Время работы : " << stats.timeMs << " мс\n";
            std::cout << "Сравнений    : " << stats.comparisons << "\n";
            std::cout << "Вставок      : " << stats.insertions << "\n";
        }
        else if (choice == 5) {
            if (!hasSorted) {
                std::cout << "Сначала выполните сортировку (пункт 4).\n";
                continue;
            }
            std::string fileName = readFileName("Введите имя результирующего файла: ");
            if (writeArrayToFile(fileName, sorted)) {
                std::cout << "Результат сохранён в файл \"" << fileName << "\".\n";
            } else {
                std::cout << "Не удалось записать файл \"" << fileName << "\".\n";
            }
        }
        else if (choice == 6) {
            int size = readInt("Размер набора для анализа: ");
            runBenchmark(size);
        }
        else {
            std::cout << "Нет такого пункта меню.\n";
        }
    }

    return 0;
}
