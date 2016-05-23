#include "basepage.h"

BasePage::BasePage(WContainerWidget* container){
	_container=container;
	_header=new WContainerWidget(container);
	_sidebar= new WContainerWidget(container);
	_pagecontent= new WContainerWidget(container);
	_pagecontent->setId("pagecontent");
}

void BasePage::printHeader(){
	_header->clear();
	_header->addWidget(new WText("<h1> RateBook </h1>")); 
	_header->setId("header");
	
}

void BasePage::sidebar() {
    _sidebar->clear();
    _sidebar->setId("sidebar");
    _sidebar->addWidget(new WText("Sidebar Menu"));
	WText *list;
	list=new WText(
				 "<ul>" 
					"<li> <a href='#/authors'> authors </a> </li>"
					"<li> <a href='#'> types of books </a> </li>" 
					"<li> <a href='#/'> rates </a> </li>" 
				"</ul>");
	list->setInternalPathEncoding(true);
	_sidebar->addWidget(list);
}

void BasePage::clearContent(){
 	_pagecontent->clear();
}

void BasePage::setContentText(std::string str){
	_pagecontent->addWidget(new WText(str));
}

void BasePage::printTop10( const Dbo::collection<Dbo::ptr<AllBooks> >& top10){
	//setContentText("top10");
	// # creating table
	Wt::WTable *table = new Wt::WTable();
	table->setHeaderCount(1);
	table->setWidth(Wt::WLength("70%"));
	table->elementAt(0, 0)->addWidget(new Wt::WText("#"));
	table->elementAt(0, 1)->addWidget(new Wt::WText("Title of book"));
	table->elementAt(0, 2)->addWidget(new Wt::WText("Author"));
	table->elementAt(0, 3)->addWidget(new Wt::WText("Mark"));
	_pagecontent->addWidget(table);
	int row=1;
		for (Dbo::collection<Dbo::ptr<AllBooks> >::const_iterator i = top10.begin(); i != top10.end(); ++i){
			Dbo::ptr<AllBooks> Book = *i;
			table->elementAt(row, 0)
			->addWidget(new Wt::WText(Wt::WString::fromUTF8("{1}")
					  .arg(row)));
			table->elementAt(row, 1)
			->addWidget(new Wt::WText(WString::fromUTF8(Book.get()->title)));
			//Wt::log("info") << "!!!"<< Book.get()->title;
			_pagecontent->addWidget(table);	
			row++;
		}
}