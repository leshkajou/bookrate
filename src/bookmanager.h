#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <string>
#include <Wt/WApplication>
#include "tables.h"
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/WLineEdit>
#include <Wt/WTemplate>
#include "tables.h"

using namespace Wt;

/*
	Class, which works with users input of book, author or mark
*/
class BookManager{
	public:
	BookManager();
	void addBook(std::string title, std::string author, std::string years, std::string genre,  
						  int year, std::string seria, int numOfBooks, int numInSeria, int mark);
	void addAuthor(std::string name, std::string years);
	void refreshRate(int id, int newMark, int numMark, Dbo::Session &session);
	~BookManager();
};

#endif