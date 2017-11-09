#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "gaapplication.h"

using namespace GeneticAlgorithm;

class Application : public QApplication
{
public:
    Application(int &argc, char **argv);
    ~Application() {}

public slots:
    void showMainWindow();

private:
    GAApplication *_mainWindow;

};

#endif // APPLICATION_H
