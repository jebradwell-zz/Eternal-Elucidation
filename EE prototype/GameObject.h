#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#define CLASS_TYPE(classname) \
	public: \
	void Update(); \
	virtual const char * GetObjectType() { return GetClassType(); } \
	static const char * GetClassType() { return #classname; };

#define DEFAULT_SERIALIZATION \
	bool Load( const char *Filename ){return true;} \
	bool Save( const char *Filename ){return true;} \
	bool Save(){return true;};

#include "SFML/Graphics.hpp"
#include <vector>

class GameObject
{
public:
	std::vector<sf::Shape> CollisionBounds;
	sf::Vector2<int> Position;
	virtual ~GameObject(){};
	virtual void Update() = 0;
	virtual const char * GetObjectType() = 0;
	virtual bool Load( const char *Filename ) = 0;
	virtual bool Save( const char *Filename ) = 0;
	virtual bool Save() = 0;	
};

#endif