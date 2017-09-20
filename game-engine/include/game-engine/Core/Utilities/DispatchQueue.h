#ifndef _DISPATCHQUEUE_H
#define _DISPATCHQUEUE_H

#include <pthread/pthread.h>
#include <semaphore.h>
#include <queue>
#include <iostream>

#include "game-engine/Core/Utilities/Task.h"
#include "game-engine/Core/Utilities/Thread.h"

class DispatchQueue
{
    friend class DispatchThread;
    
private:
    std::queue<Task> mTasks;
    sem_t *mSem;
    DispatchThread mThread;
    unsigned int numTasks = 0;
    
public:
    DispatchQueue()
    {}
    
    void initialise(std::string name);
 
    void sendToQueue(const Task &task);
    
private:
 
    Task getNextTask();
    
    sem_t* getSemaphore() { return mSem; }
    
    std::string mName;
    
    void run();
    
 };

#endif /* _DISPATCHQUEUE_H */
