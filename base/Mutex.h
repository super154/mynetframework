#ifndef MYNETFRAAMEWORK_MUTEX_H
#define MYNETFRAAMEWORK_MUTEX_H

#include <pthread.h>
#include <assert.h>
namespace base
{
/*
	线程互斥锁，简单封装线程库方法
*/
class MutexLock
{
private:
	pthread_mutex_t mutex_;		// 互斥锁
	pid_t holder_;				// 当前所有者
public:
	MutexLock() : holder_(0)
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	~MutexLock()
	{
		assert(holder_ == 0);
		pthread_mutex_destroy(&mutex_);
	}
	void lock()
	{
		pthread_mutex_lock(&mutex_);
		// TODO 增加对当前锁所有者的修改
	}
	void unlock()
	{
		pthread_mutex_unlock(&mutex_);
		// TODO 增加对当前锁所有者的修改
	}
	pthread_mutex_t* getPthreadMutex()
	{
  		return &mutex_;
	}	
};

/*
	互斥锁控制器，利用RAII机制去管理锁
*/
class MutexLockGuard 
{
public:
	MutexLockGuard(MutexLock& mutex) : mutex_(mutex)
	{
		mutex_.lock();
	}
	~MutexLockGuard()
	{
		mutex_.unlock();
	}
private:
	MutexLock& mutex_;
};

}

#endif
