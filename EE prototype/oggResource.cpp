#include "oggResource.h"
#include <iostream>

OGGResource::OGGResource ( const std::string &Filename )
{
	this->m_name = Filename;
	this->LoadingError = this->OGGSoundBuffer.LoadFromFile(Filename);
}

Resource * OGGResourceMaker::Create( const std::string &Filename )
{
    return new OGGResource(Filename);
}

void OGGResource::Dump(std::ostream & o) const
{
    o << "Resource address: " << this << "\n";
    o << "Resource type: " << GetType() << "\n";
    o << "Name: " << m_name << "\n";
}
