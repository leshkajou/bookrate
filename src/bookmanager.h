#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <string>
#include <Wt/WApplication>
#include "tables.h"
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <vector>


using namespace Wt;
typedef Wt::Dbo::collection< Wt::Dbo::ptr<Book> > Books;
/**
	Class, which works with users input of book, author or mark
*/
class BookManager{
	Dbo::Session session;
	Dbo::backend::Sqlite3 database;
	public:
	BookManager();
	//Dbo::collection<Dbo::ptr<Book> > getTop10();  
	std::vector<Book> topBooks(int);
	void updateRate(int id, int mark);
	
	
	
	
	void addBook(std::string title, std::string author, std::string years, std::string genre,  
						  int year, std::string seria, int numOfBooks, int numInSeria, int mark);
	void addAuthor(std::string name, std::string years);
	void refreshRate(int id, int newMark, int numMark);
	~BookManager();
};

#endif