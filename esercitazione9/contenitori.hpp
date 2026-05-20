#pragma once
#include <list>

template<typename T>
class fifo
{
	std::list<T> data;
	
public:
	
	void put(const T& value) {
		data.push_back(value);
	}
	
	/* essendo fifo tolgo il primo elemento */
	T get() {
		T valore = data.front();
		data.pop_front();
		return valore;
	}
	
	bool empty() const {
		return data.empty();
	}
	
};

template<typename T>
class lifo
{
		std::list<T> data;
		
public:
	
	void put(const T& value) {
		data.push_back(value);
	}
	
	/* essendo lifo, tolgo l'ultimo elemento */
	T get() {
		T valore = data.back();
		data.pop_back();
		return valore;
	}
	
	bool empty() const {
		return data.empty();
	}
	
};