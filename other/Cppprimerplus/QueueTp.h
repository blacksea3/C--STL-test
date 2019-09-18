#pragma once
#include "global.h"

//Queueƒ£∞Â¿‡
template <class Type>
class QueueTp
{
private:
	enum {MAX = 10};
	Type items[MAX];
	int front;
	int end;
public:
	QueueTp();
	bool isempty();
	bool isfull();
	bool push(const Type& item);
	bool pop(Type& item);
	~QueueTp();
};

void QueueTpClassTest();
