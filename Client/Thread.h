/*
   File:        Thread.h

   Objective:   Thread class for Windows and Linux/Unix
                To create and start executing a new thread:
                - derive a new class from Thread
                - implement the run function
                - instantiate an object of the new class
                - call the object's start function
                This will cause the run function to start
                executing in a new thread. One void* pointer
                argument can be passed to the run function.

   Date:        2008 Örjan Sterner
*/

#ifndef THREAD_H
#define THREAD_H

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
#include <windows.h>
static unsigned long __stdcall threadFunction(void*);
#else
#include <pthread.h>
static void* threadFunction(void *);
#endif


class Thread {

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
friend unsigned long __stdcall threadFunction(void*);
#else
friend void* threadFunction(void *);
#endif

public:
  Thread();
  virtual ~Thread();
  bool start(void* =0);
  void detach();
  void* wait();
  void stop();
  unsigned long getThreadID();
  unsigned long getCurrentThreadID();
  static void sleep(int mSec); // milli secs
protected:
  virtual void* run(void*)=0;
private:

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32)
  HANDLE threadHandle;
  unsigned long threadID;
#else
  pthread_t threadHandle;
  pthread_t threadID;
#endif
  bool started;
  bool detached;
  void* parameters;
};

#endif
