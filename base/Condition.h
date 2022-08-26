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
private:
	MutexLock& mutex_;
	pthread_cond_t pcond_;
}
}

#endif
