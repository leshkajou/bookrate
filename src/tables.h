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
class Book;

/**
	Class describing a author table in db
*/
class Author{
	public:
	std::string name;
	std::string years;
	//int id;
	Dbo::collection< Dbo::ptr<Book> > books;
	
	template<class Action>
	void persist(Action& a)
	  {
		//Dbo::field(a, id, "id");
		Dbo::field(a, name, 	"Name");
		Dbo::field(a, years,    "Years");
		Dbo::hasMany(a, books, Dbo::ManyToOne, "Author");
	  }
};

/**
	Class describing a genre table in db
*/
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

/**
	Class describing a book seria in db
*/
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
/**
	Class describing a book table in db
*/
class Book{
	public:
	std::string title;
	int mark;
	int year;
	int numInSeria;
	int id;
	int numMarks;
	std::string description;
	
	Dbo::ptr<Author> author;
	Dbo::ptr<Genre> genre;
	Dbo::ptr<Seria> seria;
	Author author_;
	Genre genre_;
	Seria seria_;
	
	template<class Action>
  	void persist(Action& a)
	  {
		Dbo::field(a, id, 	"id");
		Dbo::field(a, title, 	"Title");
		Dbo::field(a, mark,     "Mark");
		Dbo::field(a, year,     "Year");
		Dbo::belongsTo(a, author, "Author");
		Dbo::field(a, numMarks, "NumMarks");
		Dbo::belongsTo(a, genre, "Genre");
		Dbo::belongsTo(a, seria, "Seria");
		Dbo::field(a, numInSeria, "NumInSeria");
		Dbo::field(a, description, "Description");
	  }
};



#endif