#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ball.h"

#include <QMainWindow>
#include <qgraphicsview.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsView *graphView;
    QGraphicsScene *graphScene;
    std::list<Ball> generateBalls();
    bool launched;
};

#endif // MAINWINDOW_H
