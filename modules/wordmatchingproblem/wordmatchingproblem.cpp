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
    int i, choice;

    getInput();
    initialPop();

    //display();
    reproduction(); //sorting_based_on_fitness();
    display();

    printf("\nENTER YOUR CHOICE (TO CONTINUE 1 TO EXIT 0) : ");

    scanf("%d", &choice);

    while ((choice == 1) && (pfit[0] != strlen(input))) {
        crossover();
        gen++;
        mutation();
        reproduction(); //sorting_based_on_fitness();
        display();
        choice = inputChoice();
    }

    results();
}

void WordMatchingProblem::getInput()
{
    printf("\n\n\n\t\tWORD MATCHING PROBLEM");
    printf("\n\t **************************************");
    printf("\n\n\n\n\t\tENTER THE WORD TO BE MATCHED : ");
    scanf("%s", input);
    printf("\n\n\n\t THE ASCII EQUIVALENT OF THE LETTERS IN THE ENTERED WORD");
    printf("\n\t------- ------- ------- ");
    printf("\n\n LETTERS :");

    for (int i = 0; i < strlen(input); i++) {
        printf(" %c ", input[i]);
    }

    printf("\n ASCII :");

    for (int i = 0; i < strlen(input); i++) {
        printf(" %3d", input[i]);
    }
}

void WordMatchingProblem::initialPop()
{
    int i, j;
    randomize();

    for (i = 0; i < 50; i++) {
        for (j = 0; j < strlen(input); j++) {
            parent[i][j] = random(26) + 97;

            if (parent[i][j] == input[j]) {
                pfit[i]++;
            }
        }
    }
}

void WordMatchingProblem::display()
{
    int i, j, nexti;
    clrscr();
    printf("\n\n\t\t THE CHROMOSOMES OF PARENTS AND CHILDREN");
    printf("\n\t---- ------ ------- --\n");
    printf("\n\t\t PREVIOUS GENERATION CHILDREN CHROMOSOMES\n\n");

    for (i = 0; i < 50; i++) {
        if (((i) % 4) == 0) {
            printf("\n");
        }

        for (j = 0; j < strlen(input); j++) {
            printf("%c", child[i][j]);
        }

        printf("% 2d ", cfit[i]);
    }

    printf("\n\t\t\tMUTANTS OF THIS GENERATION\n");

    for (i = 0; i < 05; i++) {
        if (i == 3) {
            printf("\n");
        }

        for (j = 0; j < strlen(input); j++) {
            printf("%c", mutant[i][j]);
        }

        printf("% 2d ", mfit[i]);
    }

    getch();
    clrscr();
    printf("\n\n\t\t THE CHROMOSOMES OF PARENTS AND CHILDREN");
    printf("\n\t---- ------ ------\n");
    printf("\n\t\t NEXT GENERATION PARENTS CHROMOSOMES\n\n");

    for (i = 0; i < 50; i++) {
        if (((i) % 4) == 0) {
            printf("\n");
        }

        for (j = 0; j < strlen(input); j++) {
            printf("%c", parent[i][j]);
        }

        printf("% 2d ", pfit[i]);
    }

    getch();
}

void WordMatchingProblem::reproduction() //sorting_based_on_fitness()
{
    char tempc;
    int temp;
    int i, j, k;

    for (i = 0; i < 50; i++) {
        for (j = 0; j < strlen(input); j++) {
            mating_pool[i][j] = parent[i][j];
            fit[i] = pfit[i];
        }
    }

    for (i = 50; i < 100; i++) {
        for (j = 0; j < strlen(input); j++) {
            mating_pool[i][j] = child[i - 50][j];
            fit[i] = cfit[i - 50];
        }
    }

    for (i = 100; i < 105; i++) {
        for (j = 0; j < strlen(input); j++) {
            mating_pool[i][j] = mutant[i - 100][j];
            fit[i] = mfit[i - 100];
        }
    }

//sorting
    for (i = 0; i < 105; i++) {
        for (j = i + 1; j < 105; j++) {
            if (fit[i] < fit[j]) {
                for (k = 0; k < strlen(input); k++) {
                    tempc = mating_pool[i][k];
                    mating_pool[i][k] =
                        mating_pool[j][k];
                    mating_pool[j][k] = tempc;
                    temp = fit[i];
                    fit[i] = fit[j];
                    fit[j] = temp;
                }
            }
        }
    }

    for (i = 0; i < 50; i++) {
        for (j = 0; j < strlen(input); j++) {
            parent[i][j] = mating_pool[i][j];
            pfit[i] = fit[i];
        }
    }

    for (i = 50; i < 100; i++) {
        for (j = 0; j < strlen(input); j++) {
            child[i - 50][j] = mating_pool[i][j];
            cfit[i - 50] = fit[i];
        }
    }
}

