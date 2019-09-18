#include "QueueTp.h"

template<class Type>
QueueTp<Type>::QueueTp()
{
	front = 0;
	end = 0;
}

template<class Type>
bool QueueTp<Type>::isempty()
{
	return front == end;
}

template<class Type>
bool QueueTp<Type>::isfull()
{
	return (front - (end + 1))%MAX == 0;
}

template<class Type>
bool QueueTp<Type>::push(const Type & item)
{
	if (isfull()) return false;
	else
	{
		items[end++] = item;
		end %= MAX;
		return true;
	}
}

template<class Type>
bool QueueTp<Type>::pop(Type & item)
{
	if (isempty()) return false;
	else
	{
		item = items[front++];
		front %= MAX;
		return true;
	}
}

template<class Type>
QueueTp<Type>::~QueueTp()
{
}

void QueueTpClassTest()
{
	QueueTp<int> q;

	for (int i = 0; i < 15; ++i)
	{
		cout << "ret of q.push(i): " << q.push(i) << endl;
	}

	for (int i = 0; i < 2; ++i)
	{
		int temp;
		cout << "ret of q.pop(temp): " << q.pop(temp);
		cout << "temp: " << temp << endl;
	}

	for (int i = 0; i < 15; ++i)
	{
		cout << "ret of q.push(i): " << q.push(i) << endl;
	}

	for (int i = 0; i < 15; ++i)
	{
		int temp;
		cout << "ret of q.pop(temp): " << q.pop(temp);
		cout << "temp: " << temp << endl;
	}
}
