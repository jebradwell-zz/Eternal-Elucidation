#include "wavResource.h"
#include <iostream>

WAVResource::WAVResource ( const std::string &Filename )
{
	this->m_name = Filename;
	this->LoadingError = this->WAVSoundBuffer.LoadFromFile(Filename);
}

Resource * WAVResourceMaker::Create( const std::string &Filename )
{
    return new WAVResource(Filename);
}

void WAVResource::Dump(std::ostream & o) const
{
    o << "Resource address: " << this << "\n";
    o << "Resource type: " << GetType() << "\n";
    o << "Name: " << m_name << "\n";
}
