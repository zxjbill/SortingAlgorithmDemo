#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "sortingalgorithm.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void on_runBtn_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_resetBtn_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_stopBtn_clicked();

    void on_stepBtn_clicked();

private:
    Ui::MainWindow *ui;
    int id1, id2, id3;
    vector<int> vc1;
    vector<int> position;
    vector<int> red_position;
    vector<int> blue_position;
    vector<int> green_position;
    bool isSorting =false;
    bool is_completed = false;
    SortingAlgorithm::SortType now_sorting_type = SortingAlgorithm::SelectSort;
    int data_size = 20;
    int timer_period = 100;
    bool is_stop = false;
    void SelectColor();
    vector<int> colorful_position;
    vector<int> color_calculator(int index, int total);
};

#endif // MAINWINDOW_H
