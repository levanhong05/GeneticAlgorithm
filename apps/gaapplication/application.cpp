#include "application.h"

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    _mainWindow = new GAApplication();

    //GeneticAlgorithm::WorkCase::currentCase();
}

void Application::showMainWindow()
{
    _mainWindow->showMaximized();
}
