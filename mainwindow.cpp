#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortingalgorithm.h"
#include "QPainter"
#include <vector>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vc1 = SortingAlgorithm::random_vector(20);
    position = vector<int>({0, 0, 0, vc1.size(), 0});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1)
    {
        is_completed = SortingAlgorithm::sorting_Stepbystep(vc1, position, SortingAlgorithm::Bubble_Sort);

        update();

        if (is_completed)
        {
            killTimer(id1);
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);

    float x_startPosition = 10;
    float y_startPosition = 20;
    float bg_width = 480;
    float bg_height = 450;

    // 画背景
    painter.drawRect(x_startPosition, y_startPosition,
                     bg_width, bg_height);

    // 画条纹
    painter.setBrush(Qt::black);
    painter.setPen(Qt::red);

    float delta_x = 5;
    float delta_y = 10;

    int k;
    k = vc1.size();
    double step_lenth = (bg_width - delta_x * 2) / k;
    int vc1_max = 0;

    for (vector<int>::iterator i = vc1.begin(); i != vc1.end(); ++i)
    {
        if (vc1_max < *i)
        {
            vc1_max = *i;
        }
    }

    float y_step = (bg_height - delta_y) / vc1_max;

    for (unsigned int j = 0; j < vc1.size(); ++j)
    {
        int height = vc1[j];
        if (j == position[0] || j == position[1])
        {
            painter.setBrush(Qt::blue);
        }
        else
        {
            painter.setBrush(Qt::black);
        }
        float x = x_startPosition + delta_x + j * step_lenth;
        float y = y_startPosition + bg_height - y_step * height;
        painter.drawRect(x, y, step_lenth, y_step * height);
    }
}

void MainWindow::on_runBtn_clicked()
{
    id1 = startTimer(timer_period);
    this->isSorting = true;
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    data_size = value;
    ui->sizeLabel->setText(QString(value));
}

void MainWindow::on_resetBtn_clicked()
{
    vc1 = SortingAlgorithm::random_vector(20);
    position = vector<int>({0, 0, 0, vc1.size(), 0});
    update();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    timer_period = value;

    ui->period_label->setText(QString(value));
}
