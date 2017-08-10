#ifndef _GLTHREAD_H
#define _GLTHREAD_H

#include <pthread/pthread.h>
#include <semaphore.h>
#include <queue>
#include <iostream>

/*class GLThread
{
private:
    std::queue<std::function<void(void)> > mJobs;
    pthread_t handle;
    sem_t *sem;
    
public:
    static GLThread& getInstance()
    {
        static GLThread instance;
        return instance;
    }
    
    void giveJob(std::function<void(void)> job)
    {
        this->mJobs.push(job);
        sem_post(sem);
        std::cout << "Job added!" << std::endl;
    }
    
private:
    GLThread()
    {
        //sem_init(sem,0,0);
        
        if ((sem = sem_open("glSemaphore", O_CREAT, 0644, 0)) == SEM_FAILED) {
            std::cout << "Error initalising semaphore" << std::endl;
        }
        
        pthread_create(&handle, NULL, run, NULL);
    }
    
    GLThread(GLThread const&);              // Don't Implement
    void operator=(GLThread const&);		// Don't implement
    
    
    std::function<void(void)> getNextJob()
    {
        std::function<void(void)> front = mJobs.front();
        mJobs.pop();
        return front;
    }
    
    sem_t* getSemaphore() { return sem; }

    static void *run(void*)
    {
        while(true)
        {
            sem_wait(GLThread::getInstance().getSemaphore());
            std::cout << "Job processing!" << std::endl;
            std::function<void(void)> job = GLThread::getInstance().getNextJob();
            job();
        }
    }
};*/

#endif /* _GLTHREAD_H */
