#include "bookmanager.h"

BookManager::BookManager(){
	
}

void BookManager::addBook(std::string title,  int year, int numInSeria, int mark){
		Dbo::backend::Sqlite3 database(WApplication::instance()->docRoot() + "/db/bookrate.db");
		Dbo::Session session;
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
		
		
		Author *author1 = new Author();
		author1->name = "example-author";
		author1->years = "example-date";
		Dbo::Transaction addAuth(session);
		Dbo::ptr <Author> newAuthor=session.add(author1);
		addAuth.commit();
	
		Genre *genre1 = new Genre();
		genre1->genre = "example-genre";
		Dbo::Transaction addGenre(session);
		Dbo::ptr <Genre> newGenre=session.add(genre1);
		addGenre.commit();
	
		Seria *seria1 = new Seria();
		seria1->seria = "example-seria";
		seria1->numOfBooks = 33;
		Dbo::Transaction addSeria(session);
		Dbo::ptr <Seria> newSeria=session.add(seria1);
		addSeria.commit();
		//int a = session.query<int>("select id from Author").where("name = example-author");
		//book->year=a;
		//Dbo::collection<Dbo::ptr<Book> >  = session.find<Book>().orderBy("mark DESC").limit(10);
		//Dbo::collection<= session.find<Author>().where("name = ?");
		Dbo::Transaction addBookInDb(session);
		Book *book = new Book();
		book->title=title;
		book->mark=mark;
		book->year=year;
		book->numInSeria=numInSeria;
		book->description="!";
		//book->author.id();
		Dbo::ptr <Book> newBook=session.add(book);
		
		newBook.modify()->author = newAuthor;
		newBook.modify()->genre= newGenre;
		newBook.modify()->seria = newSeria;
		addBookInDb.commit();
		//addBookInDb.commit();
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