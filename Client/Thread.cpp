/*
   File:  Thread.h
*/
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
#include <process.h>
#else
#include <string>
#include <iostream>
#include <errno.h>
#endif

#include "Thread.h"

Thread::Thread()
:started(false), detached(false)
{ }

Thread::~Thread() {
  stop();
}

void* Thread::run(void *param) {
  return NULL;
}

bool Thread::start(void *param) {
  if(!started) {
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
     parameters = param;
     if(threadHandle =
           CreateThread(NULL,0,threadFunction,this,0,&threadID))
     {
        if(detached)
           CloseHandle(threadHandle);
        started = true;
     }
#else
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);

    if(detached)
      pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED);

    int res;
    if((res=pthread_create(&threadID, &attributes, threadFunction, this)) != 0) {

      std::string s;
      switch(res) {

        case ENOMEM:
		s="ThreadCreate error: No resources"; break;
	case EINVAL:
		s="ThreadCreate error: Invalid attribute"; break;
	case EPERM:
		s="ThreadCreate error: No permission for scheduling param"; break;
      }

      std::cerr << s << std::endl;
      return false;  // False
    }
    else
      started = true;

    pthread_attr_destroy(&attributes);
#endif
  }
  return started;
}

void* Thread::wait() {
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
  DWORD status = static_cast<DWORD>(NULL);
  if(started && !detached) {
    WaitForSingleObject(threadHandle,INFINITE);
    GetExitCodeThread(threadHandle,&status);
    CloseHandle(threadHandle);
    detached=true;
  }
  return reinterpret_cast<void*>(status);

#else
  void *status = NULL;
  if(started && !detached) {

    int res;
    if((res=pthread_join(threadID,&status)) !=0) {
    	std::string s;
      	switch(res) {

        case ESRCH:
		s="wait error: No thread with this thread-id found"; break;
	case EINVAL:
		s="wait error: Not a joinable thread"; break;
	case EDEADLK:
		s="wait error: Recursive deadlock"; break;
       }
       std::cerr << s << std::endl;
    }
    detached = true;
  }
  return status;
#endif
}

void Thread::stop() {
  if(started && !detached) {
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
    TerminateThread(threadHandle,0);
    CloseHandle(threadHandle);

#else
    pthread_cancel(threadID);
    pthread_detach(threadID);
#endif
    detached=true;
  }
}

void Thread::detach() {
  if(started && !detached) {
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
    CloseHandle(threadHandle);
#else
    pthread_cancel(threadID);
    pthread_detach(threadID);
#endif
    detached=true;
  }
}

unsigned long Thread::getThreadID() {
  return threadID;
}

unsigned long Thread::getCurrentThreadID() {
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
   return GetCurrentThreadId();
#else
   return threadID;
#endif
}

void Thread::sleep(int mSec) {
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
  ::Sleep(mSec);

#else
  timespec sleepTime, timeLeft;
  sleepTime.tv_sec = mSec / 1000; // seconds
  sleepTime.tv_nsec = 1000000 *(mSec % 1000);  //nanoseconds

  while( nanosleep(&sleepTime, &timeLeft)==-1) { //
    if(errno==EINTR) { // Interrupted by a signal
      sleepTime = timeLeft;
    }
    else
      break;
  } // while
#endif
}

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
static unsigned long __stdcall threadFunction(void *pThread) {

  Thread* thread = static_cast<Thread*>(pThread);
  return
    reinterpret_cast<unsigned long>(thread->run(thread->parameters));
}
#else

static void* threadFunction(void *pThread)
{
  Thread *thread =  static_cast<Thread*>(pThread);
  return thread->run(thread->parameters);
}

#endif








