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
		Dbo::Transaction t(session);
		Dbo::collection<Dbo::ptr<Book> > top10 = session.find<Book>().orderBy("mark DESC").limit(10);
        page->printTop10(top10);
		t.commit();	
}

void App::authors(){
        page->setContentText("authors are:");
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
    }