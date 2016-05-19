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
	setContentText("top10");
	for (Dbo::collection<Dbo::ptr<AllBooks> >::const_iterator i = top10.begin(); i != top10.end(); ++i){
		Dbo::ptr<AllBooks> Book = *i;
		_pagecontent->addWidget(new WText(WString::fromUTF8(Book.get()->title)));
	}
}