#include "pngResource.h"
#include <iostream>

PNGResource::PNGResource ( const std::string &Filename )
{
	this->m_name = Filename;
	this->LoadingError = this->PNGImage.LoadFromFile(Filename);
}

Resource * PNGResourceMaker::Create( const std::string &Filename )
{
    return new PNGResource(Filename);
}

void PNGResource::Dump(std::ostream & o) const
{
    o << "Resource address: " << this << "\n";
    o << "Resource type: " << GetType() << "\n";
    o << "Name: " << m_name << "\n";
}
