#pragma once

#include <vector>
#include <algorithm>

template<typename T>
void bubble_sort(std::vector<T>& vec)
{
	int n = vec.size();
	
	if (n == 0 || n == 1) {
		return;
	}
	
	else {
		for (int i = 0; i < n-1; i++) {
			for (int j = n-1; j > i; j-- ) {
				if (vec[j] < vec[j-1]) {
					std::swap(vec[j], vec[j-1]);
				}
			}
		}
		return;
	}
}