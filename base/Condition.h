#ifndef MYNETFRAAMEWORK_CONDITION_H 
#define MYNETFRAAMEWORK_CONDITION_H

#include "Mutex.h"

#include <pthread.h>

namespace base
{
class Condition
{
public:
	Condition(MutexLock& mutex) : mutex_(mutex)
	{
		pthread_cond_init(&pcond_, NULL);
	}
	~Condition()
	{
		pthread_cond_destroy(&pcond_)
	}
	void notify()
	{
		pthread_cond_signal(&pcond_);
	}
	void notifyAll()
	{
		pthread_cond_broadcast(&pcond_);
	}
	void wait()
	{
		pthread_cond_wait(&pcond_, mutex_.getPthreadMutex());
	}
	//bool waitForSecond(double seconds);
private:
	MutexLock& mutex_;
	pthread_cond_t pcond_;
}
}

#endif
