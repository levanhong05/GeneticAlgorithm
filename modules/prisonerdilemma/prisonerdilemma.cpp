#include "prisonerdilemma.h"
#include "ui_prisonerdilemma.h"

#include "console.h"

using namespace GeneticAlgorithm;

PrisonerDilemma::PrisonerDilemma(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrisonerDilemma)
{
    ui->setupUi(this);

    ui->txtNumberGeneration->setValidator(new QIntValidator(1, INT_MAX));
}

PrisonerDilemma::~PrisonerDilemma()
{
    delete ui;
}

QString PrisonerDilemma::name()
{
    return tr("Prisoner’s Dilemma");
}

void PrisonerDilemma::execute()
{
    int a[10][70], selectString[5][70];
    int bestString[20][70], max, ind = 0;
    int counter = 1;
    int n, temp[10];

    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 70; i++) {
            a[j][i] = qrand() % 3;
        }
    }

    //THE NUMBER OF GENERATION TO BE SCANED IN
    ui->txtResult->insertPlainText("Number of generation: " + ui->txtNumberGeneration->text() + "\n");

    n = ui->txtNumberGeneration->text().toInt();

    for (int i = 0; i < 10; i++) {
        score[i] = calculate(&a[i][0]);
    }

    //function for sorting the score array and finding the index of best score
    sortSelect();

    for (int i = 0; i < 7; i++) {
       int  p = index[i]; //THE ORDER OF BEST SCORE STORED IN INDEX.

        for (int j = 0; j < 70; j++) {
            selectString[i][j] = a[p][j];
        }
    }

    bestScore[0] = score[0];

    for (int i = 0; i < 70; i++) {
        bestString[0][i] = selectString[0][i];
    }

    while (counter < n) {
        for (int i = 0; i < 7; i = i + 2) {
            crossover(&a[i][0], &a[i + 1][0]);
        }

        for (int i = 0; i < 9; i++) {
            score[i] = 0;
        }

        for (int i = 0; i < 7; i++) {
            score[i] = calculate(&a[i][0]);
        }

        //CALCULATE FUNCTION RETURNS SCORE OF EACH STRING
        sortSelect();
        bestScore[counter] = score[0];
        int p = index[0];

        for (int j = 0; j < 70; j++) {
            bestString[counter][j] = a[p][j];
        }

        counter++;
    }

    //OUTPUT THE BEST SCORES.
    for (int p = 0; p < n; p++) {
        ui->txtResult->insertPlainText("The best score in the generation " + QString::number(p + 1) + ": " + QString::number(bestScore[p]) + "\n");
    }

    //OUTPUT THE BEST STRINGS.
    for (int i = 0; i < n; i++) {
        ui->txtResult->insertPlainText("\n\nThe best string in generation " + QString::number(i + 1) + " :\n\n");

        for (int j = 0; j < 70; j++) {
            if (j % 2 == 0 && j != 0) {
                ui->txtResult->insertPlainText(" ");
            }

            if (bestString[i][j] == 1) {
                ui->txtResult->insertPlainText("d");
            }
            //COVERTING 1’S AND 0’S TO d AND c
            else {
                ui->txtResult->insertPlainText("c");
            }
        }
    }

    //CALCULATING THE BEST OF THE BEST
    for (int i = 0; i < n; i++) {
        temp[i] = bestScore[i];
    }

    max = temp[0];

    for (int i = 1; i < n; i++) {
        if (max < temp[i]) {
            max = temp[i];
            ind = i;
        }
    }

    //CALCULATING THE BEST FROM THE SELECTED.
    ui->txtResult->insertPlainText("\n\n");
    ui->txtResult->insertPlainText("\nTHE BEST STRING IN ALL GENERATION IS\n\n");

    for (int i = 0; i < 70; i++) {
        if (i % 2 == 0 && i != 0) {
            ui->txtResult->insertPlainText(" ");
        }

        if (bestString[ind][i] == 1) {
            ui->txtResult->insertPlainText("d");
        } else {
            ui->txtResult->insertPlainText("c");
        }
    }

    ui->txtResult->insertPlainText("\n\nTHE CORRESPONDING BEST SCORE IS: " + QString::number(bestScore[ind]));
}

int PrisonerDilemma::calculate(int *ptr)
{
    int *a;

    int p1, p2;
    a = ptr;
    p1 = 0;
    p2 = 0;

    for (int i = 0; i < 70; i = i + 2) { //calculating the values according to truth table.
        if (a[i] == 1 && a[i + 1] == 1) {
            p1 = p1 + 3;
            p2 = p2 + 3;
        }

        if (a[i] == 1 && a[i + 1] == 0) {
            p1 = p1 + 5;
            p2 = p2 + 0;
        }

        if (a[i] == 0 && a[i + 1] == 1) {
            p1 = p1 + 0;
            p2 = p2 + 5;
        }

        if (a[i] == 0 && a[i + 1] == 0) {
            p1 = p1 + 1;
            p2 = p2 + 1;
        }
    }

    return (p1 + p2); //RETRUN THE TOTAL SCORE OF THE STRING.
}

void PrisonerDilemma::sortSelect() //ORDINARY SORTING PROCEDURE
{
    int temp[9];

    for (int i = 0; i < 10; i++) {
        temp[i] = score[i];
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 9; j >= i; j--) {
            if (temp[i] < temp[j]) { //USUSAL SWAPPING PROCEDURE.
                int t = temp[j];
                temp[j] = temp[i];
                temp[i] = t;
            }
        }
    }

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 10; j++) {
            if (temp[i] == score[j]) {
                index[i] = j;
            }
        }
    }

    score[0] = temp[0];
}

void PrisonerDilemma::crossover(int *ptr1, int *ptr2)
{
    int temp;

    int ind = qrand() % 61; //RANDOM POINT OF CROSSOVER

    for (int i = ind; i < 70; i++) {
        temp = ptr1[i];
        ptr1[i] = ptr2[i];
        ptr2[i] = temp;
    }
}
