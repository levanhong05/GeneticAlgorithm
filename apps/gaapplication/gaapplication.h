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

private slots:
    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionTraveling_Salesman_Problem_triggered();

private:
    Ui::GAApplication *ui;
};

}

#endif // GAAPPLICATION_H
