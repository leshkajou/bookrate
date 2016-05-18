#include "app.h"
#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WLink>

using namespace Wt;

WApplication* createApplication(const WEnvironment &env) {
	WApplication* tmp = new App(env);
    return tmp;
}

int main(int argc, char** argv) {
    return WRun(argc, argv, &createApplication);
}
