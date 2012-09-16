#ifndef EXTENSIBLEFACTORY_H_
#define EXTENSIBLEFACTORY_H_


#include <string>
#include <map>
#include <assert.h>


template <class T>
class FactoryMakerBase
{
public:
    virtual T * Create() const = 0;    
    virtual const char * GetObjectType() const = 0;
};


template <class Type, class Base>
class FactoryMaker : public FactoryMakerBase<Base>
{
public:
	virtual Base * Create () const
	{
		return new Type;
	}
    virtual const char * GetObjectType() const
    {
        return Type::GetClassType();
    }
};



template <class T>
class ExtensibleFactory 
{
public:
    typedef FactoryMakerBase<T> FactoryType;
       
    T * Create (const std::string & objectType);
    void Register (FactoryType * pMaker);
    void Unregister (const std::string & objectType);
    
private:
    typedef std::map<std::string, FactoryType *> TypeMap;
    TypeMap m_makers;        
};


template <class T>
void ExtensibleFactory<T>::Register (FactoryType * pMaker)
{
    assert (pMaker != NULL);
    m_makers[std::string(pMaker->GetObjectType())] = pMaker;
}


template <class T>
void ExtensibleFactory<T>::Unregister (const std::string & objectType)
{
    typename TypeMap::iterator it = m_makers.find(objectType);
    if (it != m_makers.end()) 
    {
        FactoryType * pMaker = (*it).second;
        assert (pMaker != NULL);
        delete pMaker;
        m_makers.erase(it);
    }
}

template <class T>
T * ExtensibleFactory<T>::Create (const std::string & objectType)
{
    typename TypeMap::iterator it = m_makers.find(objectType);
    if (it == m_makers.end())
        return NULL;
    FactoryType * pMaker = (*it).second;
    return pMaker->Create();    
}

#endif