#include "ds/sort.hpp"

#include <algorithm>

namespace {

bool lessThan(int value, int pivot, SortStats& stats) {
    stats.comparisons++;
    return value < pivot;
}

bool greaterThan(int value, int pivot, SortStats& stats) {
    stats.comparisons++;
    return value > pivot;
}

void quickSortImpl(std::vector<int>& a, int left, int right, SortStats& stats) {
    int i = left;
    int j = right;
    int pivot = a[(left + right) / 2];

    while (i <= j) {
        while (lessThan(a[i], pivot, stats)) {
            ++i;
        }
        while (greaterThan(a[j], pivot, stats)) {
            --j;
        }
        if (i <= j) {
            if (i < j) {
                std::swap(a[i], a[j]);
                stats.swaps++;
            }
            ++i;
            --j;
        }
    }

    if (left < j) {
        quickSortImpl(a, left, j, stats);
    }
    if (i < right) {
        quickSortImpl(a, i, right, stats);
    }
}

} // namespace

void quickSortHoare(std::vector<int>& a, SortStats& stats) {
    if (a.size() < 2) {
        return;
    }
    quickSortImpl(a, 0, static_cast<int>(a.size() - 1), stats);
}

size_t countDistinctSorted(const std::vector<int>& a) {
    if (a.empty()) {
        return 0;
    }
    size_t count = 1;
    for (size_t i = 1; i < a.size(); ++i) {
        if (a[i] != a[i - 1]) {
            count++;
        }
    }
    return count;
}
