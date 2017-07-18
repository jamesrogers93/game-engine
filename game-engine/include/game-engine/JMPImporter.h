#ifndef _JMPIMPORTER_H
#define _JMPIMPORTER_H

#include <string>
#include <utility>

template <class T>
class JMPImporter
{
protected:
    
    JMPImporter(){}
    
    T* importedObject;
    
public:
    
    virtual bool Import(const std::string &path) = 0;
    
    T* getImportedObject() { return importedObject; }
};

#endif /* _JMPIMPORTER_H */
