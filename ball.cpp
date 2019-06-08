#include "ball.h"
#include <QRandomGenerator>

void Ball::setNumber(int value)
{
    number = value;
}

int Ball::getNumber() const
{
    return number;
}

double Ball::getWeight() const
{
    return weight;
}

void Ball::setWeight(double value)
{
    weight = value;
}


int Ball::getRadius() const
{
    return radius;
}

void Ball::setRadius(int value)
{
    radius = value;
}

pair<double, double> Ball::getVelocityVector() const
{
    return velocityVector;
}

void Ball::setVelocityVector(const pair<double, double> &value)
{
    velocityVector = value;
}

Type Ball::getType() const
{
    return type;
}

void Ball::setType(const Type &value)
{
    type = value;
}

Position<double> Ball::getPosition() const
{
    return position;
}

void Ball::setPosition(const Position<double> &value)
{
    position = value;
}

bool Ball::operator==(const Ball &b)
{
    if(this->number == b.number && this->position == b.position){
        return true;
    }
    return false;
}
bool Ball::operator!=(const Ball &b)
{
    if(this->position == b.position || this->number == b.number){
        return false;
    }
    return true;
}

Ball::Ball()
{

}

Ball::Ball(Position<double> position, pair<int, int> velocity, int number, int radius)
{
    this->position = position;
    this->velocityVector = velocity;
    this->number = number;
    this->radius = radius;
}


