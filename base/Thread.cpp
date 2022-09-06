#include "Thread.h"
#include "CurrentThread.h"
#include "CountDownLatch.h"

#include <stdio.h>
#include <type_traits>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace base
{
pid_t gettid()
{
	return static_cast<pid_t>(::syscall(SYS_gettid));
}
void afterFork()
{
	
}
class ThreadNameInitializer
{
	public:
 	ThreadNameInitializer()
	{
    	CurrentThread::tid();
    	pthread_atfork(NULL, NULL, &afterFork);
  	}
};

ThreadNameInitializer init;

struct ThreadData
{
  	typedef base::Thread::ThreadFunc ThreadFunc;
  	ThreadFunc func_;
  	string name_;
  	pid_t* tid_;
  	CountDownLatch* latch_;

  	ThreadData(ThreadFunc func,
             const string& name,
             pid_t* tid,
             CountDownLatch* latch)
    : func_(std::move(func)),
      name_(name),
      tid_(tid),
      latch_(latch)
  	{ }

  	void runInThread()
  	{
    	*tid_ = CurrentThread::tid();
    	tid_ = NULL;
    	latch_->countDown();
    	latch_ = NULL;

    	::prctl(PR_SET_NAME, CurrentThread::t_threadName);
    	try
    	{
    	  	func_();
    	}
    	catch (const std::exception& ex)
    	{
      		fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
      		fprintf(stderr, "reason: %s\n", ex.what());
      		abort();
    	}
    	catch (...)
    	{
      		fprintf(stderr, "unknown exception caught in Thread %s\n", name_.c_str());
      		throw; // rethrow
    	}
  	}
};
void* startThread(void* obj)
{
 	ThreadData* data = static_cast<ThreadData*>(obj);
  	data->runInThread();
  	delete data;
  	return NULL;
}
Thread::Thread(ThreadFunc func,const std::string& name) 
	: started_(false), 
	  joined_(false), 
	  pthreadId_(0), 
	  tid_(0), 
	  func_(std::move(func)), 
	  name_(name),
	  latch_(1)
{
	setDefName();
}

Thread::~Thread()
{
	if(started_ && !joined_)
	{
		pthread_detach(pthreadId_);
	}
}

void Thread::start()
{
	started_ = true;
	ThreadData* data = new ThreadData(func_, name_, &tid_, &latch_);
	if(pthread_create(&pthreadId_, NULL, &startThread, data))
	{
		started_ = false;
	}
	else
	{
		latch_.wait();
		assert(tid_ > 0);
	}
}

int Thread::join()
{
	assert(started_);
	assert(!joined_);
	joined_ = true;
	return pthread_join(pthreadId_, NULL);
}
void CurrentThread::cacheTid()
{
     if (t_cachedTid == 0)
    {
        t_cachedTid = gettid();
        t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
    }
}

}
