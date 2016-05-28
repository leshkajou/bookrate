#include "basepage.h"
#include <Wt/WApplication>
#include <Wt/WIntValidator>
#include <Wt/Utils>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WTextEdit>
#include "bookmanager.h"


BasePage::BasePage(WContainerWidget* container){
	_container=container;
	_header=new WContainerWidget(container);
	_sidebar= new WContainerWidget(container);
	_pagecontent= new WContainerWidget(container);
	_pagecontent->setId("pagecontent");
}

void BasePage::printHeader(){
	_header->clear();
	_header->setStyleClass("color");
	_header->addWidget(new WText("<h1> <p align='center' >RateBook</p></h1>")); 
	_header->setId("header");
}

void BasePage::sidebar() {
    _sidebar->clear();
    _sidebar->setId("sidebar");
   //_sidebar->addWidget(new WText("Sidebar Menu"));
	WText *list;
	list=new WText(
				 "<ul class='menu'>" 
					"<li> <a href='#/rate'> rate </a> </li>"
					"<li> <a href='#/authors'> authors </a> </li>"
					"<li> <a href='#/genres'> genres </a> </li>" 
					"<li> <a href='#/series'> series and cycles </a> </li>" 
					"<li> <a href='#/newbook'> add new book </a> </li>"
					"<li> <a href='#/addmark'> add your mark </a> </li>"
				"</ul>"
				"<div class=\"footer\">"
					"<p> <font color='white'> copyright by Alexey 2016 </font> </p>"
					"<p>  <a href='#/'> docs </a> |<a href='http://vk.com/id156854642'> myVk </a> </p>"
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

int BasePage::intoInt(WLineEdit *ptr){
	std::string stringV=ptr->valueText().toUTF8();
	int intV = std::stoi(stringV);
	return intV;
}

void BasePage::addBook(){
	WContainerWidget *container = new WContainerWidget();
	Wt::WTemplate *t = new Wt::WTemplate(Wt::WString::tr("addBookForm"));
	
	WLineEdit *editTitle = new WLineEdit(container);
	editTitle->setPlaceholderText("title");
	t->bindWidget("title", editTitle);
	
	WLineEdit *editAuthor = new WLineEdit(container);
	editAuthor->setPlaceholderText("author");
	t->bindWidget("author", editAuthor);
	
	WLineEdit *editAuthorYears = new WLineEdit(container);
	editAuthorYears->setPlaceholderText("years of life");
	t->bindWidget("years", editAuthorYears);
	
	WLineEdit *editGenre = new WLineEdit(container);
	editGenre->setPlaceholderText("genre");
	t->bindWidget("genre", editGenre);
	
	WLineEdit *editYear = new WLineEdit(container);
	editYear->setPlaceholderText("year");
	t->bindWidget("year", editYear);
	
	WLineEdit *editSeria = new WLineEdit(container);
	editSeria->setPlaceholderText("seria");
	t->bindWidget("seria", editSeria);
	
	WLineEdit *editNumOfBooks = new WLineEdit(container);
	editNumOfBooks->setPlaceholderText("num of books");
	t->bindWidget("numOfBooks", editNumOfBooks);
	
	WLineEdit *editNumInSeria = new WLineEdit(container);
	editNumInSeria->setPlaceholderText("number in seria");
	t->bindWidget("numInSeria", editNumInSeria);
	
	WLineEdit *editMark = new WLineEdit(container);
	editMark->setPlaceholderText("mark");
	editMark->setValidator(new Wt::WIntValidator(1, 10));
	t->bindWidget("mark", editMark);
	
	WPushButton *button = new WPushButton("Add book", container);
	button->setMargin(10, Top | Bottom);

	button->clicked().connect(std::bind([=] () {BookManager bm; bm.addBook(editTitle->valueText().toUTF8(),
																		   editAuthor->valueText().toUTF8(),
																		   editAuthorYears->valueText().toUTF8(),
																		   editGenre->valueText().toUTF8(),
																		   intoInt(editYear),
																		   editSeria->valueText().toUTF8(),
																		   intoInt(editNumOfBooks),
																		   intoInt(editNumInSeria),
																		   intoInt(editMark)); }));
	
	t->bindWidget("button", button);
	_pagecontent->addWidget(t);	
}

void BasePage::addAuthor(){
	WContainerWidget *container1 = new WContainerWidget();
	Wt::WTemplate *r = new Wt::WTemplate(Wt::WString::tr("addAuthorForm"));
	
	WLineEdit *editName = new WLineEdit(container1);
	editName->setPlaceholderText("name");
	r->bindWidget("name", editName);
	
	WLineEdit *editYears = new WLineEdit(container1);
	editYears->setPlaceholderText("years");
	r->bindWidget("years", editYears);
				  
	WPushButton *button = new WPushButton("Add author", container1);
	button->setMargin(10, Top | Bottom);
				  
	button->clicked().connect(std::bind([=] () {BookManager am; am.addAuthor("123","2016"); }));
				  
	r->bindWidget("button", button);
	_pagecontent->addWidget(r);
}



void BasePage::addMark(const Dbo::collection<Dbo::ptr<Book> >& listaddmark){	
	WTable *table = new WTable();
	table->setHeaderCount(1);
	table->setStyleClass("tablestyle");
	table->elementAt(0, 0)->addWidget(new WText("<p align='left'> # </p>"));
	table->elementAt(0, 1)->addWidget(new WText("<p align='left'> Title of book </p>"));
	table->elementAt(0, 2)->addWidget(new WText("<p align='left'> Author </p>"));
	table->elementAt(0, 3)->addWidget(new WText("<p align='left'> Genre </p>"));
	table->elementAt(0, 4)->addWidget(new WText("<p align='left'> Add your mark </p>"));
	_pagecontent->addWidget(table);
	int row=1;
		for (Dbo::collection<Dbo::ptr<Book> >::const_iterator i = listaddmark.begin(); i != listaddmark.end(); ++i){
			Dbo::ptr<Book> book = *i;
			table->setStyleClass("tablestyle th,td,tr");
			//headers
			table->elementAt(row, 0)
			->addWidget(new WText(WString::fromUTF8("{1}")
					  .arg(row)));
			//titles
			table->elementAt(row, 1)
			->addWidget(new WText(WString::fromUTF8("{1}")
				      .arg(book.get()->title)));
			//authors
			table->elementAt(row, 2)
			->addWidget(new WText(WString::fromUTF8("{1}")
				      .arg((book.get()->author.get()->name))));
			//genres
			table->elementAt(row, 3)
			->addWidget(new WText(WString::fromUTF8("{1}")
				      .arg((book.get()->genre.get()->genre))));
			//add mark
			WLineEdit *editAddMark = new WLineEdit(table->elementAt(row,4));
			editAddMark->setPlaceholderText("Add mark");
			table->elementAt(row, 4)
			->addWidget(editAddMark);
			table->elementAt(row, 4)
			->addWidget(new WText("<br></br>"));
			WPushButton *button = new WPushButton("Add mark", table->elementAt(row,4));
			button->setMargin(10, Top | Bottom);
			table->elementAt(row, 4)
			->addWidget(button);
			/*button->clicked().connect(std::bind([] ( Dbo::ptr<Book> book) {
						BookManager bm;
						std::cout<<book.get()->title; 
						int curMark=book.get()->mark; 
						int curNumMarks=book.get()->numMarks; 	
						bm.refreshRate(book.get()->id, curMark+5, curNumMarks+1, session);												
			},*i ));*/
			row++;
			_pagecontent->addWidget(table);	
		}
}
