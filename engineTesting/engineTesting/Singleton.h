#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

template <class T>
class Singleton
{
public:
	static T *getInstance();
	static void Destroy();	
	~Singleton<T>();
private:
	Singleton<T>();

	static T *single;
};

template<class T>
Singleton<T>::Singleton()
{
}

template<class T>
Singleton<T>::~Singleton()
{
}

template <class T>
T *Singleton<T>::getInstance()
{
	if(!single)
		single = new T();	
	return single;
}

template <class T>
void Singleton<T>::Destroy()
{
	if (single == NULL)
		return;
	delete single;
	single = 0;
}

template <class T> T *Singleton<T>::single;


#endif //SINGLETON_H





//template<class T>
//class Singleton
//{
//private:
//    class InstPtr
//    {
//    public:
//        InstPtr() : m_ptr(0) {}
//        ~InstPtr() { delete m_ptr; }
//        T* Get() { return m_ptr; }
//        void Set(T* p)
//        {
//            if(p!= 0)
//            {
//                delete m_ptr;
//                m_ptr = p;
//            }
//        }
//    private:
//        T* m_ptr;
//    };
//
//    static InstPtr sm_ptr;
//    Singleton();
//	~Singleton();
//    Singleton(const Singleton&);
//    Singleton& operator=(const Singleton&);
//
//public:
//    static T* getInstance()
//    {
//        if(sm_ptr.Get() == 0)
//        {
//            sm_ptr.Set(new T());
//        }
//        return sm_ptr.Get();
//    }
//};

//#include <assert.h>
//
//template <class T>
//class Singleton
//{
//public:
//	static T* getInstance() {
//		if(!m_pInstance) m_pInstance = new T;
//		assert(m_pInstance !=NULL);
//		return m_pInstance;
//	}
//protected:
//	Singleton();
//	~Singleton();
//private:
//	Singleton(Singleton const&);
//	Singleton& operator=(Singleton const&);
//	static T* m_pInstance;
//};
//
//template <class T> T* Singleton<T>::m_pInstance=NULL;