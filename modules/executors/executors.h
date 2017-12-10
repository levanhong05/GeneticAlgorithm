#ifndef EXECUTORS_H
#define EXECUTORS_H

#include <QList>
#include <QObject>
#include <QDockWidget>
#include <QDirIterator>

#include "executors_global.h"

#include "executors.h"
#include "runlogwidget.h"

#include "console.h"
#include "executor.h"
#include "workcase.h"

#include "waitingdialog.h"

namespace GeneticAlgorithm {

typedef struct ExecutingJob{
    ExecutingJob(QString title, QWidget *parent = 0);
    QString title;
    QDockWidget *dock;
    RunLogWidget *logWidget;

    Executor *exec;
    bool beginWrite;
} ExecutingJob;

class EXECUTORSSHARED_EXPORT Executors : public QObject
{
    Q_OBJECT
public:
    Executors(QObject *parent = 0);

public slots:
    void execWordNet(QString grammar, QString wordnet);

private slots:
    void onErrorLogging(QString);

    void onResultLogging(QString result);

    void onTestLogging(QString result);

signals:
    void sentenceDetect(QString sentence);

private:
    QString shortPathName(const QString &file);

    bool removeDir(QString dirName);

    void scanDir(QString dirName, QString dst = "wave");

private:
    QList<ExecutingJob *> _jobs;

    WaitingDialog *_wait;
    bool _isWrite;
};

extern Executors EXECUTORSSHARED_EXPORT executors;

}

#endif // EXECUTORS_H
