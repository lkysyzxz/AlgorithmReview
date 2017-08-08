#pragma once
#include<map>
#include<vector>
#include<algorithm>
#include<assert.h>
/****
 *	Author:	º®½­Ñ©1719
 *	Date:	2017.8.8
 *	Email:	<lkysyzxz@outlook.com>
 *	Detail:	This files define the data struct named heap.I used BaseHeap as the base class and
 *			create PriorityQueue by using BaseHeap.
 *	Other:	Have your fun.
 */
template<class _Item>
class BaseHeap
{
protected:
	std::vector<_Item> heap;
	int count;
protected:
	virtual void HeapAdjust(int root)
	{
		int left = root * 2 + 1;
		int right = root * 2 + 2;
		int select = root;
		while (root < count) {
			left = root * 2 + 1;
			right = root * 2 + 2;
			select = root;
			if (left < count && heap[left] < heap[select])
				select = left;
			if (right < count&&heap[right] < heap[select])
				select = right;
			if (select != root)
			{
				swap(heap[select], heap[root]);
				root = select;
			}
			else
			{
				break;
			}
		}
	}
public:
	BaseHeap()
	{
		count = 0;
	}

	int Size()
	{
		return count;
	}

	virtual void Push(const _Item& t)
	{
		if (count == heap.size())
			heap.push_back(t);
		else
			heap[count] = t;
		count++;
		int cur = Size() - 1;
		while (cur > 0 && (heap[cur] < heap[(cur - 1) / 2]))
		{
			std::swap(heap[cur], heap[(cur - 1) / 2]);
			cur = (cur - 1) / 2;
		}
	}

	_Item Top()
	{
		return heap[0];
	}


	virtual void Pop()
	{
		swap(heap[count - 1], heap[0]);
		count--;
		HeapAdjust(0);
	}

	virtual void UpdateElement(int index, const _Item& newValue)
	{
		heap[index] = newValue;
		int cur = index;
		while (cur > 0 && (heap[cur] < heap[(cur - 1) / 2]))
		{
			std::swap(heap[cur], heap[(cur - 1) / 2]);
			cur = (cur - 1) / 2;
		}
		HeapAdjust(index);
	}

	virtual ~BaseHeap()
	{
		if (heap.size() > 0)
			heap.clear();
	}
};

template<class _PQItem>
class PriorityQueue :public BaseHeap<_PQItem>
{
public:
	PriorityQueue() :BaseHeap<_PQItem>()
	{

	}

	int Find(const _PQItem& t)
	{
		for (int i = 0; i < Size(); i++)
		{
			if (heap[i] == t)
				return i;
		}
		return -1;
	}

	const _PQItem& GetItem(int index)
	{
		return heap[index];
	}

	void Clear()
	{
		if (heap.size() > 0)
			heap.clear();
		if (Size() > 0)
			count = 0;
	}
};