#ifndef _JMPIMPORTER_H
#define _JMPIMPORTER_H

#include <string>
#include <utility>
#include <thread>

template <class T>
class JMPImporter
{
protected:
    
    JMPImporter()
    {}
    
    T* importedObject;
    std::thread mThread;
    
public:
    
    virtual void ImportAsynchronously(const std::string &path) = 0;
    virtual bool Import(const std::string &path) = 0;
    
    void join()
    {
        if(mThread.joinable())
        {
            mThread.join();
        }
    }
    
    T* getImportedObject() { return importedObject; }
    
};

#endif /* _JMPIMPORTER_H */
