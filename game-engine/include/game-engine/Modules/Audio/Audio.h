#ifndef _AUDIO_H
#define _AUDIO_H

// STD
#include <string>
#include <map>

// Game Engine AR
#include "game-engine/Modules/CoreModule.h"

class AudioListener;
class AudioSource;


class Audio : public CoreModule
{
public:
    
    static Audio& getInstance()
    {
        static Audio instance;
        return instance;
    }
    
    bool initialise();
    bool deinitialise();
    bool update();
    
    //bool addAIProperty(const std::string &name, AIProperty *property);
    //bool removeAIProperty(const std::string &name);
    
private:
    
    //std::map<std::string, AIProperty *> aIProperties;
    
    Audio();
    Audio(Audio const&);              // Don't Implement
    void operator=(Audio const&);  // Don't implement
    
};

#endif /* _AUDIO_H */
