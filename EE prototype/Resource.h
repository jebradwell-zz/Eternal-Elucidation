///////////////////////////////////////////////////////////////////////////////
// COPYRIGHT © 2009 Jeb Bradwell, Adam Zech & Ron Moore
// This file is distributed under the terms of the GNU General Public License
///////////////////////////////////////////////////////////////////////////////
/// @file Resource.h
///
/// @brief
/// Holds the code for the resource class
///
/// @remarks
/// This class is inherited publicly by all the resource classes
/// used in the game engine.
///////////////////////////////////////////////////////////////////////////////

#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class ResourceManager;

///////////////////////////////////////////////////////////////////////////////
/// @class Resource
///
/// @brief
/// The Resource class is used by the resource manager class to keep track of 
/// already loaded resources.
///
/// @remarks
/// 
///////////////////////////////////////////////////////////////////////////////
class Resource {
public:
	typedef std::string Type;
	virtual void *GetResource() = 0;
	virtual const std::string & GetName() const = 0;
	virtual Type GetType() const = 0;
	virtual void Dump(std::ostream & o) const = 0;
protected:
	virtual ~Resource() {};

	friend class ResourceManager;    // The resource manager is the only place resources can be destroyed
};

std::ostream & operator<< (std::ostream & o, const Resource & res);

#endif //RESOURCE_H