#ifndef WORDMATCHINGPROBLEM_H
#define WORDMATCHINGPROBLEM_H

#include "wordmatchingproblem_global.h"

#include <QWidget>
#include <QObject>

namespace Ui {
class WordMatchingProblem;
}

namespace GeneticAlgorithm {

class WORDMATCHINGPROBLEMSHARED_EXPORT WordMatchingProblem : public QWidget
{
    Q_OBJECT
public:
    explicit WordMatchingProblem(QWidget *parent = 0);
    ~WordMatchingProblem();

    QString name();

    void execute();

private slots:
    void on_btnRun_clicked();

private:
    Ui::WordMatchingProblem *ui;

    QString _input;

    QChar _parent[50][15], _child[50][15], _mating_pool[105][15], _mutant[5][15];

    int pfit[50], cfit[50], fit[105], mfit[5];

    int gen;

    void inputChoice();
    void results();
    void mutation();
    void crossover();
    void reproduction();
    void display();
    void initialPop();
    void getInput();
};

}

#endif // WORDMATCHINGPROBLEM_H
