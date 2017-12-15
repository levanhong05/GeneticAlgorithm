#include "travelingsalesman.h"
#include "ui_travelingsalesman.h"

#include "console.h"

using namespace GeneticAlgorithm;

TravelingSalesman::TravelingSalesman(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TravelingSalesman)
{
    ui->setupUi(this);

    ui->txtNumberGeneration->setValidator(new QIntValidator(1, INT_MAX));

    gen = 0;
}

TravelingSalesman::~TravelingSalesman()
{
    delete ui;
}

QString GeneticAlgorithm::TravelingSalesman::name()
{
    return tr("Traveling Salesman Problem");
}

void TravelingSalesman::execute()
{
    int index = 0;

    _tsp.push_back({999, 10, 3, 2, 5, 6, 7, 2, 5, 4});
    _tsp.push_back({20, 999, 3, 5, 10, 2, 8, 1, 15, 6});
    _tsp.push_back({10, 5, 999, 7, 8, 3, 11, 12, 3, 2});
    _tsp.push_back({3, 4, 5, 999, 6, 4, 10, 6, 1, 8});
    _tsp.push_back({1, 2, 3, 4, 999, 5, 10, 20, 11, 2});
    _tsp.push_back({8, 5, 3, 10, 2, 999, 6, 9, 20, 1});
    _tsp.push_back({3, 8, 5, 2, 20, 21, 999, 3, 5, 6});
    _tsp.push_back({5, 2, 1, 25, 15, 10, 6, 999, 8, 1});
    _tsp.push_back({10, 11, 6, 8, 3, 4, 2, 15, 999, 1});
    _tsp.push_back({5, 10, 6, 4, 15, 1, 3, 5, 2, 999});

    _pa.push_back({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    _pa.push_back({9, 8, 6, 3, 2, 1, 0, 4, 5, 7});
    _pa.push_back({2, 3, 5, 0, 1, 4, 9, 8, 6, 7});
    _pa.push_back({4, 8, 9, 0, 1, 3, 2, 5, 6, 7});

    for (int i = 4; i < 1000; i++) {
        _pa.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    }

    mincost = 9999;

    row = 0;

    numoff = 4;

    mc = 0;
    row1 = 0;
    col1 = 0;
    loc = 0;

    ui->txtResult->clear();

    offcal1(_pa);
    offcal2(_pa);

    ui->txtResult->insertPlainText("Generation 1\n");

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 10; j++) {
            ui->txtResult->insertPlainText(QString::number(offspring[i][j]) + "     ");
        }

        ui->txtResult->insertPlainText("\n");
    }

    index = count;

    for (int y = 1; y < gen; y++) {
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < 10; j++) {
                _pa[i][j] = offspring[i][j];
            }
        }

        numoff = count;

        offcal1(_pa);
        offcal2(_pa);

        ui->txtResult->insertPlainText("\nGeneration " + QString::number(y + 1) + "\n");

        for (int i = index; i < count; i++) {
            for (int j = 0; j < 10; j++) {
                ui->txtResult->insertPlainText(QString::number(offspring[i][j]) + "     ");
            }

            ui->txtResult->insertPlainText("\n");
        }

        index = count;
    }

    ui->txtResult->insertPlainText("\n\nMinimum Cost Path\n");

    for (int z = 0; z < 10; z++) {
        ui->txtResult->insertPlainText(QString::number(res[0][z]) + "     ");
    }

    ui->txtResult->insertPlainText("\n\nMinimum Cost:\t" + QString::number(mincost) + "\n");
}

/* finding the offspring using cyclic crossover */
void TravelingSalesman::offcal1(QList<QList<int> > pa)
{
    count = 0;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 10; j++) {
            offspring[i][j] = -1;
        }
    }

    for (int k = 0; k < numoff; k++) {
        for (int l = k + 1; l < numoff; l++) {
            offspring[row][0] = pa[k][0];
            loc = pa[l][0];
            bool flag = true;

            while (flag) {
                for (int j = 0; j < 10; j++) {
                    if (pa[k][j] == loc) {
                        if (offspring[row][j] == -1) {
                            offspring[row][j] = loc;
                            loc = pa[l][j];
                        } else {
                            flag = false;
                        }
                    }
                }
            }/* end while*/

            for (int m = 0; m < 10; m++) {
                if (offspring[row][m] == -1) {
                    offspring[row][m] = pa[l][m];
                }
            }

            for (int z = 0; z < 10; z++) {
                if (z < 9) {
                    row1 = offspring[row][z];
                    col1 = offspring[row][z + 1];
                    mc = mc + _tsp[row1][col1];
                } else {
                    row1 = offspring[row][z];
                    col1 = offspring[row][0];
                    mc = mc + _tsp[row1][col1];
                }
            }

            if (mc < mincost) {
                for (int z = 0; z < 10; z++) {
                    res[0][z] = offspring[row][z];
                }

                mincost = mc;
            }

            count++;
            row++;
        }/* end l*/
    }
}

void TravelingSalesman::offcal2(QList<QList<int> > pa)
{
    for (int k = 0; k < numoff; k++) {
        for (int l = k + 1; l < numoff; l++) {
            offspring[row][0] = pa[l][0];
            loc = pa[k][0];
            bool flag = true;

            while (flag) {
                for (int j = 0; j < 10; j++) {
                    if (pa[l][j] == loc) {
                        if (offspring[row][j] == -1) {
                            offspring[row][j] = loc;
                            loc = pa[k][j];
                        } else {
                            flag = false;
                        }
                    }
                }
            }/* end while*/

            for (int m = 0; m < 10; m++) {
                if (offspring[row][m] == -1) {
                    offspring[row][m] = pa[k][m];
                }
            }

            for (int z = 0; z < 10; z++) {
                if (z < 9) {
                    row1 = offspring[row][z];
                    col1 = offspring[row][z + 1];
                    mc = mc + _tsp[row1][col1];
                } else {
                    row1 = offspring[row][z];
                    col1 = offspring[row][0];
                    mc = mc + _tsp[row1][col1];
                }
            }

            row++;

            if (mc < mincost) {
                for (int z = 0; z < 10; z++) {
                    res[0][z] = offspring[row][z];
                }

                mincost = mc;
            }

            count++;
        }/* end l*/
    }
}

void TravelingSalesman::on_txtNumberGeneration_editingFinished()
{
    bool ok = false;

    gen = ui->txtNumberGeneration->text().toInt(&ok);

    if (!ok) {
        gen = 0;
    }
}

void TravelingSalesman::on_btnRun_clicked()
{
    bool ok = false;

    gen = ui->txtNumberGeneration->text().toInt(&ok);

    if (!ok) {
        gen = 0;
    }

    if (gen > 0) {
        execute();
    }
}
