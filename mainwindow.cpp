#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortingalgorithm.h"
#include "QPainter"
#include <vector>
#include <QDebug>
#include "stdlib.h"
#include <QDebug>
#include <algorithm>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    now_sorting_type = SortingAlgorithm::Select_Sort;
    ui->setupUi(this);
    vc1 = SortingAlgorithm::random_vector(20);
    qDebug() << vc1.size();
    red_position.clear();
    blue_position.clear();
    green_position.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1)
    {
        is_completed = SortingAlgorithm::sorting_Stepbystep(vc1, position, now_sorting_type);

        update();

        if (is_completed)
        {
            killTimer(id1);
        }
    }

    if (is_stop)
    {
        killTimer(id1);
        is_stop = false;
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
    painter.setPen(Qt::black);

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

    for (int j = 0; j < int(vc1.size()); ++j)
    {
        int height = vc1[j];
        bool is_change_color = false;

        this->SelectColor();
        // 设置绘制条状的色彩
        for (auto p_iter = blue_position.begin(); p_iter != blue_position.end(); p_iter++)
        {
            if (*p_iter == j)
            {
                painter.setBrush(Qt::blue);
                painter.setPen(Qt::blue);
                is_change_color = true;
                break;
            }
        }

        for (auto p_iter = red_position.begin(); p_iter != red_position.end(); p_iter++)
        {
            if (*p_iter == j)
            {
                painter.setBrush(Qt::blue);
                painter.setPen(Qt::blue);
                is_change_color = true;
                break;
            }
        }

        for (auto p_iter = green_position.begin(); p_iter != green_position.end(); p_iter++)
        {
            if (*p_iter == j)
            {
                painter.setBrush(Qt::green);
                painter.setPen(Qt::green);
                is_change_color = true;
                break;
            }
        }

        if (!is_change_color)
        {
            painter.setBrush(Qt::black);
            painter.setPen(Qt::black);
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

    switch (now_sorting_type) {
    case SortingAlgorithm::Bubble_Sort:
        position = vector<int>({0, 0, 0, int(vc1.size()), 0});
        break;
    case SortingAlgorithm::Select_Sort:
        position = vector<int>({0, 0, 1, -1});
        break;
    default:
        break;
    }
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    data_size = value;
    char *size_s = new char[3];
    itoa(value, size_s, 10);
    ui->sizeLabel->setText(size_s);
    delete size_s;
}

void MainWindow::on_resetBtn_clicked()
{
    vc1 = SortingAlgorithm::random_vector(data_size);
    position = vector<int>({0, 0, 0, int(vc1.size()), 0});
    update();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    timer_period = value;
    char *period_s = new char[4];
    itoa(value, period_s, 10);
    ui->period_label->setText(period_s);
    delete period_s;
}

void MainWindow::on_stepBtn_clicked()
{
    is_stop = true;
}

void MainWindow::SelectColor()
{
    if (position.size() < 3)
    {
        return;
    }

    switch (now_sorting_type) {
    case SortingAlgorithm::Bubble_Sort:
        blue_position.clear();
        red_position.clear();
        green_position.clear();
        red_position.push_back(position[0]);
        red_position.push_back(position[1]);
        break;
    case SortingAlgorithm::Select_Sort:
        blue_position.clear();
        red_position.clear();
        green_position.clear();
        blue_position.push_back(position[0]);
        red_position.push_back(position[2]);
        green_position.push_back(position[3]);
        break;
    default:
        break;
    }
}
