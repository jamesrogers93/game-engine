#ifndef _THREAD_H
#define _THREAD_H

#include <pthread/pthread.h>

class DispatchQueue;

class DispatchThread
{
public:
    DispatchThread()
    {}
    
    void start(DispatchQueue* dispatchQueue);
private:
    
    pthread_t handle;
    DispatchQueue* mDispatchQueue;
    
    static void* run(void* context);
};

#endif /* _TASK_H */
