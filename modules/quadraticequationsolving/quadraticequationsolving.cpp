#include "quadraticequationsolving.h"
#include "ui_quadraticequationsolving.h"

#include "console.h"

using namespace GeneticAlgorithm;

QuadraticEquationSolving::QuadraticEquationSolving(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuadraticEquationSolving)
{
    ui->setupUi(this);
}

QuadraticEquationSolving::~QuadraticEquationSolving()
{
    delete ui;
}

QString QuadraticEquationSolving::name()
{
    return tr("Quadratic Equation Solving");
}

void QuadraticEquationSolving::execute()
{
    ui->txtResult->clear();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            ipop[i].chromosome[j] = qrand() % 2;
        }
    }

    /* start of the next generation */
    int index = 0;

    while (index < gen) {
        /* Converting a binary string into decimal value */
        for (int i = 0; i < 10; ++i) {
            num = 0;

            for (int j = 0; j < 4; ++j) {
                num = num + (ipop[i].chromosome[j] * pow(2, j));
            }

            num = num - (ipop[i].chromosome[4] * pow(2, 4));
            ipop[i].decimal_val = num;
        }

        /* Calculating fittness value */
        for (int i = 0; i < 10; ++i) {
            ipop[i].fittness = function(ipop[i].decimal_val);
        }

        ui->txtResult->insertPlainText("\n\n\nGeneration " + QString::number(index) + "\n");
        ui->txtResult->insertPlainText("\nInitial population - output\n");

        for (int i = 0; i < 10; ++i) {
            for (int j = 4; j >= 0; --j) {
                ui->txtResult->insertPlainText(QString::number(ipop[i].chromosome[j]));
            }

            ui->txtResult->insertPlainText("         " + QString::number(ipop[i].decimal_val));
            ui->txtResult->insertPlainText("         " + QString::number(ipop[i].fittness));
            ui->txtResult->insertPlainText("\n");
        }

        for (int i = 0; i < 10; ++i) {
            if (ipop[i].fittness == 0) {
                ui->txtResult->insertPlainText("\nStop generations\n");
                ui->txtResult->insertPlainText("Result = " + QString::number(ipop[i].decimal_val) +"\n");

                ui->txtResult->insertPlainText("End\n");
                return;
            }
        }

        if (index == gen - 1) {
            ui->txtResult->insertPlainText("\nStop generations\n");
            ui->txtResult->insertPlainText("Result = Can not found root.\nEnd\n");

            return;
        }

        /* tournament selection */
        ui->txtResult->insertPlainText("\nTournament selection\n ");

        int i = 0;

        while (i <= 9) {
            s1 = rand() % 10;
            s2 = rand() % 10;
            ui->txtResult->insertPlainText(QString::number(s1) + " " + QString::number(s2) + " " + QString::number(ipop[s1].fittness) +
                                           " " + QString::number(ipop[s2].fittness) + "\n");

            if (ipop[s1].fittness < ipop[s2].fittness) {
                for (int j = 0; j < 5; ++j) {
                    newpop[i].chromosome[j] = ipop[s1].chromosome[j];
                }
            } else {
                for (int j = 0; j < 5; ++j) {
                    newpop[i].chromosome[j] = ipop[s2].chromosome[j];
                }
            }

            i++;
        }

        ui->txtResult->insertPlainText("\nNew population - output\n");

        for (int i = 0; i < 10; ++i) {
            for (int j = 4; j >= 0; --j) {
                ui->txtResult->insertPlainText(QString::number(newpop[i].chromosome[j]));
            }

            ui->txtResult->insertPlainText("\n");
        }

        /*crossover operation */
        ui->txtResult->insertPlainText("\nCrossover operation\n");
        ui->txtResult->insertPlainText("\nLeft/right cut-point position\n");

        for (int i = 0; i <= 4; ++i) {
            flag = qrand() % 2;
            cut = qrand() % 5;

            ui->txtResult->insertPlainText(QString::number(flag) + " " + QString::number(cut) + "\n");

            if (flag == 0) { /* crossover to left of cutpoint position*/
                for (int j = 0; j <= cut - 1; ++j) {
                    t = newpop[2 * i].chromosome[j];
                    newpop[2 * i].chromosome[j] = newpop[(2 * i + 1)].chromosome[j];
                    newpop[(2 * i + 1)].chromosome[j] = t;
                }
            } else { /* crossover to the right of cutpoint position*/
                for (int j = cut + 1; j <= 4; ++j) {
                    t = newpop[2 * i].chromosome[j];
                    newpop[2 * i].chromosome[j] = newpop[(2 * i + 1)].chromosome[j];
                    newpop[(2 * i + 1)].chromosome[j] = t;
                }
            }

            for (int j = 4; j >= 0; --j) {
                ui->txtResult->insertPlainText(QString::number(newpop[2 * i].chromosome[j]));
            }

            ui->txtResult->insertPlainText("\n");

            for (int j = 4; j >= 0; --j) {
                ui->txtResult->insertPlainText(QString::number(newpop[2 * i + 1].chromosome[j]));
            }

            ui->txtResult->insertPlainText("\n");
        }

        /* copy newpopulation to initial population*/
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 5; ++j) {
                ipop[i].chromosome[j] = newpop[i].chromosome[j];
            }
        }

        index++;
    }
}

int QuadraticEquationSolving::function(int x)
{
    return (x * x + 5 * x + 6);
}

void QuadraticEquationSolving::on_btnRun_clicked()
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