void WordMatchingProblem::crossover()
{
    int xover_pt;
    int i, j, k;

    for (i = 0; i < 50; i++) {
        xover_pt = random(strlen(input));
        cfit[i] = 0;
        cfit[i + 1] = 0;

        for (j = 0; j < xover_pt; j++) {
            child[i][j] = parent[i][j];

            if (input[j] == child[i][j]) {
                cfit[i]++;
            }

            child[i + 1][j] = parent[i + 1][j];

            if (input[j] == child[i + 1][j]) {
                cfit[i + 1]++;
            }
        }

        for (j = xover_pt; j < strlen(input); j++) {
            child[i][j] = parent[i + 1][j];

            if (input[j] == child[i][j]) {
                cfit[i]++;
            }

            child[i + 1][j] = parent[i][j];

            if (input[j] == child[i + 1][j]) {
                cfit[i + 1]++;
            }
        }

        i++;
    }
}

void WordMatchingProblem::mutation()
{
    int i, mut_pt, j;
    char mut_val;
    randomize();

    for (i = 0; i < 05; i++) {
        mut_pt = random(strlen(input));
        mut_val = random(26) + 97;
        mfit[i] = 0;

        for (j = 0; j < mut_pt; j++) {
            mutant[i][j] = parent[1][j];

            if (mutant[i][j] == input[j]) {
                mfit[i]++;
            }
        }

        mutant[i][mut_pt] = mut_val;

        if (mutant[i][j] == input[j]) {
            mfit[i]++;
        }

        for (j = mut_pt + 1; j < strlen(input); j++) {
            mutant[i][j] = parent[1][j];

            if (mutant[i][j] == input[j]) {
                mfit[i]++;
            }
        }
    }
}

void WordMatchingProblem::results()
{
    int i;
    clrscr();
    printf("\n\n\n\t\tWORD MATCHING PROBLEM ");
    printf("\n\t ****************************************");
    printf("\n\n\n\t\t THE MATCHING WORD FOR THE GIEN INPUT WORD");
    printf("\n\n\t\t OBTAINED USING GENETIC ALGORITHM");
    printf("\n\n\t\t\t ");

    for (i = 0; i < strlen(input); i++) {
        printf("%c", parent[0][i]);
    }

    printf("\n\t\t\t –");

    for (i = 0; i < strlen(input); i++) {
        printf("-");
    }

    printf("–\n\n\n\t\t USER INPUT : %s", input);
    printf("\n\n\n\t THE FITNESS OF THE GA GENERATED WORD AND THE USER’S INPUT");
    printf("\n\n\t\t\t\t %2d/%d", pfit[0], strlen(input));
    printf("\n\n\n\t\t\t GENERATIONS COUNT : %d", gen);
}

int WordMatchingProblem::inputChoice()
{
    int choice, i;
    clrscr();
    printf("\n\n\n\n\t\t\t GENEREATION NUMBER : %d", gen);
    printf("\n\t\t –––––––––––––––");
    printf("\n\n\n\t\tTHE FITTEST INDIVIDUAL TILL THE PREVIOUS GENERATION\n\n\n\t\t\t\t");

    for (i = 0; i < strlen(input); i++) {
        printf("%c", parent[0][i]);
    }

    printf(" / ");

    for (i = 0; i < strlen(input); i++) {
        printf("%c", input[i]);
    }

    printf("\n\n\n\t\t\t WITH A FITNESS OF %d/%d", pfit[0], strlen(input));
    printf("\n\n\n\n\t\tENTER YOUR CHOICE (TO CONTINUE 1 TO EXIT 0) : ");
    scanf("%d", &choice);
    return choice;
}
