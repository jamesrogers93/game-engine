#ifndef _TASK_H
#define _TASK_H

class Task
{
public:
    
    Task(std::function<void(void)> functionPtr) : mFunctionPtr(functionPtr)
    {}
    
    void run()
    {
        mFunctionPtr();
    }
    
private:
    std::function<void(void)> mFunctionPtr;
};

#endif /* _TASK_H */
