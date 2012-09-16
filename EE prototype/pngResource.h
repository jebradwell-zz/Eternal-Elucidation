#ifndef PNGRESOURCE_H
#define PNGRESOURCE_H

#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include <stdio.h>


class PNGResourceMaker : public ResourceMaker
{
public:
    virtual Resource * Create ( const std::string &Filename );    
    virtual const char * GetExtension () { return ".png"; }
};

class PNGResource : public Resource
{
public:
    PNGResource ( const std::string &Filename );
	virtual void *GetResource(){return &PNGImage;}
    virtual const std::string & GetName() const { return m_name; }
    virtual Type GetType() const { return "PNGResource"; }
    virtual void Dump(std::ostream & o) const;    
private:
    std::string m_name;
	sf::Image PNGImage;
	bool LoadingError;
};

#endif //PNGRESOURCE_H
