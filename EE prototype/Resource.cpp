#include "Resource.h"

std::ostream & operator<< (std::ostream & o, const Resource & res)
{
   res.Dump(o);
   return o;
}