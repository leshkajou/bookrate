#include "app.h"
#include "basepage.h"
#include <Wt/WTemplate>
#include <iostream>
#include <Wt/WLineEdit>
#include <Wt/WTemplate>
#include "tables.h"
#include <Wt/WContainerWidget>
#include <Wt/WString>

using namespace Wt;

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
		/*session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");*/
        internalPathChanged().connect(this, &App::onInternalPathChange);
        rates();
}

WContainerWidget* App::content() {
	if (_content == 0) {
		_content = new WContainerWidget(root());
		_content->setId("content");
	}
	return _content;	
}

App::~App(){
	delete page;	
}


void App::rates() {
		Dbo::Session session;
		session.setConnection(database);
		session.mapClass<Book>("Book");
		session.mapClass<Author>("Author");
		session.mapClass<Genre>("Genre");
		session.mapClass<Seria>("Seria");
		//session.createTables();
		Dbo::Transaction rate(session);
		Dbo::collection<Dbo::ptr<Book> > top10 = session.find<Book>().orderBy("mark DESC").limit(10);
        page->printTop10(top10);
		rate.commit();	
}

void App::authors(){
        //page->setContentText("authors are:");
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

void App::addNewBook(){
	page->setContentText("Add new book:");
	page->addBook();
}

void App::addYourMark(){
	page->setContentText("authors are:");
	/*Dbo::Session session;
	session.setConnection(database);
	session.mapClass<Book>("Book");
	session.mapClass<Author>("Author");
	session.mapClass<Genre>("Genre");
	session.mapClass<Seria>("Seria");*/
	//session.createTables();
	/*Dbo::Transaction addmark(session);
	Dbo::collection<Dbo::ptr<Book> > listaddmark = session.find<Book>();
	page->addMark(listaddmark);
	addmark.commit();*/	
}

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
    }