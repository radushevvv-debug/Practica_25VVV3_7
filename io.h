#ifndef IO_H
#define IO_H

#include <vector>
#include <string>

// Читает массив целых чисел из файла в формате CSV (числа через запятую).
// Допускаются пробелы и переносы строк между числами.
// При успехе возвращает true и заполняет out.
// При ошибке возвращает false и записывает текст ошибки в error.
bool readArrayFromFile(const std::string& filename, std::vector<int>& out, std::string& error);

// Записывает массив в файл в формате CSV (числа через запятую).
// Возвращает true при успехе, false если файл не удалось открыть.
bool writeArrayToFile(const std::string& filename, const std::vector<int>& data);

// Генерирует массив из count случайных чисел в диапазоне [minValue, maxValue].
std::vector<int> generateRandomArray(int count, int minValue, int maxValue);

#endif
