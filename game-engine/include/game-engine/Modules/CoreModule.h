#ifndef _COREMODULE_H
#define _COREMODULE_H

#include <cstddef>

enum class CoreModuleType
{
	CM_GRAPHICS,
    CM_AR,
    CM_ANIMATION,
	CM_AUDIO,
	CM_PHYSICS,
	CM_INPUT,
    CM_GUI
};

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

class CoreModule
{
public:
	CoreModule(CoreModuleType type) : type(type) {}

	virtual bool initialise() = 0;
	virtual bool deinitialise() = 0;
    virtual bool update() = 0;
    
    const CoreModuleType& getType() { return this->type; }

private:
	CoreModuleType type;

};


#endif /* _COREMODULE_H */
