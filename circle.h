#ifndef CIRCLE_H
#define CIRCLE_H

#include "ball.h"

#include <QPaintEvent>
#include <qgraphicsitem.h>

#include <QBrush>
#include <QColor>
#include <QRandomGenerator>


class Circle : public QGraphicsEllipseItem
{
    QGraphicsTextItem* text;
    Ball ball;

public:
    Circle(Ball ball) : QGraphicsEllipseItem(ball.getPosition().getX() - ball.getRadius()
                                             , ball.getPosition().getY() - ball.getRadius(),
                                             2 * ball.getRadius(), 2* ball.getRadius()) {
        this->ball = ball;
        this->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
        QColor color;
        switch (ball.getType()){
            case FLUFF : color = QColor::fromRgb(220, 255, 251); break;
            case WOOD: color = QColor::fromRgb(209, 195, 183); break;
            case COPPER: color = QColor::fromRgb(218, 138, 103); break;
            case GOLD: color = QColor::fromRgb(232, 191, 139); break;
            default: color = QColor::fromRgb(207,207,196); break;

        }
        this->setBrush(QBrush(color));

    }
    void setText(QGraphicsTextItem*, bool);
};

#endif // CIRCLE_H
