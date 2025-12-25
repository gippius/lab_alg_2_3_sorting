#include "app/menu.hpp"
#include "ds/sort.hpp"

#include <iostream>
#include <limits>
#include <random>
#include <vector>

namespace {

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printArray(const std::vector<int>& a) {
    if (a.empty()) {
        std::cout << "Массив пуст.\n";
        return;
    }
    std::cout << "Массив (" << a.size() << "):\n";
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << "[" << i << "] = " << a[i] << "\n";
    }
}

bool readSize(const char* prompt, size_t& out) {
    std::cout << prompt;
    if (!(std::cin >> out)) {
        clearInput();
        return false;
    }
    return true;
}

bool readInt(const char* prompt, int& out) {
    std::cout << prompt;
    if (!(std::cin >> out)) {
        clearInput();
        return false;
    }
    return true;
}

void sortAndReport(std::vector<int>& a, SortStats& stats, bool& has_stats) {
    stats = {};
    if (!a.empty()) {
        quickSortHoare(a, stats);
        has_stats = true;
        std::cout << "Сортировка выполнена (быстрая, Хоара).\n";
        std::cout << "Сравнений: " << stats.comparisons
                  << ", перестановок: " << stats.swaps << "\n";
    } else {
        has_stats = false;
        std::cout << "Массив пуст, сортировка не требуется.\n";
    }
}

void printMenu() {
    std::cout << "\n==== Лабораторная работа 3: Быстрая сортировка (Хоара) ====\n";
    std::cout << "1) Ввести массив вручную\n";
    std::cout << "2) Сгенерировать массив\n";
    std::cout << "3) Показать массив\n";
    std::cout << "4) Отсортировать массив\n";
    std::cout << "5) Найти элемент по индексу\n";
    std::cout << "6) Найти элементы по значению\n";
    std::cout << "7) Добавить элемент (с пересортировкой)\n";
    std::cout << "8) Удалить элемент по индексу (с пересортировкой)\n";
    std::cout << "9) Посчитать количество разных чисел\n";
    std::cout << "10) Показать счетчики последней сортировки\n";
    std::cout << "0) Выход\n";
    std::cout << ">> ";
}

} // namespace

void runMenu() {
    std::vector<int> a;
    SortStats last_stats{};
    bool has_stats = false;

    std::mt19937 rng(std::random_device{}());

    while (true) {
        printMenu();
        int cmd = -1;
        if (!(std::cin >> cmd)) {
            clearInput();
            continue;
        }

        if (cmd == 0) {
            std::cout << "Пока!\n";
            break;
        }
        else if (cmd == 1) {
            size_t n = 0;
            if (!readSize("Введите размер массива: ", n)) {
                continue;
            }
            a.clear();
            a.resize(n);
            for (size_t i = 0; i < n; ++i) {
                int x = 0;
                while (!readInt(("a[" + std::to_string(i) + "] = ").c_str(), x)) {
                }
                a[i] = x;
            }
            has_stats = false;
            std::cout << "Массив введен.\n";
        }
        else if (cmd == 2) {
            size_t n = 0;
            int minv = 0, maxv = 0;
            if (!readSize("Введите размер массива: ", n)) {
                continue;
            }
            if (!readInt("Минимум: ", minv)) {
                continue;
            }
            if (!readInt("Максимум: ", maxv)) {
                continue;
            }
            if (minv > maxv) {
                std::swap(minv, maxv);
            }
            std::uniform_int_distribution<int> dist(minv, maxv);
            a.clear();
            a.reserve(n);
            for (size_t i = 0; i < n; ++i) {
                a.push_back(dist(rng));
            }
            has_stats = false;
            std::cout << "Массив сгенерирован.\n";
        }
        else if (cmd == 3) {
            printArray(a);
        }
        else if (cmd == 4) {
            sortAndReport(a, last_stats, has_stats);
        }
        else if (cmd == 5) {
            if (a.empty()) {
                std::cout << "Массив пуст.\n";
                continue;
            }
            int idx = -1;
            if (!readInt("Введите индекс (с нуля): ", idx)) {
                continue;
            }
            if (idx < 0 || static_cast<size_t>(idx) >= a.size()) {
                std::cout << "Индекс вне диапазона.\n";
                continue;
            }
            std::cout << "a[" << idx << "] = " << a[static_cast<size_t>(idx)] << "\n";
        }
        else if (cmd == 6) {
            if (a.empty()) {
                std::cout << "Массив пуст.\n";
                continue;
            }
            int value = 0;
            if (!readInt("Введите значение: ", value)) {
                continue;
            }
            bool found = false;
            for (size_t i = 0; i < a.size(); ++i) {
                if (a[i] == value) {
                    std::cout << "Найдено на индексе " << i << "\n";
                    found = true;
                }
            }
            if (!found) {
                std::cout << "Элементов с таким значением нет.\n";
            }
        }
        else if (cmd == 7) {
            int value = 0;
            if (!readInt("Введите новое значение: ", value)) {
                continue;
            }
            a.push_back(value);
            sortAndReport(a, last_stats, has_stats);
        }
        else if (cmd == 8) {
            if (a.empty()) {
                std::cout << "Массив пуст.\n";
                continue;
            }
            int idx = -1;
            if (!readInt("Введите индекс для удаления (с нуля): ", idx)) {
                continue;
            }
            if (idx < 0 || static_cast<size_t>(idx) >= a.size()) {
                std::cout << "Индекс вне диапазона.\n";
                continue;
            }
            a.erase(a.begin() + idx);
            if (a.empty()) {
                has_stats = false;
                std::cout << "Массив пуст после удаления.\n";
            } else {
                sortAndReport(a, last_stats, has_stats);
            }
        }
        else if (cmd == 9) {
            if (a.empty()) {
                std::cout << "Массив пуст.\n";
                continue;
            }
            sortAndReport(a, last_stats, has_stats);
            size_t distinct = countDistinctSorted(a);
            std::cout << "Количество разных чисел: " << distinct << "\n";
        }
        else if (cmd == 10) {
            if (!has_stats) {
                std::cout << "Сортировка еще не выполнялась.\n";
                continue;
            }
            std::cout << "Сравнений: " << last_stats.comparisons
                      << ", перестановок: " << last_stats.swaps << "\n";
        }
        else {
            std::cout << "Неизвестная команда.\n";
        }
    }
}
