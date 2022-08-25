#ifndef MYNETFRAAMEWORK_THREAD_H
#define MYNETFRAAMEWORK_THREAD_H

namespace base
{
/*
	封装线程
*/
class Thread
{
public:
	typedef std::function<void ()> ThreadFunc;
	explicit Thread(ThreadFunc fun, const string& name = string());

	~Thread();

	void start();
	int join();
	
	pid_t tid() const {return tid_;}
	const string& name() {return name_;}
private:
	void setDefName();

	bool	started_;
	bool	joined_;
	pthread_t	pthreadId_;
	pid_t		tid_;
	ThreadFunc	func_;
	string		name_;
}

}

#endif
