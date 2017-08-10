#ifndef _TASK_H
#define _TASK_H


class Task
{
public:
    
    Task(std::function<void()> functionPtr) : mFunctionPtr(functionPtr)
    {}
    
    void run()
    {
        mFunctionPtr();
    }
    
private:
    std::function<void()> mFunctionPtr;
};

#endif /* _TASK_H */
