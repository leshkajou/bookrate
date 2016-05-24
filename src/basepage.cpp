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
					"<li> <a href='#/'> rate </a> </li>"
					"<li> <a href='#/authors'> authors </a> </li>"
					"<li> <a href='#/genres'> genres </a> </li>" 
					"<li> <a href='#/series'> series and cycles </a> </li>" 
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
			->addWidget(new WText(WString::fromUTF8("{1}")
				      .arg(Book.get()->title)));
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

void BasePage::printAuthors(const Dbo::collection<Dbo::ptr<Author> >& listauthors){
	WTable *authTable = new WTable();
	authTable->setHeaderCount(1);
	authTable->setStyleClass("tablestyle");
	authTable->elementAt(0, 0)->addWidget(new WText("<p align='left'> # </p>"));
	authTable->elementAt(0, 1)->addWidget(new WText("<p align='left'> Full name or pseudo </p>"));
	authTable->elementAt(0, 2)->addWidget(new WText("<p align='left'> Years of life </p>"));
	_pagecontent->addWidget(authTable);
	int row=1;
	for (Dbo::collection<Dbo::ptr<Author> >::const_iterator i = listauthors.begin(); i != listauthors.end(); ++i){
			Dbo::ptr<Author> Author = *i;
			authTable->setStyleClass("tablestyle th,td,tr");
			//headers
			authTable->elementAt(row, 0)
			->addWidget(new WText(WString::fromUTF8("{1}")
					  .arg(row)));
			//name
			authTable->elementAt(row, 1)
			->addWidget(new WText(WString::fromUTF8(Author.get()->name)));
			//authors
			authTable->elementAt(row, 2)
			->addWidget(new WText(WString::fromUTF8("{1}")
				      .arg((Author.get()->years))));
			_pagecontent->addWidget(authTable);	
			row++;
	}
}

void BasePage::printGenres(const Dbo::collection<Dbo::ptr<Genre> >& listgenres){
	WTable *genreTable = new WTable();
	genreTable->setHeaderCount(1);
	genreTable->setStyleClass("tablestyle");
	genreTable->elementAt(0, 0)->addWidget(new WText("<p align='left'> # </p>"));
	genreTable->elementAt(0, 1)->addWidget(new WText("<p align='left'> Types og genres </p>"));
	_pagecontent->addWidget(genreTable);
	int row=1;
	for (Dbo::collection<Dbo::ptr<Genre> >::const_iterator i = listgenres.begin(); i != listgenres.end(); ++i){
			Dbo::ptr<Genre> Genre = *i;
			genreTable->setStyleClass("tablestyle th,td,tr");
			//headers
			genreTable->elementAt(row, 0)
			->addWidget(new WText(WString::fromUTF8("{1}")
					  .arg(row)));
			//genre
			genreTable->elementAt(row, 1)
			->addWidget(new WText(WString::fromUTF8(Genre.get()->genre)));
			_pagecontent->addWidget(genreTable);	
			row++;
	}
}

void BasePage::printSeries(const Dbo::collection<Dbo::ptr<Seria> >& listseries){
	WTable *seriaTable = new WTable();
	seriaTable->setHeaderCount(1);
	seriaTable->setStyleClass("tablestyle");
	seriaTable->elementAt(0, 0)->addWidget(new WText("<p align='left'> # </p>"));
	seriaTable->elementAt(0, 1)->addWidget(new WText("<p align='left'> Name of seria </p>"));
	seriaTable->elementAt(0, 2)->addWidget(new WText("<p align='left'> Number of books </p>"));
	_pagecontent->addWidget(seriaTable);
	int row=1;
	for (Dbo::collection<Dbo::ptr<Seria> >::const_iterator i = listseries.begin(); i != listseries.end(); ++i){
			Dbo::ptr<Seria> Seria = *i;
			seriaTable->setStyleClass("tablestyle th,td,tr");
			//headers
			seriaTable->elementAt(row, 0)
			->addWidget(new WText(WString::fromUTF8("{1}")
					  .arg(row)));
			//genre
			seriaTable->elementAt(row, 1)
			->addWidget(new WText(WString::fromUTF8(Seria.get()->seria)));
			//num of books in seria
			seriaTable->elementAt(row, 2)
			->addWidget(new WText(WString::fromUTF8("{1}")
				      .arg((Seria.get()->numOfBooks))));
			_pagecontent->addWidget(seriaTable);	
			row++;
	}
}