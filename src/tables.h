#ifndef TABLES_H
#define TABLES_H

#include <Wt/Dbo/Dbo>
#include <string>
#include <Wt/WDateTime>
#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>

using namespace Wt;
class Author;
class Genre;
class Seria;

class Book{
	public:
	std::string title;
	int mark;
	int year;
	int numInSeria;
	std::string description;
	
	Dbo::ptr<Author> author;
	Dbo::ptr<Genre> genre;
	Dbo::ptr<Seria> seria;
	
	template<class Action>
  	void persist(Action& a)
	  {
		Dbo::field(a, title, 	"Title");
		Dbo::field(a, mark,     "Mark");
		Dbo::field(a, year,     "Year");
		Dbo::belongsTo(a, author, "Author");
		Dbo::belongsTo(a, genre, "Genre");
		Dbo::belongsTo(a, seria, "Seria");
		Dbo::field(a, numInSeria, "NumInSeria");
		Dbo::field(a, description, "Description");
	  }
};

class Author{
	public:
	std::string name;
	int years;
	Dbo::collection< Dbo::ptr<Book> > books;
	
	template<class Action>
	void persist(Action& a)
	  {
		Dbo::field(a, name, 	"Name");
		Dbo::field(a, years,    "Years");
		Dbo::hasMany(a, books, Dbo::ManyToOne, "Author");
	  }
};

class Genre{
	public:
	std::string genre;
	Dbo::collection< Dbo::ptr<Book> > genres;
	
	template<class Action>
	void persist(Action& a)
	  {
		Dbo::field(a, genre, 	"Genre");
		Dbo::hasMany(a, genres, Dbo::ManyToOne, "Genre");
	  }
};

class Seria{
	public:
	std::string seria;
	int numOfBooks;
	Dbo::collection< Dbo::ptr<Book> > series;
	
	template<class Action>
	void persist(Action& a)
	  {
		Dbo::field(a, seria, 	"Seria");
		Dbo::field(a, numOfBooks, 	"NumOfBooks");
		Dbo::hasMany(a, series, Dbo::ManyToOne, "Seria");
	  }
};

#endif