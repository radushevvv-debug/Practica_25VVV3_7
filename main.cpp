#include "bst_sort.h"
#include "io.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>

#ifdef _WIN32
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
        // Обработка пунктов меню добавляется в следующем коммите
    }

    return 0;
}
