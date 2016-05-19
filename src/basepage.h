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
#include "allbooks.h"
#include <Wt/Dbo/Dbo>

using namespace Wt;

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
	void printTop10( const Dbo::collection<Dbo::ptr<AllBooks> >& top10);
	void printTable();
	void setContentText(std::string);
	void clearContent();
};

#endif