#include "app.h"
#include "basepage.h"
#include <Wt/WTemplate>
#include <iostream>
#include "tables.h"

using namespace Wt;

App::App(const WEnvironment &env): WApplication(env), database(WApplication::instance()->docRoot() + "/db/bookrate.db") {
		std::cout<<"docroot = "<<WApplication::instance()->docRoot()<<std::endl;
		std::cout<<"uproot = " <<WApplication::instance()->appRoot()<<std::endl;
        appName = "RateYourBook";
        setTitle(appName);
        _content = 0;
        page = new BasePage(content());
        page->printHeader();
        page->sidebar();
		//page->footer();
        useStyleSheet("templates/style.css");
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

void App::onInternalPathChange() {
        std::cout<<"internal path changed "<<internalPath()<<std::endl;
        page->clearContent();
        if (internalPath() == "/") {
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
    }