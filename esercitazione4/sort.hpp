#pragma once

#include <vector>

template<typename T>
bool is_sorted(const std::vector<T>& vec)
{
	int n = vec.size();
	
	bool sorted = true;
	
	if (n == 0 || n == 1) {
		return sorted;
	}
	
	for (int i = 0; i < n-1; i++) {
			
		if (vec[i+1] >= vec[i]) {
			continue;
		}
			
		else {
			sorted = false;
			break;
		}
	}
	return sorted;
}