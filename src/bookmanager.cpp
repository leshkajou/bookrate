#include "bookmanager.h"

BookManager::BookManager():database(WApplication::instance()->docRoot() + "/db/bookrate.db"){
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
}



BookManager::~BookManager(){	
}



std::vector<Book> BookManager::topBooks(int lim){
	Dbo::Transaction transaction(session);
	
	Books top = session.find<Book>().orderBy("Mark/NumMarks desc").limit(lim);

	std::vector<Book> result;
	for (Books::const_iterator i = top.begin(); i != top.end(); ++i) {
		Dbo::ptr<Book> book = *i;
		result.push_back(*book);
		result.back().author_= *(book.get()->author);
		result.back().genre_= *(book.get()->genre);
		result.back().seria_= *(book.get()->seria);
	}

	transaction.commit();

	return result;
}



void BookManager::updateRate(std::string title, int plusmark){
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open((WApplication::instance()->docRoot() + "/db/bookrate.db").c_str(), &db);
	if( rc ){
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  exit(0);
	}else{
	  fprintf(stderr, "Opened database successfully\n");
	}
	std::string sqlQuery;
	sqlQuery="UPDATE Book SET NumMarks=NumMarks+1, Mark= Mark+"; 
	sqlQuery+=std::to_string(plusmark)+" WHERE Title="+title;
		
	rc = sqlite3_exec(db, sqlQuery.c_str(), NULL, NULL, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}else{
	  fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	
}


/**
	adding new book
*/
void BookManager::addBook(std::string title, std::string author, std::string years, std::string genre,  
						  int year, std::string seria, int numOfBooks, int numInSeria, int mark){
		
		Dbo::backend::Sqlite3 database(WApplication::instance()->docRoot() + "/db/bookrate.db");
		Dbo::Session session;
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
		
		//adding author from other table in db using foreign key
		Author *author1 = new Author();
		author1->name = author;
		author1->years = years;
		Dbo::Transaction addAuth(session);
		Dbo::ptr <Author> newAuthor=session.add(author1);
		addAuth.commit();
		
		//adding genre from other table in db using foreign key
		Genre *genre1 = new Genre();
		genre1->genre = genre;
		Dbo::Transaction addGenre(session);
		Dbo::ptr <Genre> newGenre=session.add(genre1);
		addGenre.commit();
		
		//adding seria from other table in db using foreign key
		Seria *seria1 = new Seria();
		seria1->seria = seria;
		seria1->numOfBooks = numOfBooks;
		Dbo::Transaction addSeria(session);
		Dbo::ptr <Seria> newSeria=session.add(seria1);
		addSeria.commit();
		
		//adding changes in book table
		Dbo::Transaction addBookInDb(session);
		Book *book = new Book();
		book->title=title;
		book->mark=mark;
		book->year=year;
		book->numInSeria=numInSeria;
		book->description="!";
		book->numMarks=1;
		//book->author.id();
		Dbo::ptr <Book> newBook=session.add(book);
		
		//adding changes from other tables
		newBook.modify()->author = newAuthor;
		newBook.modify()->genre= newGenre;
		newBook.modify()->seria = newSeria;
		addBookInDb.commit();
}

/**
	adding new author
*/
void BookManager::addAuthor(std::string name, std::string years){
		//mapping and setting session with db
		Dbo::backend::Sqlite3 database(WApplication::instance()->docRoot() + "/db/bookrate.db");
		Dbo::Session session;
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
		Dbo::Transaction addAuthorInDb(session);
		Author *addAuthor = new Author();
		//adding changes in author table
		addAuthor->name=name;
		addAuthor->years=years;
		Dbo::ptr <Author> newAuthor=session.add(addAuthor);
		addAuthorInDb.commit();
}

void BookManager::refreshRate(int id, int newMark, int numMark){
		//mapping and setting session with db
		Dbo::backend::Sqlite3 database(WApplication::instance()->docRoot() + "/db/bookrate.db");
		Dbo::Session session1;
		session1.setConnection(database);
		session1.mapClass<Book>("Book");
		session1.mapClass<Author>("Author");
		session1.mapClass<Genre>("Genre");
		session1.mapClass<Seria>("Seria");
		Dbo::Transaction refr(session1);
		Dbo::ptr<Book> refr1 = session1.find<Book>().where("id = ?").bind(id);
		//adding changes of mark
		refr1.modify()->numMarks += numMark;
		refr1.modify()->mark += newMark;
		refr.commit();
		std::cout<<refr1.get()->id<<std::endl;
}

