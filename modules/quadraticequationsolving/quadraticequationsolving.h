#ifndef QUADRATICEQUATIONSOLVING_H
#define QUADRATICEQUATIONSOLVING_H

#include "quadraticequationsolving_global.h"

#include <QWidget>
#include <QObject>

namespace Ui
{
class QuadraticEquationSolving;
}

namespace GeneticAlgorithm
{

class QUADRATICEQUATIONSOLVINGSHARED_EXPORT QuadraticEquationSolving : public QWidget
{
    Q_OBJECT
public:
    explicit QuadraticEquationSolving(QWidget *parent = 0);
    ~QuadraticEquationSolving();

    QString name();

    void execute();

private slots:
    void on_btnRun_clicked();

private:
    int function(int x);

    struct c {
        int chromosome[5];
        int decimal_val;
        int fittness;
    };

private:
    Ui::QuadraticEquationSolving *ui;

    struct c ipop[10], newpop[10];
    int cut, gen, t, flag, num, s1, s2;

};

}

#endif // QUADRATICEQUATIONSOLVING_H
