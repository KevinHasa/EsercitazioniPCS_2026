#pragma once

#include <vector>
#include <algorithm>

template<typename T>
bool is_sorted(const std::vector<T>& vec)
{
	int n = vec.size();
	
	bool sorted = true;
	
	if (n == 0 || n == 1) 
	{
		return sorted;
	}
	
	for (int i = 0; i < n-1; i++) 
	{
			
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

template<typename T>
void insertionsort(std::vector<T>& vec)
{
	int n = vec.size();
	
	for (int j = 1; j < n; j++) 
	{
		T key = vec[j];
		int i = j-1;
		
		while (i >= 0 && vec[i] > key) 
		{
			vec[i+1] = vec[i];
			i -= 1;
		}
		vec[i+1] = key;
	}
}

template<typename T>
void bubblesort(std::vector<T>& vec)
{
	int n = vec.size();
	
	for (int i = 0; i < n-1; i++) 
	{
		for (int j = n-1; j > i; j-- ) 
		{
			if (vec[j] < vec[j-1]) 
			{
				std::swap(vec[j], vec[j-1]);
			}
		}
	}
}

template<typename T>
void selectionsort(std::vector<T>& vec)
{
	int n = vec.size();
	
	for (int i = 0; i < n-1; i++) 
	{
		 int min_index = i;
		for (int j = i+1; j < n; j++) 
		{
			if (vec[j] < vec[min_index]) 
			{
				min_index = j;
			}
		}
		std::swap(vec[i], vec[min_index]);
	}
}

template<typename T>
int partition(std::vector<T>& vec, int p, int r)
{
	T x = vec[r];
	int i = p-1;
	for (int j = p; j < r; j++) 
	{
		if (vec[j] <= x) {
			i = i +1;
			std::swap(vec[i], vec[j]);
		}
	}
	std::swap(vec[i+1], vec[r]);
	return i+1;
}

template<typename T>
void quicksort(std::vector<T>& vec, int p, int r)
{
	if (p < r) 
	{
		int q = partition(vec, p, r);
		quicksort(vec, p, q-1);
		quicksort(vec, q+1, r);
	}
}

template<typename T>
void modified_quicksort(std::vector<T>& vec, int p, int r)
{
	if (r - p + 1 < 211)
	{
		for (int j = p+1; j < r+1; j++) 
		{
			T key = vec[j];
			int i = j-1;
			
			while (i >= p && vec[i] > key) 
			{
				vec[i+1] = vec[i];
				i -= 1;
			}
		vec[i+1] = key;
		}
	}
	
	else if (p < r) 
	{
		int q = partition(vec, p, r);
		modified_quicksort(vec, p, q-1);
		modified_quicksort(vec, q+1, r);
	}
}

template<typename T>
void merge(std::vector<T>& vec, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	std::vector<T> L(n1);
	std::vector<T> R(n2);
	
	for (int i = 0; i < n1; i++)
	{
		L[i] = vec[p+i];
	}
	
	for (int j = 0; j < n2; j++)
	{
		R[j] = vec[q+j+1];
	}
	
	int i = 0;
	int j = 0;
	
	for (int k = p; k < r+1; k++) 
	{
		if (i < n1 && (j >= n2 || L[i] <= R[j]))
		{
			vec[k] = L[i];
			i = i+1;
		}
		
		else 
		{
			vec[k] = R[j];
			j = j+1;
		}
	}
}

template<typename T>
void mergesort(std::vector<T>& vec, int p, int r)
{
	if (p < r)
	{
		int q =(p+r)/2;
		mergesort(vec, p, q);
		mergesort(vec, q+1, r);
		merge(vec, p, q, r);
	}
}