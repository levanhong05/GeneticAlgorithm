#ifndef PRISONERDILEMMA_H
#define PRISONERDILEMMA_H

#include "prisonerdilemma_global.h"

#include <QWidget>
#include <QObject>

namespace Ui {
class PrisonerDilemma;
}

namespace GeneticAlgorithm {

class PRISONERDILEMMASHARED_EXPORT PrisonerDilemma : public QWidget
{
    Q_OBJECT
public:
    explicit PrisonerDilemma(QWidget *parent = 0);
    ~PrisonerDilemma();

    QString name();

    void execute();

private slots:
    void on_btnRun_clicked();

private:
    int calculate(int*);
    void crossover(int*, int*);
    void sortSelect(void);

private:
    Ui::PrisonerDilemma *ui;

    //THESE ARE SOME GLOBAL VARIABLE USED
    int bestScore[20];
    int score[9];
    int index[6];
};

}

#endif // PRISONERDILEMMA_H
