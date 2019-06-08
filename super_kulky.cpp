#include "box.h"
#include "circle.h"
#include "generator.h"
#include "illegalargumentexception.h"
#include "super_kulky.h"
#include "options.h"
#include "toosmallrangeexception.h"
#include "super_kulky.h"
#include <QMessageBox>
#include <QtDebug>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTextItem>
#include <unistd.h>
#include <QThread>
#include <QTime>
#include <position.h>
#include <ui_mainwindow.h>

using namespace std;

SuperKulky::SuperKulky(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuperKulky) {
        ui->setupUi(this);
        initializeBoxes();
        connect(ui->resultSpin, SIGNAL(valueChanged(int)), this, SLOT(adjustResultScene(int)));
}

SuperKulky::~SuperKulky()
{
    delete ui;
}

void SuperKulky::spinnersEnabled(bool enabled)
{
    ui->ballSpin->setEnabled(enabled);
    ui->resultSpin->setEnabled(enabled);
    ui->toSpin->setEnabled(enabled);
    ui->fromSpin->setEnabled(enabled);
}

void SuperKulky::displayAlert(QString title)
{
    QMessageBox msgBox;
    msgBox.setText(title);
    msgBox.exec();
}

void SuperKulky::drawBoxWithLine()
{
    graphScene->clear();
    graphScene->items().clear();
    addLine();
}

void SuperKulky::on_startButton_clicked()
{
    Box box;
    unsigned int currentResultSize = 0;
    adjustResultScene(ui->resultSpin->value());

    try {
       box = Box(FIELD_SIZE, LINE_WIDTH, LINE_HEIGTH, generateBalls());
       launched = true;
       spinnersEnabled(!launched);
    } catch (IllegalArgumentException e) {
        displayAlert("Wybierz poprawny zakres liczb.");
    }
    catch (TooSmallRangeException e) {
        displayAlert("Wybierz większy zakres liczb.");
    }

    while(launched) {
           list<Ball> balls;
           for (int i = 0; i < D_POSITION; i++){
               balls = box.move();
               if(currentResultSize < box.getResult().size()) {
                   addNewResultBall(currentResultSize, box.getResult().back());
                   currentResultSize++;
               }
               if (currentResultSize == ui->resultSpin->value()){
                   launched = false;
                   break;
               }
           }
           drawBoxWithLine();
           drawBallsInBox(balls);

           delay();
       }
    spinnersEnabled(!launched);
    drawBoxWithLine();
}

std::list<Ball> SuperKulky::generateBalls()
{
    Options options = Options(
                ui->resultSpin->value(),
                ui->ballSpin->value(),
                ui->fromSpin->value(),
                ui->toSpin->value()
                );

    qDebug() << options;
    Generator g(FIELD_SIZE);
    g.setOptions(options);
    return g.generate();
}

void SuperKulky::addLine()
{
    int lineWidth = 100;
    int lineHeigth = 10;
    auto line = new QGraphicsRectItem(FIELD_SIZE - lineWidth, FIELD_SIZE - lineHeigth,
                                      lineWidth, lineHeigth);
    line->setBrush(Qt::red);
    graphScene->addItem(line);
}

void SuperKulky::addDrawBox()
{
    graphView = new QGraphicsView(ui->graphWidget);
    graphScene = new QGraphicsScene;
    graphScene->setSceneRect(0, 0, FIELD_SIZE, FIELD_SIZE);
    graphView->setScene(graphScene);
    graphView->show();

    addLine();
}

void SuperKulky::initializeBoxes()
{
    addDrawBox();
    addResultView(1);
}

void SuperKulky::on_resetButton_clicked()
{
    launched = false;
}

void SuperKulky::addResultView(int adj)
{
    resultView = new QGraphicsView(ui->resultWidget);
    resultScene = new QGraphicsScene;
    resultScene->setSceneRect(0, 0, RESULT_SIZE*adj, RESULT_SIZE);
    resultView->setScene(resultScene);
    resultView->show();
}

void SuperKulky::addNewResultBoxes(int adj)
{
    int lineWidth = 1;
    for (int i = 1; i < adj; i++){
            auto line = new QGraphicsRectItem(RESULT_SIZE*i, 0, lineWidth, RESULT_SIZE);
            line->setBrush(Qt::gray);
            resultScene->addItem(line);
    }
}

void SuperKulky::adjustResultScene(int adj)
{
    delete resultView;
    addResultView(adj);
    if (adj > 1) addNewResultBoxes(adj);
}
void SuperKulky::addNewResultBall(unsigned int currentResultSize, Ball ball)
{
    ball.setPosition(Position<double>(30 + currentResultSize*60,30));
    ball.setRadius(ball.getRadius() * 2 / 3);
    auto circle = new Circle(ball);
    resultScene->addItem(circle);
    auto text = resultScene->addText(QString::number(ball.getNumber()));
    circle->setText(text, true);
}

void SuperKulky::drawBallsInBox(list<Ball> balls)
{
    for (auto ball = balls.begin(); ball != balls.end(); ++ball){
        auto circle = new Circle(*ball);
        graphScene->addItem(circle);
        circle->setText(graphScene->addText(QString::number(ball->getNumber())), false);
    }
}

void SuperKulky::delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(1);
    while (QTime::currentTime() < dieTime) QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}
