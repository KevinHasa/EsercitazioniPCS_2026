#pragma once

#include <vector>
#include <algorithm>

template<typename T>
void selection_sort(std::vector<T>& vec)
{
	int n = vec.size();
	
	if (n == 0 || n == 1) {
		return;
	}
	
	for (int i = 0; i < n-1; i++) {
		 int min_index = i;
		for (int j = i+1; j < n; j++) {
			if (vec[j] < vec[min_index]) {
				min_index = j;
			}
		}
		std::swap(vec[i], vec[min_index]);
	}
	return;
}