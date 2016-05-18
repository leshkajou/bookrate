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

using namespace Wt;

class BasePage
{
	WContainerWidget* _container;
	WContainerWidget* _header;
	WContainerWidget* _footer;
	WContainerWidget* _sidebar;
public:
	BasePage(WContainerWidget*);
	void printHeader();
};

#endif