#include <iostream>

int getSum(int* arr, int length)
{
	int sum = 0;
	for (int i = 0; i < length; ++i)
	{
		sum += arr[i];
	}
	return sum;
}

double getAverage(int* arr, int length)
{
	return (double)getSum(arr, length) / length;
}
void bubble_sort(int* arr, int length, int flag) // bubble sort
{
	for (int i = length - 1; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (flag == 1) // 오름차순
			{
				if (arr[j] > arr[j + 1]) // swap
				{
					int temp = arr[j + 1];
					arr[j + 1] = arr[j];
					arr[j] = temp;
				}
			}
			else if (flag == 2) // 내림차순
			{
				if (arr[j] < arr[j + 1]) // swap
				{
					int temp = arr[j + 1];
					arr[j + 1] = arr[j];
					arr[j] = temp;
				}
			}
			else
			{
				// error
				std::cout << "invalid sort flag\n";
				return;
			}
		}
	}
}
void printArr(int* arr, int length)
{
	for (int i = 0; i < length; ++i)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}
int main()
{
	const int ARR_SIZE = 5;
	int arr[ARR_SIZE] = { 0 };
	for (int i = 0; i < ARR_SIZE; ++i)
	{
		std::cin >> arr[i];
	}
	//int length = sizeof(arr) / sizeof(int);

	std::cout << getSum(arr, ARR_SIZE) << '\n';
	std::cout << getAverage(arr, ARR_SIZE) << '\n';

	bubble_sort(arr, ARR_SIZE, 1); // 오름차순
	printArr(arr, ARR_SIZE);

	bubble_sort(arr, ARR_SIZE, 2); // 내림차순
	printArr(arr, ARR_SIZE);

	return 0;
}