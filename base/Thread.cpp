#include "Thread.h"

#include <stdio.h>

namespace base
{

Thread::Thread(ThreadFunc func,const std::string& name) 
	: started_(false), 
	  joined_(false), 
	  pthreadId_(0), 
	  tid_(0), 
	  func_(std::move(func)), 
	  name_(name)
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

}
