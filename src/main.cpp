#include "MainApp/MainApp.hpp"

int main(int argc, char* args[]) {

	MainApp mainApp;

    if (!mainApp.init()) {
        return 1;
    }

    mainApp.run();

	mainApp.deinit();

	return 0;
}
