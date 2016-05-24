#ifndef AUTHORS_H
#define AUTHORS_H

#include <Wt/Dbo/Dbo>
#include <string>
#include <Wt/WDateTime>
#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>
class Authors;
#include "allbooks.h"
using namespace Wt;

class Authors{
	public:
	int authorid;
	std::string name;
	int years;
	Dbo::collection< Dbo::ptr<AllBooks> > books;
	
	template<class Action>
	void persist(Action& a)
	  {
		Dbo::field(a, authorid,  "id");
		Dbo::field(a, name, 	"Name");
		Dbo::field(a, years,    "Years of life");
		Dbo::hasMany(a, books, Dbo::ManyToOne, "Authors");
	  }
};

#endif