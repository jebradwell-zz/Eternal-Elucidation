#include <assert.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
    ResourceMap::iterator it = m_resources.begin();
    while (it != m_resources.end()) 
    {
        Resource * pRes = (*it).second;
        delete pRes;
        ++it;
    }
}


void ResourceManager::Register(ResourceMaker * pMaker)
{
    assert (pMaker != NULL);
    m_makers[std::string(pMaker->GetExtension())] = pMaker;
}


Resource * ResourceManager::Create(const std::string & filename)
{
	boost::filesystem::path full_path (filename);
      
    ResourceMap::iterator it = m_resources.find(full_path.string());
    if (it != m_resources.end()) 
        return (*it).second;
        
    Resource * pRes = LoadResource(full_path.string());    
    if (pRes == NULL)
        return NULL;
    
    m_resources[full_path.string()] = pRes;     
    return pRes;
}


Resource * ResourceManager::LoadResource(const std::string & filename)
{
	boost::filesystem::path path (filename);
	std::string ext = boost::filesystem::extension(path);
    
    MakerMap::iterator it = m_makers.find(ext);
    if (it == m_makers.end())
        return NULL;

    ResourceMaker * pMaker = (*it).second;
    assert (pMaker != NULL);
    
    //FILE * fin = fopen(filename.c_str(), "rt");
    //if (fin == NULL)
    //    return NULL;        
    Resource * pRes = pMaker->Create(filename);
    //fclose(fin);
        
    return pRes;
}