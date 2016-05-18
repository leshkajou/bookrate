#include "app.h"
#include "basepage.h"
#include <Wt/WTemplate>

using namespace Wt;

App::App(const WEnvironment &env): WApplication(env) {
        appName = "RateYourBook";
        setTitle(appName);
		_content = 0;
		BasePage test(content());
		test.printHeader();
}

WContainerWidget* App::content() {
	if (_content == 0) {
		_content = new WContainerWidget(root());
		_content->setId("content");
	}
	return _content;
	
}