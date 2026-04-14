#pragma once

#include <vector>
#include <algorithm>

template<typename T>
void insertion_sort(std::vector<T>& vec)
{
	int n = vec.size();
	
	if (n == 0 || n == 1) {
		return;
	}
	
	for (int j = 1; j < n; j++) {
		T key = vec[j];
		int i = j-1;
		while (i >= 0 && vec[i] > key) {
			vec[i+1] = vec[i];
			i -= 1;
		}
		vec[i+1] = key;
	}
	return;
}