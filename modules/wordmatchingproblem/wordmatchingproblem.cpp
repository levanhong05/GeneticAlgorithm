#include "wordmatchingproblem.h"
#include "ui_wordmatchingproblem.h"

#include "console.h"

using namespace GeneticAlgorithm;

WordMatchingProblem::WordMatchingProblem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordMatchingProblem)
{
    ui->setupUi(this);

    gen = 0;

    for (int i = 0; i < 50; i++) {
        pfit[i] = 0;
        cfit[i] = 0;
    }

    for (int i = 0; i < 150; i++) {
        fit[i] = 0;
    }

    for (int i = 0; i < 5; i++) {
        mfit[i] = 0;
    }
}

WordMatchingProblem::~WordMatchingProblem()
{
    delete ui;
}

QString WordMatchingProblem::name()
{
    return tr("Word Matching Problem");
}

void WordMatchingProblem::execute()
{
    ui->txtResult->clear();

    getInput();
    initialPop();

    //display();
    reproduction(); //sorting_based_on_fitness();
    display();

    if (pfit[0] != _input.length()) {
        crossover();
        gen++;
        mutation();
        reproduction(); //sorting_based_on_fitness();
        display();
        inputChoice();
    }

    results();
}

void WordMatchingProblem::getInput()
{
    ui->txtResult->insertPlainText("WORD MATCHING PROBLEM");
    ui->txtResult->insertPlainText("\n **************************************");
    ui->txtResult->insertPlainText("\n\n\n\nTHE WORD TO BE MATCHED : ");

    _input = ui->txtWordMatch->text();

    ui->txtResult->insertPlainText(_input);

    ui->txtResult->insertPlainText("\n\n\n THE ASCII EQUIVALENT OF THE LETTERS IN THE ENTERED WORD");
    ui->txtResult->insertPlainText("\n------- ------- ------- ");
    ui->txtResult->insertPlainText("\n\n LETTERS :");

    for (int i = 0; i < _input.length(); i++) {
        ui->txtResult->insertPlainText(" " + _input[i] + " ");
    }

    ui->txtResult->insertPlainText("\n ASCII :");

    for (int i = 0; i < _input.length(); i++) {
        int code = _input[i].toLatin1();

        ui->txtResult->insertPlainText(" " + QString::number(code));
    }
}

void WordMatchingProblem::initialPop()
{
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < _input.length(); j++) {
            _parent[i][j] = qrand() % 27 + 97;

            if (_parent[i][j] == _input[j]) {
                pfit[i]++;
            }
        }
    }
}

void WordMatchingProblem::display()
{
    ui->txtResult->insertPlainText("\n\n THE CHROMOSOMES OF PARENTS AND CHILDREN");
    ui->txtResult->insertPlainText("\n---- ------ ------- --\n");
    ui->txtResult->insertPlainText("\n PREVIOUS GENERATION CHILDREN CHROMOSOMES\n\n");

    for (int i = 0; i < 50; i++) {
        if ((i % 4) == 0) {
            ui->txtResult->insertPlainText("\n");
        }

        for (int j = 0; j < _input.length(); j++) {
            ui->txtResult->insertPlainText(QString (_child[i][j]));
        }

        ui->txtResult->insertPlainText("\t");

        ui->txtResult->insertPlainText(QString::number(cfit[i]));

        ui->txtResult->insertPlainText("\t");
    }

    ui->txtResult->insertPlainText("\nMUTANTS OF THIS GENERATION\n");

    for (int i = 0; i < 5; i++) {
        if (i == 3) {
            ui->txtResult->insertPlainText("\n");
        }

        for (int j = 0; j < _input.length(); j++) {
            ui->txtResult->insertPlainText(QString (_mutant[i][j]));
        }

        ui->txtResult->insertPlainText("\t");

        ui->txtResult->insertPlainText(QString::number(mfit[i]));

        ui->txtResult->insertPlainText("\t");
    }

    ui->txtResult->insertPlainText("\n\n THE CHROMOSOMES OF PARENTS AND CHILDREN");
    ui->txtResult->insertPlainText("\n---- ------ ------\n");
    ui->txtResult->insertPlainText("\n NEXT GENERATION PARENTS CHROMOSOMES\n\n");

    for (int i = 0; i < 50; i++) {
        if ((i % 4) == 0) {
            ui->txtResult->insertPlainText("\n");
        }

        for (int j = 0; j < _input.length(); j++) {
            ui->txtResult->insertPlainText(QString (_parent[i][j]));
        }

        ui->txtResult->insertPlainText("\t");

        ui->txtResult->insertPlainText(QString::number(pfit[i]));

        ui->txtResult->insertPlainText("\t");
    }
}

void WordMatchingProblem::reproduction() //sorting_based_on_fitness()
{
    QChar tempc;
    int temp;

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < _input.length(); j++) {
            _mating_pool[i][j] = _parent[i][j];
            fit[i] = pfit[i];
        }
    }

    for (int i = 50; i < 100; i++) {
        for (int j = 0; j < _input.length(); j++) {
            _mating_pool[i][j] = _child[i - 50][j];
            fit[i] = cfit[i - 50];
        }
    }

    for (int i = 100; i < 105; i++) {
        for (int j = 0; j < _input.length(); j++) {
            _mating_pool[i][j] = _mutant[i - 100][j];
            fit[i] = mfit[i - 100];
        }
    }

