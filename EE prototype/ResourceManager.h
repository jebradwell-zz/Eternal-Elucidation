///////////////////////////////////////////////////////////////////////////////
// COPYRIGHT © 2009 Jeb Bradwell, Adam Zech & Ron Moore
// This file is distributed under the terms of the GNU General Public License
///////////////////////////////////////////////////////////////////////////////
/// @file ResourceManager.h
///
/// @brief
/// Manager class for all loaded resouces of the game engine.
///
/// @remarks
/// More detailed description of this file
/// that could span many sentences. This would be another sentence.
///////////////////////////////////////////////////////////////////////////////
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <map>

#include "ResourceMaker.h"
#include "Resource.h"

#include "Singleton.h"


class ResourceManager {
public:
	~ResourceManager();

	void Register (ResourceMaker * pMaker);
	void Unregister (const std::string & objectType);

	Resource * Create(const std::string & filename);

private:
	Resource * LoadResource(const std::string & filename);

	typedef std::map<std::string, ResourceMaker *> MakerMap;
	MakerMap m_makers;

	typedef std::map<std::string, Resource *> ResourceMap;
	ResourceMap m_resources;
};

typedef Singleton<ResourceManager> RM;

#endif //RESOURCE_MANAGER_H