#ifndef APP_H
#define APP_H
#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WLink>
#include <Wt/WText>
#include "basepage.h"
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>

using namespace Wt;
/**
	Class, which creates base page and
	then creates variable part of application, according to user's actions
*/
class App: public WApplication {
private:
    std::string appName;
    WContainerWidget* _content;
	BasePage *page;
	void authors();
	void genres();
	void rates();
	void series();
	void addNewBook();
	void addYourMark();
	void seriesAndCycles();
	void addNewAuthor();
	void printDocs();
	//Dbo::Session session;
	//Dbo::backend::Sqlite3 database;
public:
    App(const WEnvironment &env);
	WContainerWidget* content();
	~App();
	//Dbo::Session getSession();
protected:
	virtual void onInternalPathChange();
};

#endif