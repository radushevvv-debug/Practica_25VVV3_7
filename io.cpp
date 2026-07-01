#include "io.h"
#include <fstream>
#include <sstream>
#include <random>
#include <cctype>

// Проверяет, является ли строка корректным целым числом (необязательный
// знак + одна или более цифр).
static bool isInteger(const std::string& token) {
    if (token.empty()) {
        return false;
    }
    size_t start = 0;
    if (token[0] == '+' || token[0] == '-') {
        start = 1;
    }
    if (start == token.size()) {
        return false; // только знак без цифр
    }
    for (size_t i = start; i < token.size(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(token[i]))) {
            return false;
        }
    }
    return true;
}

bool readArrayFromFile(const std::string& filename, std::vector<int>& out, std::string& error) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        error = "не удалось открыть файл \"" + filename + "\"";
        return false;
    }

    out.clear();
    std::string raw;
    // Считываем весь файл и заменяем запятые и точки с запятой на пробелы,
    // чтобы дальше разбить ввод на отдельные числа.
    std::stringstream buffer;
    buffer << file.rdbuf();
    raw = buffer.str();
    for (char& c : raw) {
        if (c == ',' || c == ';') {
            c = ' ';
        }
    }

    std::stringstream stream(raw);
    std::string token;
    while (stream >> token) {
        if (!isInteger(token)) {
            error = "файл содержит некорректное значение: \"" + token + "\"";
            out.clear();
            return false;
        }
        out.push_back(std::stoi(token));
    }

    if (out.empty()) {
        error = "файл пуст или не содержит чисел";
        return false;
    }
    return true;
}
bool writeArrayToFile(const std::string& filename, const std::vector<int>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    for (size_t i = 0; i < data.size(); i++) {
        file << data[i];
        if (i + 1 < data.size()) {
            file << ", ";
        }
    }
    file << "\n";
    return true;
}
