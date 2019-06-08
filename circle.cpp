#include "circle.h"

#include <QFont>

void Circle::setText(QGraphicsTextItem *value, bool result = false)
{
    text = value;
    QFont qfont = QFont();

    if(result){
       qfont.setPixelSize(this->ball.getRadius() * 2 / 3);
    }
    else {
       qfont.setPixelSize(this->ball.getRadius() / 2);
    }

    text->setFont(qfont);
    text->setPos(this->ball.getPosition().getX() - (this->ball.getRadius() / 2),
                 this->ball.getPosition().getY() - (this->ball.getRadius() / 2)) ;
}
