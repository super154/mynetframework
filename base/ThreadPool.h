#ifndef MYNETFRAAMEWORK_THREADPOOL_H
#define MYNETFRAAMEWORK_THREADPOOL_H

#include "Mutex.h"
#include "Condition.h"
#include "Thread.h"
#include "Type.h"

namespace base
{
class ThreadPool
{
public:
	typedef std::function<void ()> Task;

	explicit ThreadPool(const string& nameArg = string("ThreadPool"));
	~ThreadPool();

	void setMaxQueueSize(int maxSize) {maxQueueSize_ = maxSize;};
	void setThreadInitCallbase(const Task& cb) {threadInitCallbase_ = cb};
	void start(int numThreads);
	void stop();
	const string& name() const { return name_};
	size_t queueSize() const ;
	void run(Task t);
private:
	bool isFull() const;
	void runInThread();
	Task task();

	
}
}

#include <deque>
#include <vector>

#endif
