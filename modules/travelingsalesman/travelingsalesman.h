#ifndef TRAVELINGSALESMAN_H
#define TRAVELINGSALESMAN_H

#include <QWidget>
#include <QObject>

#include "travelingsalesman_global.h"

namespace Ui {
class TravelingSalesman;
}

namespace GeneticAlgorithm {

class TRAVELINGSALESMANSHARED_EXPORT TravelingSalesman : public QWidget
{
    Q_OBJECT
public:
    explicit TravelingSalesman(QWidget *parent = 0);
    ~TravelingSalesman();

    QString name();

    void execute();

private slots:
    void on_txtNumberGeneration_editingFinished();

    void on_btnRun_clicked();

private:
    void offcal1(QList<QList<int> > pa);
    void offcal2(QList<QList<int> > pa);

private:
    Ui::TravelingSalesman *ui;

    QList<QList<int> > _tsp;
    QList<QList<int> > _pa;

    int loc;
    int count, row, res[1][10], row1, col1;
    int numoff;
    int offspring[1000][10];
    int mincost, mc;

    int gen;
};

}

#endif // TRAVELINGSALESMAN_H
