#include "game-engine/Core/Dispatch/DispatchQueue.h"

void DispatchQueue::initialise()
{
    if ((mSem = sem_open("glSemaphore", O_CREAT, 0644, 0)) == SEM_FAILED)
    {
        std::cout << "Error initalising semaphore" << std::endl;
    }
    
    mThread.start(this);
}

void DispatchQueue::sendToQueue(const Task &task)
{
    mTasks.push(task);
    sem_post(mSem);
    std::cout << "Job added!" << std::endl;
}


Task DispatchQueue::getNextTask()
{
    Task front = mTasks.front();
    mTasks.pop();
    return front;
}
