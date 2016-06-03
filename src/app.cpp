#include "app.h"
#include "basepage.h"
#include <Wt/WTemplate>
#include <iostream>
#include <Wt/WLineEdit>
#include <Wt/WTemplate>
#include "tables.h"
#include <Wt/WContainerWidget>
#include <Wt/WString>
#include "bookmanager.h"

using namespace Wt;
/**
Builder of App class;
It includes:
	-creating an object, which returns the current application instance
	-including xml- and css-files
	-setting the browser window title and internal path
	-printing of design methods of web-site
*/
App::App(const WEnvironment &env): WApplication(env), database(WApplication::instance()->docRoot() + "/db/bookrate.db") {
		Wt::WApplication *app = Wt::WApplication::instance();
		app->messageResourceBundle().use("general");
        appName = "RateYourBook";
        setTitle(appName);
        _content = 0;
        page = new BasePage(content());
        page->printHeader();
        page->sidebar();
        useStyleSheet("templates/style.css");
        internalPathChanged().connect(this, &App::onInternalPathChange);
        rates();
}

/**
	Creating of content container
*/
WContainerWidget* App::content() {
	if (_content == 0) {
		_content = new WContainerWidget(root());
		_content->setId("content");
	}
	return _content;	
}

/**
	Destructor
*/
App::~App(){
	delete page;	
}

/**
	Printing the rate page:
		-Creating session with database and mapping classes
		-Creating transaction->creating sql query of top 10 books rate->
		->printing the result using printTop10 method->committing changes
*/
void App::rates() {
		BookManager bm;
		page->printTop(bm.topBooks(10));
}
/**
	Printing the author's page:
		-Creating session with database and mapping classes
		-Creating transaction->creating sql query of author's list->
		->printing the result using printAuthors method->committing changes
*/
void App::authors(){
		Dbo::Session session;
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
		Dbo::Transaction authors(session);
		Dbo::collection<Dbo::ptr<Author> > listauthors = session.find<Author>().orderBy("name");
		page->printAuthors(listauthors);
		authors.commit();
		
}

/**
	printing lists of genres
*/
void App::genres(){
	Dbo::Session session;
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
		Dbo::Transaction genres(session);
		Dbo::collection<Dbo::ptr<Genre> > listgenres = session.find<Genre>().orderBy("genre");
		page->printGenres(listgenres);
		genres.commit();
}

/**
	printing lists of series
*/
void App::series(){
	Dbo::Session session;
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
		Dbo::Transaction series(session);
		Dbo::collection<Dbo::ptr<Seria> > listseries = session.find<Seria>().where("id > 1");
		page->printSeries(listseries);
		series.commit();
}

/**
	printing data in "add new book" page using
	addNewBook1 method
*/
void App::addNewBook(){
	page->addNewBook1();
}

/**
	printing data in "add your mark" page using
	addMark method
*/
void App::addYourMark(){
	//page->setContentText("Add your mark:");
	std::vector<Book> books;
	{
		BookManager bm;
		books=bm.topBooks(30);
	}
	page->addYourMark(books);
}

void App::printDocs(){
	page->setContentText("Test:");
}

/**
	function of choosing of methods of App class,
	according to internal path
*/
void App::onInternalPathChange() {
        std::cout<<"internal path changed "<<internalPath()<<std::endl;
        page->clearContent();
        if (internalPath() == "/rate") {
            rates();
        }
// elseif..
        else if (internalPath() == "/authors") {
            authors();
        }
		else if (internalPath() == "/genres") {
            genres();
        }
		else if (internalPath() == "/series") {
            series();
        }
		else if (internalPath() == "/newbook") {
            addNewBook();
        }
		else if (internalPath() == "/addmark") {
            addYourMark();
        }
		else if (internalPath() == "/docs") {
            printDocs();
        }
    }