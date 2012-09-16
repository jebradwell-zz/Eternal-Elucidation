#ifndef OGGResource_H
#define OGGResource_H

#include "SFML/Audio.hpp"
#include "ResourceManager.h"
#include <stdio.h>


class OGGResourceMaker : public ResourceMaker
{
public:
    virtual Resource * Create ( const std::string &Filename );    
    virtual const char * GetExtension () { return ".ogg"; }
};

class OGGResource : public Resource
{
public:
    OGGResource ( const std::string &Filename );
	virtual void *GetResource(){return &OGGSoundBuffer;};
    virtual const std::string & GetName() const { return m_name; }
    virtual Type GetType() const { return "OGGResource"; }
    virtual void Dump(std::ostream & o) const;    
private:
    std::string m_name;
	sf::SoundBuffer OGGSoundBuffer;
	bool LoadingError;
};

#endif //OGGResource_H
