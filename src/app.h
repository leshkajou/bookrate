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
	void aaNewAuthor();
	void seriesAndCycles();
	void addNewAuthor();
	Dbo::backend::Sqlite3 database;
//	Dbo::Session session;
public:
    App(const WEnvironment &env);
	WContainerWidget* content();
	~App();
	//Dbo::Session getSession();
protected:
	virtual void onInternalPathChange();
};

#endif