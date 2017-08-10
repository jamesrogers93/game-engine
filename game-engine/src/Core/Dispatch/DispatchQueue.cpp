#include "game-engine/Core/Dispatch/DispatchQueue.h"

void DispatchQueue::initialise(std::string name)
{
    this->mName = name;
    
    if ((mSem = sem_open(name.data(), O_CREAT, 0644, 0)) == SEM_FAILED)
    {
        std::cout << "Error initalising semaphore" << std::endl;
    }
    
    mThread.start(this);
}

void DispatchQueue::sendToQueue(const Task &task)
{
    mTasks.push(task);
    numTasks++;
    sem_post(mSem);
    //std::cout << "Job added!" << std::endl;
}

Task DispatchQueue::getNextTask()
{
    Task front = mTasks.front();
    mTasks.pop();
    numTasks--;
    return front;
}

void DispatchQueue::run()
{
    while(true)
    {
        sem_wait(getSemaphore());
        
        //std::cout << "Job processing!" << std::endl;
        
        Task task = getNextTask();
        
        task.run();
    }
}
