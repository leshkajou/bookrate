#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WLink>
#include <Wt/WText>
#include <Wt/WImage>
#include <Wt/WHBoxLayout>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>
#include <Wt/WBreak>
#include <Wt/WMenu>
#include <Wt/WStackedWidget>
#include <Wt/WTextArea>
#include <Wt/WGroupBox>
#include <Wt/WText>
#include <Wt/WVBoxLayout>
#include <string>
#include "tables.h"
#include <Wt/Dbo/Dbo>
#include <Wt/WLineEdit>
#include <Wt/WTemplate>

using namespace Wt;

/**
	Class, which generates containers of content, creates design of web-site and
	also creates methods of adding widgets and output db information
*/
class BasePage
{
	WContainerWidget* _container;
	WContainerWidget* _header;
	WContainerWidget* _footer;
	WContainerWidget* _sidebar;
	WContainerWidget* _pagecontent;
public:
	BasePage(WContainerWidget*);
	void printHeader();
	void sidebar();
	void footer();
	void printTop10(const Dbo::collection<Dbo::ptr<Book> >& top10);
	void printAuthors(const Dbo::collection<Dbo::ptr<Author> >& listauthors);
	void printGenres(const Dbo::collection<Dbo::ptr<Genre> >& listgenres);
	void printSeries(const Dbo::collection<Dbo::ptr<Seria> >& listseries);
	void setContentText(std::string);
	void addNewBook1();
	void addAuthor();
	void clearContent();
	void addMark(const Dbo::collection<Dbo::ptr<Book> >& listaddmark);
	static int intoInt(WLineEdit *ptr);
	
	void printTop(const std::vector<Book>&);
	void addYourMark(const std::vector<Book>&);
};

#endif