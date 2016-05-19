#ifndef ALLBOOKS_H
#define ALLBOOKS_H

#include <Wt/Dbo/Dbo>
#include <string>
#include <Wt/WDateTime>
#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>

using namespace Wt;

class AllBooks{
	public:
	int bookid;
	std::string title;
	int mark;
	template<class Action>
  	void persist(Action& a)
	  {
		Dbo::field(a, bookid,   "bookid");
		Dbo::field(a, title, 	"Title");
		Dbo::field(a, mark,     "Mark");
	  }
};
DBO_EXTERN_TEMPLATES(AllBooks);
#endif