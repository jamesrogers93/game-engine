#ifndef _DISPATCHQUEUE_H
#define _DISPATCHQUEUE_H

#include <pthread/pthread.h>
#include <semaphore.h>
#include <queue>
#include <iostream>

#include "game-engine/Core/Dispatch/Task.h"
#include "game-engine/Core/Dispatch/Thread.h"

class DispatchQueue
{
    friend class DispatchThread;
    
private:
    std::queue<Task> mTasks;
    sem_t *mSem;
    DispatchThread mThread;
    
public:
    DispatchQueue()
    {}
    
    void initialise();
 
    void sendToQueue(const Task &task);
    
private:
 
    Task getNextTask();
    
    sem_t* getSemaphore() { return mSem; }
    
 };

#endif /* _DISPATCHQUEUE_H */
