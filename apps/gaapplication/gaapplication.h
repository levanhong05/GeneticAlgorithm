#ifndef GAAPPLICATION_H
#define GAAPPLICATION_H

#include <QMainWindow>

namespace Ui {
class GAApplication;
}

namespace GeneticAlgorithm {

class GAApplication : public QMainWindow
{
    Q_OBJECT
public:
    explicit GAApplication(QWidget *parent = 0);
    ~GAApplication();

public slots:
    QMenu* addMenu(const QString &title);
    int addTab(QString title, QWidget *w, QIcon icon = QIcon(), bool activated = false, bool showCloseButton = true);

    void raiseTab(QWidget * w);
    void removeTab(QWidget * w);

    void onCurrentTabChanged(int index);

    void hideTabBar();
    void showTabBar();
    void enableTab(QWidget *w);
    void disableTab(QWidget *w);

    void onHideTab(QString mode);

signals:
    void currentTabChanged(QWidget *w);

private slots:
    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionTraveling_Salesman_Problem_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionPrisoner_s_Dilemma_triggered();

    void on_actionWord_Matching_Problem_triggered();

    void on_actionQuadratic_Equation_Solving_triggered();

    void on_actionMaximize_f_x_x_triggered();

    void on_actionMinimization_a_Sine_Function_with_Constraints_triggered();

    void on_actionMximizing_the_Function_f_x_x_sin_10_x_10_triggered();

private:
    Ui::GAApplication *ui;

};

}

#endif // GAAPPLICATION_H
