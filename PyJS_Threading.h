#ifndef PyJS_Threading_h__
#define PyJS_Threading_h__
#include "config.h"
#ifndef NO_THREADING


#ifdef HAVE_CXX_THREADS

#	include <mutex>
#	include <condition_variable>
typedef std::mutex CScriptMutex;
typedef std::unique_lock<std::mutex> CScriptUniqueLock;
typedef std::condition_variable CScriptCondVar;

#else

class CScriptMutex {
public:
	CScriptMutex();
	~CScriptMutex();
	void lock() { mutex->lock(); }
	void unlock() { mutex->unlock(); }
	void *getRealMutex() { return mutex->getRealMutex(); }
	class CScriptMutex_t{
	public:
//		virtual ~CScriptMutex_t()=0;
		virtual void lock()=0;
		virtual void unlock()=0;
		virtual void *getRealMutex()=0;
	};
private:
	CScriptMutex_t *mutex;

};

class CScriptUniqueLock {
public:
	CScriptUniqueLock(CScriptMutex &Mutex) : mutex(&Mutex) { mutex->lock(); }
	~CScriptUniqueLock() { mutex->unlock(); }
	CScriptMutex *mutex;
};

class CScriptCondVar {
public:
	CScriptCondVar();
	virtual ~CScriptCondVar();
	void notify_one() { condVar->notify_one(); }
	void wait(CScriptUniqueLock &Lock) { condVar->wait(Lock); }
	class CScriptCondVar_t{
	public:
		virtual void notify_one()=0;
		virtual void wait(CScriptUniqueLock &Lock)=0;
	};
private:
	CScriptCondVar_t *condVar;
};

#endif /*HAVE_CXX_THREADS*/


class CScriptSemaphore
{
private:
	CScriptCondVar cond;
	CScriptMutex mutex;
	unsigned int count;
	unsigned int max_count;

public:
	CScriptSemaphore(unsigned int currentCount=1, unsigned int maxCount=1) : count(currentCount), max_count(maxCount) {}
	void post() {
		CScriptUniqueLock lock(mutex);

		++count;
		cond.notify_one();
	}
	void wait() {
		CScriptUniqueLock lock(mutex);
		while(!count) cond.wait(lock);
		--count;
	}
	unsigned int currentWaits() {
		CScriptUniqueLock lock(mutex);
		return count;
	}
};

class CScriptThread {
public:
	CScriptThread();
	virtual ~CScriptThread();
	void Run() { thread->Run(); }
	int Stop(bool Wait=true) { return thread->Stop(Wait); }
	int retValue() { return thread->retValue(); }
	virtual int ThreadFnc()=0;
	virtual void ThreadFncFinished();
	bool isActiv() { return thread->isActiv(); }
	bool isRunning() { return thread->isRunning(); }
	bool isStarted() { return thread->isStarted(); }
	class CScriptThread_t{
	public:
		virtual void Run()=0;
		virtual int Stop(bool Wait)=0;
		virtual bool isActiv()=0;
		virtual bool isRunning()=0;
		virtual bool isStarted()=0;
		virtual int retValue()=0;
	};
private:
	CScriptThread_t *thread;
};

class CScriptCoroutine : protected CScriptThread {
public:
	CScriptCoroutine() : wake_thread(0), wake_main(0) {}
	typedef struct{} StopIteration_t;
	static StopIteration_t StopIteration;
	bool next(); // returns true if coroutine is running
protected:
	virtual int Coroutine()=0;
	void yield();
	bool yield_no_throw();
private:
	virtual int ThreadFnc();
	virtual void ThreadFncFinished();
	CScriptSemaphore wake_thread;
	CScriptSemaphore wake_main;
};



#endif // NO_THREADING
#endif // PyJS_Threading_h__
