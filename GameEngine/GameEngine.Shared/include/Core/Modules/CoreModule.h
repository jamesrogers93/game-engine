#ifndef _COREMODULE_H
#define _COREMODULE_H

enum CoreModuleType
{
	CMT_GRAPHICS,
	CMT_AUDIO,
	CMT_PHYICS,
	CMT_INPUT,
};


class CoreModule
{
public:
	CoreModule(CoreModuleType type) : moduleType(type) {}

	virtual bool initalise() = 0;
	virtual bool deinitalise() = 0;

private:
	CoreModuleType moduleType;

};


#endif /* _COREMODULE_H */
