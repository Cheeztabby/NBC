#pragma once
#include <algorithm> 

template<typename T>
class SimpleVector
{
public:
	T* data = nullptr;
	int currentSize = 0;
	int currentCapacity = 0;

public:
	void resize(int newCapacity);
	SimpleVector(int capacity = 10);
	SimpleVector(const SimpleVector& other);
	~SimpleVector();
	void push_back(const T& value);
	void pop_back();
	int size();
	int capacity();
	void sortData();
};

template<typename T>
void SimpleVector<T>::resize(int newCapacity)
{
	if (currentCapacity < newCapacity)
	{
		T* newData = new T[newCapacity];
		for (int i = 0; i < currentSize; ++i)
		{
			newData[i] = data[i];
		}
		// std::vector와 유사하게 기본 크기만큼은 원소 값을 유지하고 새로운 크기만큼은 0으로 할당함.
		for (int i = currentSize; i < newCapacity; ++i)
		{
			newData[i] = 0;
		}
		delete[] data;
		data = newData;
		currentCapacity = newCapacity;
		currentSize = newCapacity;
	}
	// 문제 조건상 배열 크기보다 작으면 아무 동작하지 않음
	/*else
	{

	}*/
}

template<typename T>
inline SimpleVector<T>::SimpleVector(int capacity)
{
	currentCapacity = capacity;
	data = new T[currentCapacity];
}

template<typename T>
inline SimpleVector<T>::SimpleVector(const SimpleVector& other)
{
	currentSize = other.currentSize;
	currentCapacity = other.currentCapacity;
	data = new T[currentCapacity];
	for (int i = 0; i < currentSize; ++i)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
SimpleVector<T>::~SimpleVector()
{
	delete[] data;
}

template<typename T>
void SimpleVector<T>::push_back(const T& value)
{
	int addSize = 5;
	if (currentSize >= currentCapacity)  // capacity 재할당. 요구사항 조건에서처럼 +5만큼 늘림
	{
		T* newData = new T[currentCapacity + addSize];
		for (int i = 0; i < currentSize; ++i)
		{
			newData[i] = data[i];
		}
		// resize()와 다르게 새로운 크기까지 0으로 빈공간을 채우지 않음. currentSize 변화 없음
		delete[] data;
		data = newData;
	}
	data[currentSize++] = value; // capacity에 여유가 있을때는 O(1) 시간복잡도로 삽입
}

template<typename T>
void SimpleVector<T>::pop_back()
{
	if (currentSize > 0)
	{
		data[--currentSize] = 0;
	}
	else
	{
		std::cout << "SimpleVector: empty\n";
	}
}

template<typename T>
int SimpleVector<T>::size()
{
	return currentSize;
}

template<typename T>
int SimpleVector<T>::capacity()
{
	return currentCapacity;
}

template<typename T>
void SimpleVector<T>::sortData()
{
	std::sort(data, data + currentSize);
}
