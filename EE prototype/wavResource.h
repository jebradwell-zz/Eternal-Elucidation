#ifndef WAVResource_H
#define WAVResource_H

#include "SFML/Audio.hpp"
#include "ResourceManager.h"
#include <stdio.h>


class WAVResourceMaker : public ResourceMaker
{
public:
    virtual Resource * Create ( const std::string &Filename );    
    virtual const char * GetExtension () { return ".wav"; }
};

class WAVResource : public Resource
{
public:
    WAVResource ( const std::string &Filename );
	virtual void *GetResource(){return &WAVSoundBuffer;}
    virtual const std::string & GetName() const { return m_name; }
    virtual Type GetType() const { return "WAVResource"; }
    virtual void Dump(std::ostream & o) const;   
private:
    std::string m_name;
	sf::SoundBuffer WAVSoundBuffer;
	bool LoadingError;
};

#endif //WAVResource_H
