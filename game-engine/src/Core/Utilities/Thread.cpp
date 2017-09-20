#include "game-engine/Core/Utilities/Thread.h"

#include "game-engine/Core/Utilities/DispatchQueue.h"
#include "game-engine/Core/Utilities/Task.h"

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
