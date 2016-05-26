#include "bookmanager.h"

BookManager::BookManager(){
	
}

void BookManager::addBook(std::string title, std::string author, std::string genre, int year, 
						  std::string seria, int numInSeria, int mark){
		Dbo::backend::Sqlite3 database(WApplication::instance()->docRoot() + "/db/bookrate.db");
		Dbo::Session session;
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
		Dbo::Transaction addBookInDb(session);
		Book *book = new Book();
		book->title=title;
		book->mark=mark;
		book->year=year;
		book->numInSeria=numInSeria;
		book->description="!";
		
		Author *author1 = new Author();
		author1->name = "example-author";
		author1->years = "example-date";
	
		Genre *genre1 = new Genre();
		genre1->genre = "example-genre";
			
		Seria *seria1 = new Seria();
		seria1->seria = "example-seria";
		seria1->numOfBooks = 33;
	
		Dbo::ptr <Book> newBook=session.add(book);
		newBook.modify()->author= author1;
		addBookInDb.commit();
}

void BookManager::addAuthor(std::string name, std::string years){
		Dbo::backend::Sqlite3 database(WApplication::instance()->docRoot() + "/db/bookrate.db");
		Dbo::Session session;
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
		Dbo::Transaction addAuthorInDb(session);
		Author *addAuthor = new Author();
		addAuthor->name=name;
		addAuthor->years=years;
		Dbo::ptr <Author> newAuthor=session.add(addAuthor);
		addAuthorInDb.commit();
}

BookManager::~BookManager(){	
}