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

class BookManager{
	public:
	BookManager();
	void addBook(std::string title, std::string author, std::string genre,
				 int year, std::string seria, int numInseria, int mark);
	void addAuthor(std::string name, std::string years);
	~BookManager();
};

#endif