#include "application.h"

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    _mainWindow = new GAApplication();
}

void Application::showMainWindow()
{
    _mainWindow->showMaximized();
}
