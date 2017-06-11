#ifndef _COREMODULE_H
#define _COREMODULE_H

enum CoreModuleType
{
	CM_GRAPHICS,
	CM_AUDIO,
	CM_PHYICS,
	CM_INPUT,
};


class CoreModule
{
public:
	CoreModule(CoreModuleType type) : type(type) {}

	virtual bool initalise() = 0;
	virtual bool deinitalise() = 0;
    virtual bool update() = 0;
    
    const CoreModuleType& getType() { return this->type; }

private:
	CoreModuleType type;

};


#endif /* _COREMODULE_H */
