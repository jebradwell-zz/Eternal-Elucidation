///////////////////////////////////////////////////////////////////////////////
// COPYRIGHT © 2009 Jeb Bradwell, Adam Zech & Ron Moore
// This file is distributed under the terms of the GNU General Public License
///////////////////////////////////////////////////////////////////////////////
/// @file ResourceMaker.h
///
/// @brief
/// a helper class which creates the individual resources for the resouce manager
///
/// @remarks
///////////////////////////////////////////////////////////////////////////////
#ifndef RESOURCE_MAKER_H
#define RESOURCE_MAKER_H

#include "Resource.h"

class ResourceMaker
{
public:
	//virtual Resource * Create (FILE * fin) = 0;
	virtual Resource * Create (const std::string &Filename) = 0;
	virtual const char * GetExtension () = 0;
};

#endif //RESOURCE_MAKER_H