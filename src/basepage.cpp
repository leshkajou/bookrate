#include "basepage.h"
#include <Wt/WApplication>


BasePage::BasePage(WContainerWidget* container){
	_container=container;
	_header=new WContainerWidget(container);
	_sidebar= new WContainerWidget(container);
	_pagecontent= new WContainerWidget(container);
	_pagecontent->setId("pagecontent");
}

void BasePage::printHeader(){
	_header->clear();
	_header->addWidget(new WText("<h1> <p align='center'>RateBook</p></h1>")); 
	_header->setId("header");
	
}

void BasePage::sidebar() {
    _sidebar->clear();
    _sidebar->setId("sidebar");
   //_sidebar->addWidget(new WText("Sidebar Menu"));
	WText *list;
	list=new WText(
				 "<ul class='menu'>" 
					"<li> <a href='#/'> rates </a> </li>"
					"<li> <a href='#/authors'> authors </a> </li>"
					"<li> <a href='#'> genres </a> </li>" 
					"<li> <a href='#/'> series and cycles </a> </li>" 
					"<li> <a href='#/'> add new book </a> </li>"
					"<li> <a href='#/'> add new author </a> </li>"
				"</ul>"
				"<div class=\"footer\">"
					"<p> copyright by Alexey 2016 </p>"
					"<p> <a href='#/'> docs </a> |<a href='http://vk.com/id156854642'> myVk </a> </p>"
				"</div>"
	);

				
	list->setInternalPathEncoding(true);
	_sidebar->addWidget(list);
}

void BasePage::footer() {
	_footer->clear();
    _footer->setId("footer");
	_footer->addWidget(new WText("Footer"));
}

void BasePage::clearContent(){
 	_pagecontent->clear();
}

void BasePage::setContentText(std::string str){
	_pagecontent->addWidget(new WText(str));
}

void BasePage::printTop10( const Dbo::collection<Dbo::ptr<Book> >& top10){
	//setContentText("top10");
	// # creating table
	WTable *table = new WTable();
	table->setStyleClass("tablestyle");
	table->setHeaderCount(1);
	table->setStyleClass("tablestyle");
	table->elementAt(0, 0)->addWidget(new WText("<p align='left'> # </p>"));
	table->elementAt(0, 1)->addWidget(new WText("<p align='left'> Title of book </p>"));
	table->elementAt(0, 2)->addWidget(new WText("<p align='left'> Author </p>"));
	table->elementAt(0, 3)->addWidget(new WText("<p align='left'> Genre </p>"));
	table->elementAt(0, 4)->addWidget(new WText("<p align='left'> Mark </p>"));
	_pagecontent->addWidget(table);
	int row=1;
		for (Dbo::collection<Dbo::ptr<Book> >::const_iterator i = top10.begin(); i != top10.end(); ++i){
			Dbo::ptr<Book> Book = *i;
			table->setStyleClass("tablestyle th,td,tr");
			//headers
			table->elementAt(row, 0)
			->addWidget(new WText(WString::fromUTF8("{1}")
					  .arg(row)));
			//titles
			table->elementAt(row, 1)
			->addWidget(new WText(WString::fromUTF8(Book.get()->title)));
			//authors
			table->elementAt(row, 2)
			->addWidget(new WText(WString::fromUTF8("{1}")
				      .arg((Book.get()->author.get()->name))));
			//genres
			table->elementAt(row, 3)
			->addWidget(new WText(WString::fromUTF8("{1}")
				      .arg((Book.get()->genre.get()->genre))));
			//marks
			table->elementAt(row, 4)
			->addWidget(new WText(WString::fromUTF8("{1}")
				      .arg((Book.get()->mark))));
			_pagecontent->addWidget(table);	
			row++;
		}
}