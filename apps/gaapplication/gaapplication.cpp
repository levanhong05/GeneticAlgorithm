#include "gaapplication.h"
#include "ui_gaapplication.h"

#include "console.h"

#include "aboutscreen.h"

using namespace GeneticAlgorithm;

GAApplication::GAApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GAApplication)
{
    ui->setupUi(this);

    this->addDockWidget(Qt::BottomDockWidgetArea, console.dock());

    console.logInfo(tr("Welcome to Genetic Algorithm Application !!!"));
}

GAApplication::~GAApplication()
{
    delete ui;
}

void GAApplication::on_actionQuit_triggered()
{
    QApplication::quit();
}

void GAApplication::on_actionAbout_triggered()
{
    AboutScreen *screen = new AboutScreen();

    screen->show();
}
