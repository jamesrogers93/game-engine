#ifndef _GLDATA_H
#define _GLDATA_H

struct UpdateNotification
{
public:
    void notify() { mFlag = true; }
    void reset() { mFlag = false; }
    
    const bool& getFlag() const { return mFlag; }
private:
    bool mFlag = true;
};

#endif /* _GLDATA_H */
