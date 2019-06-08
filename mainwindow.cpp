#include "box.h"
#include "circle.h"
#include "generator.h"
#include "illegalargumentexception.h"
#include "mainwindow.h"
#include "options.h"
#include "toosmallrangeexception.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtDebug>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTextItem>
#include <unistd.h>
#include <QThread>
#include <QTime>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
        graphView = new QGraphicsView(ui->graphWidget);
        graphScene = new QGraphicsScene;
        graphScene->setSceneRect(0,0,600,600);
        graphView->setScene(graphScene);
        graphView->show();

        auto line = new QGraphicsRectItem(500, 590, 100, 10);
        line->setBrush(Qt::red);
        graphScene->addItem(line);

//        auto line = new QGraphicsRectItem(500, 590, 100, 10);
//        line->setBrush(Qt::red);
//        graphScene->addItem(line);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{

    launched = true;

    try {

       Box box(600, generateBalls());

       while(launched){
           auto balls = box.move();
                   graphScene->clear();
                   graphScene->items().clear();
                   auto line = new QGraphicsRectItem(500, 590, 100, 10);
                   line->setBrush(Qt::red);
                   graphScene->addItem(line);

                   for (auto ball = balls.begin(); ball != balls.end(); ++ball){
                       auto circle = new Circle(*ball);
                       graphScene->addItem(circle);
                       circle->setText(graphScene->addText(QString::number(ball->getNumber())));
                   }
                   QTime dieTime= QTime::currentTime().addMSecs(1);
                       while (QTime::currentTime() < dieTime)
                           QCoreApplication::processEvents(QEventLoop::AllEvents, 1);

       }


    } catch (IllegalArgumentException e) {
        QMessageBox msgBox;
        msgBox.setText("Wybierz poprawny zakres liczb.");
        msgBox.exec();
    }
    catch (TooSmallRangeException e) {
        QMessageBox msgBox;
        msgBox.setText("Wybierz większy zakres liczb.");
        msgBox.exec();
    }

}

std::list<Ball> MainWindow::generateBalls()
{
    Options options = Options(
                ui->resultSpin->value(),
                ui->ballSpin->value(),
                ui->fromSpin->value(),
                ui->toSpin->value()
                );

    qDebug() << options;
    Generator g;
    g.setOptions(options);
    return g.generate();
}

void MainWindow::on_resetButton_clicked()
{
    launched = false;
}
