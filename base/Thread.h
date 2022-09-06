#ifndef MYNETFRAAMEWORK_THREAD_H
#define MYNETFRAAMEWORK_THREAD_H

#include <functional>
#include <memory>
#include <pthread.h>
#include <string>
#include "CountDownLatch.h"

namespace base
{
/*
	封装线程
*/
class Thread
{
public:
	typedef std::function<void ()> ThreadFunc;
	explicit Thread(ThreadFunc fun, const std::string& name = std::string());

	~Thread();

	void start();
	int join();
	
	pid_t tid() const {return tid_;}
	const std::string& name() {return name_;}
private:
	void setDefName();

	bool	started_;
	bool	joined_;
	pthread_t	pthreadId_;
	pid_t		tid_;
	ThreadFunc	func_;
	CountDownLatch latch_;
	std::string		name_;
};
}

#endif
