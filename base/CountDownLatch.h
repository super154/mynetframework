#ifndef MYNETFRAAMEWORK_COUNTDOWN_H
#define MYNETFRAAMEWORK_COUNTDOWN_H 

#include "Condition.h"
#include "Mutex.h"

namespace base
{
class CountDownLatch
{
public:
	explicit CountDownLatch(int count);

	void wait();

	void dountDown();

	int getCount() const;
private:
	mutable MutexLock mutex_;
	Condition condition_;
	int count_;
}
}

#endif
