#include "basepage.h"

BasePage::BasePage(WContainerWidget* container){
	_container=container;
	_header=new WContainerWidget(container);
}

void BasePage::printHeader(){
	_header->addWidget(new WText("Privet.Bogdan!"));
}
	