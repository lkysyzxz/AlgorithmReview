#include<iostream>
#include"Heap.h"
using namespace std;
int main()
{
	PriorityQueue<int> pq;
	for (int i = 10; i >= 0; i--)
	{
		pq.Push(i);
	}
	for (int i = 0; i <= 10; i++) {
		cout << pq.Top() << endl;
		pq.Pop();
	}
	return 0;
}