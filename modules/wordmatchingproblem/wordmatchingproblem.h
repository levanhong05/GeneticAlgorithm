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

private:
    Ui::WordMatchingProblem *ui;

    QString _input;
    QStringList _parent;
    QStringList _child;
    QStringList _mating_pool;

    QStringList _mutant;

    int pfit[50], cfit[50], fit[105], mfit[05];

    int gen;

    int inputChoice();
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
