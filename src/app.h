#ifndef APP_H
#define APP_H
#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WLink>
#include <Wt/WText>

using namespace Wt;

class App: public WApplication {
private:
    std::string appName;
    WContainerWidget* _content;
public:
    App(const WEnvironment &env);
	WContainerWidget* content();
};

#endif