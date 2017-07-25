#include "game-engine/Core/Dispatch/Thread.h"

#include "game-engine/Core/Dispatch/DispatchQueue.h"
#include "game-engine/Core/Dispatch/Task.h"

void DispatchThread::start(DispatchQueue* dispatchQueue)
{
    
    mDispatchQueue = dispatchQueue;
    
    pthread_create(&handle, NULL, run, mDispatchQueue);
}

void* DispatchThread::run(void* context)
{
    DispatchQueue *dispatchQueue = (DispatchQueue *)context;
    dispatchQueue->run();
    
    /*while(true)
    {
        sem_wait(dispatchQueue->getSemaphore());
        
        std::cout << "Job processing!" << std::endl;
        
        Task task = dispatchQueue->getNextTask();
        
        task.run();
    }*/
}
