#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    id1 = startTimer(1000);
    id2 = startTimer(2000);
    id3 = startTimer(10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1)
    {
        ui->delayLabel->setText(tr("%1").arg(qrand()%10));
    }
    else if (event->timerId() == id2){
        ui->sizeLabel->setText(tr("hello world"));
    }
    else {
        qApp->quit();
    }
}
