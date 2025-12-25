#pragma once

#include <cstddef>
#include <vector>

struct SortStats {
    long long comparisons = 0;
    long long swaps = 0;
};

void quickSortHoare(std::vector<int>& a, SortStats& stats);
size_t countDistinctSorted(const std::vector<int>& a);
