#ifndef SUPERKULKY_H
#define SUPERKULKY_H

#include "ball.h"

#include <QMainWindow>
#include <qgraphicsview.h>

namespace Ui {
class SuperKulky;
}

class SuperKulky : public QMainWindow
{
    Q_OBJECT


public:
    explicit SuperKulky(QWidget *parent = nullptr);
    ~SuperKulky();

private slots:
    void on_startButton_clicked();
    void on_resetButton_clicked();
    void adjustResultScene(int);

private:
    const int FIELD_SIZE = 600;
    const int LINE_WIDTH = 100;
    const int LINE_HEIGTH = 5;
    const int RESULT_SIZE = 60;
    const int D_POSITION = 10;
    bool launched;
    Ui::SuperKulky *ui;
    QGraphicsView *graphView;
    QGraphicsScene *graphScene;
    QGraphicsView *resultView;
    QGraphicsScene *resultScene;
    std::list<Ball> generateBalls();
    void initializeBoxes();
    void addResultView(int);
    void addNewResultBoxes(int);
    void addDrawBox();
    void addNewResultBall(unsigned int, Ball);
    void addLine();
    void drawBallsInBox(list<Ball>);
    void delay();
    void spinnersEnabled(bool);
    void displayAlert(QString);
    void drawBoxWithLine();
};

#endif // SUPERKULKY_H