//sorting
    for (int i = 0; i < 105; i++) {
        for (int j = i + 1; j < 105; j++) {
            if (fit[i] < fit[j]) {
                for (int k = 0; k < _input.length(); k++) {
                    tempc = _mating_pool[i][k];
                    _mating_pool[i][k] = _mating_pool[j][k];
                    _mating_pool[j][k] = tempc;
                    temp = fit[i];
                    fit[i] = fit[j];
                    fit[j] = temp;
                }
            }
        }
    }

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < _input.length(); j++) {
            _parent[i][j] = _mating_pool[i][j];
            pfit[i] = fit[i];
        }
    }

    for (int i = 50; i < 100; i++) {
        for (int j = 0; j < _input.length(); j++) {
            _child[i - 50][j] = _mating_pool[i][j];
            cfit[i - 50] = fit[i];
        }
    }
}

void WordMatchingProblem::crossover()
{
    int xover_pt;

    for (int i = 0; i < 50; i++) {
        xover_pt = qrand() % (_input.length());
        cfit[i] = 0;
        cfit[i + 1] = 0;

        for (int j = 0; j < xover_pt; j++) {
            _child[i][j] = _parent[i][j];

            if (_input[j] == _child[i][j]) {
                cfit[i]++;
            }

            _child[i + 1][j] = _parent[i + 1][j];

            if (_input[j] == _child[i + 1][j]) {
                cfit[i + 1]++;
            }
        }

        for (int j = xover_pt; j < _input.length(); j++) {
            _child[i][j] = _parent[i + 1][j];

            if (_input[j] == _child[i][j]) {
                cfit[i]++;
            }

            _child[i + 1][j] = _parent[i][j];

            if (_input[j] == _child[i + 1][j]) {
                cfit[i + 1]++;
            }
        }

        i++;
    }
}

void WordMatchingProblem::mutation()
{
    int mut_pt;
    char mut_val;

    int j;

    for (int i = 0; i < 05; i++) {
        mut_pt = qrand() % _input.length();
        mut_val = qrand() % 27 + 97;

        mfit[i] = 0;

        for (j = 0; j < mut_pt; j++) {
            _mutant[i][j] = _parent[1][j];

            if (_mutant[i][j] == _input[j]) {
                mfit[i]++;
            }
        }

        _mutant[i][mut_pt] = mut_val;

        if (_mutant[i][j] == _input[j]) {
            mfit[i]++;
        }

        for (j = mut_pt + 1; j < _input.length(); j++) {
            _mutant[i][j] = _parent[1][j];

            if (_mutant[i][j] == _input[j]) {
                mfit[i]++;
            }
        }
    }
}

void WordMatchingProblem::results()
{
    ui->txtResult->insertPlainText("\n\n\nWORD MATCHING PROBLEM ");
    ui->txtResult->insertPlainText("\n ****************************************");
    ui->txtResult->insertPlainText("\n\n\n THE MATCHING WORD FOR THE GIEN INPUT WORD");
    ui->txtResult->insertPlainText("\n\n OBTAINED USING GENETIC ALGORITHM");
    ui->txtResult->insertPlainText("\n\n ");

    for (int i = 0; i < _input.length(); i++) {
        ui->txtResult->insertPlainText(QString (_parent[0][i]));
    }

    ui->txtResult->insertPlainText("\n –");

    for (int i = 0; i < _input.length(); i++) {
        ui->txtResult->insertPlainText("-");
    }

    ui->txtResult->insertPlainText("–\n\n\n USER INPUT : " + _input);
    ui->txtResult->insertPlainText("\n\n\n THE FITNESS OF THE GA GENERATED WORD AND THE USER’S INPUT");
    ui->txtResult->insertPlainText("\n\n " + QString::number(pfit[0]) + "/" + QString::number(_input.length()));
    ui->txtResult->insertPlainText("\n\n\n GENERATIONS COUNT : " + QString::number(gen));
}

void WordMatchingProblem::inputChoice()
{
    ui->txtResult->insertPlainText("\n\n\n\n GENEREATION NUMBER : " + QString::number(gen));
    ui->txtResult->insertPlainText("\n –––––––––––––––");
    ui->txtResult->insertPlainText("\n\n\nTHE FITTEST INDIVIDUAL TILL THE PREVIOUS GENERATION\n\n\n");

    for (int i = 0; i < _input.length(); i++) {
        ui->txtResult->insertPlainText(QString (_parent[0][i]));
    }

    ui->txtResult->insertPlainText(" / ");

    for (int i = 0; i < _input.length(); i++) {
        ui->txtResult->insertPlainText(QString (_input[i]));
    }

    ui->txtResult->insertPlainText("\n\n\n WITH A FITNESS OF " + QString::number(pfit[0]) + "/" + QString::number(_input.length()));
}

void WordMatchingProblem::on_btnRun_clicked()
{
    execute();
}
