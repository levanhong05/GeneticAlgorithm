#include "gaapplication.h"
#include "ui_gaapplication.h"

#include "console.h"

#include "aboutscreen.h"

#include "travelingsalesman.h"
#include "wordmatchingproblem.h"
#include "prisonerdilemma.h"

using namespace GeneticAlgorithm;

GAApplication::GAApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GAApplication)
{
    ui->setupUi(this);

    this->addDockWidget(Qt::BottomDockWidgetArea, console.dock());

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onCurrentTabChanged(int)));

    console.logInfo(tr("Welcome to Genetic Algorithm Application !!!"));
}

GAApplication::~GAApplication()
{
    delete ui;
}

QMenu *GAApplication::addMenu(const QString &title)
{
    return ui->menuBar->addMenu(title);
}

int GAApplication::addTab(QString title, QWidget *w, QIcon icon, bool activated, bool showCloseButton)
{
    int lastIndex = ui->tabWidget->addTab(w, icon, title);

    if (activated) {
        ui->tabWidget->setCurrentIndex(lastIndex);
    }

    if (!showCloseButton) {
        ui->tabWidget->tabBar()->tabButton(lastIndex, QTabBar::RightSide)->resize(0, 0);
    }

    return lastIndex;
}

void GAApplication::raiseTab(QWidget *w)
{
    int index = ui->tabWidget->indexOf(w);

    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (w == ui->tabWidget->widget(i)) {
            ui->tabWidget->setCurrentIndex(index);
            return;
        }
    }
    console.logDebug("mainwindow::raiseTab error: can not find widget index.");
}

void GAApplication::removeTab(QWidget *w)
{
    int index = ui->tabWidget->indexOf(w);

    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (w == ui->tabWidget->widget(i)) {
            ui->tabWidget->removeTab(index);
            return;
        }
    }

    console.logDebug("mainwindow::removeTab error: can not find widget index.");
}

void GAApplication::onHideTab(QString mode)
{
    Q_UNUSED(mode);
}

void GAApplication::onCurrentTabChanged(int index)
{
    emit currentTabChanged(ui->tabWidget->widget(index));
}

void GAApplication::hideTabBar()
{
    QTabBar *tabBar = ui->tabWidget->findChild<QTabBar *>();
    tabBar->hide();
}

void GAApplication::showTabBar()
{
    QTabBar *tabBar = ui->tabWidget->findChild<QTabBar *>();
    tabBar->show();
}

void GAApplication::enableTab(QWidget *w)
{
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (w == ui->tabWidget->widget(i)) {
            ui->tabWidget->setTabEnabled(i, true);
            return;
        }
    }

    console.logDebug("mainwindow::raiseTab error: can not find widget index.");
}

void GAApplication::disableTab(QWidget *w)
{
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (w == ui->tabWidget->widget(i)) {
            ui->tabWidget->setTabEnabled(i, false);
            return;
        }
    }

    console.logDebug("mainwindow::raiseTab error: can not find widget index.");
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

void GAApplication::on_actionTraveling_Salesman_Problem_triggered()
{
    TravelingSalesman *salemans = new TravelingSalesman(this);

    this->addTab("TSP", salemans);
}

void GAApplication::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->widget(index)->close();

    removeTab(ui->tabWidget->widget(index));
}

void GAApplication::on_actionPrisoner_s_Dilemma_triggered()
{
    PrisonerDilemma *prisoner = new PrisonerDilemma(this);

    this->addTab("PDP", prisoner);
}

void GAApplication::on_actionWord_Matching_Problem_triggered()
{
    WordMatchingProblem *word = new WordMatchingProblem(this);

    this->addTab("WMP", word);
}
