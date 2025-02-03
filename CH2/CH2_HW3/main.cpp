#include <bits/stdc++.h>
#include "SimpleVector.h"
int main()
{
	using namespace std;
	SimpleVector<int> simpleVector;
	simpleVector.push_back(1);
	simpleVector.push_back(2);
	simpleVector.push_back(3);
	simpleVector.push_back(4);
	simpleVector.pop_back();
	SimpleVector<int> simpleVector2(simpleVector);
	simpleVector2.push_back(10);
	simpleVector2.push_back(12);
	simpleVector2.pop_back();
	simpleVector2.push_back(15);
	simpleVector2.push_back(14);
	simpleVector2.push_back(13);
	simpleVector2.push_back(11);
	simpleVector2.push_back(16);
	simpleVector2.push_back(17);
	simpleVector2.push_back(18);

	simpleVector2.resize(20);
	simpleVector2.sortData();

	for (int i = 0; i < simpleVector2.size(); ++i)
	{
		cout << simpleVector2.data[i] << ' ';
	}

	return 0;
}
