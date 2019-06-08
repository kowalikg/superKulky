#include "box.h"
#include "circle.h"

#include <qgraphicsview.h>

Box::Box(int size, int lineWidth, int lineHeigth, std::list<Ball> balls)
{
    this->SIZE = size;
    this->LINE_WIDTH = lineWidth;
    this->LINE_HEIGTH = lineHeigth;
    this->balls = balls;
}

Box::Box()
{
    this->SIZE = 0;
    this->LINE_WIDTH = 0;
    this->LINE_HEIGTH = 0;
}
void Box::fillResult()
{
    for (auto ball = balls.begin(); ball != balls.end(); ++ball){
        if (ball->getPosition().getX() > SIZE - LINE_WIDTH
                && ball->getPosition().getY() + ball->getRadius() >= SIZE - LINE_HEIGTH){
            result.push_back(*ball);
            balls.erase(ball);
        }
    }
}

void Box::detectWalls()
{
    for (auto ball = balls.begin(); ball != balls.end(); ++ball){
        Position<double> oldPosition = ball->getPosition();
        std::pair<double, double> velocity = ball->getVelocityVector();

        if (oldPosition.getX() + ball->getRadius() + velocity.first >= SIZE ||
            oldPosition.getX() - ball->getRadius() + velocity.first <= 0) {
                ball->setVelocityVector(std::make_pair(-velocity.first, velocity.second));
        }

        velocity = ball->getVelocityVector();

        if (oldPosition.getY() + ball->getRadius() + velocity.second >= SIZE ||
            oldPosition.getY() - ball->getRadius() + velocity.second <= 0) {
                ball->setVelocityVector(std::make_pair(velocity.first, -velocity.second));
        }
    }
}

void Box::detectCollision()
{
    list<pair<Ball*, Ball*>> pairs = getPairs();
    for (auto pair = pairs.begin(); pair != pairs.end(); pair++){
        Ball* ball1 = pair->first;
        Ball* ball2 = pair->second;

        double distance = ball1->getPosition().newPosition(ball1->getVelocityVector()).distance(
                    ball2->getPosition().newPosition(ball2->getVelocityVector()));

        if (distance < ball1->getRadius() + ball2->getRadius()){
            collisionOccurred(ball1, ball2);
        }
    }
}

void Box::calculateNewPositions()
{
    for (auto ball = balls.begin(); ball != balls.end(); ++ball){
        ball->setPosition(ball->getPosition().newPosition(ball->getVelocityVector()));
    }
}

list<Ball> Box::move()
{
    fillResult();
    detectCollision();
    detectWalls();
    calculateNewPositions();

    return balls;
}
std::list<Ball> Box::getResult() const
{
    return result;
}

std::list<pair<Ball*, Ball*>> Box::getPairs()
{
    std::list<pair<Ball*, Ball*>> result;
        for(auto it1 = balls.begin(); it1 != balls.end(); it1++) {
            for(auto it2 = balls.begin(); it2 != it1; it2++) {
                    result.push_back(std::make_pair(&*it1, &*it2));
            }
        }
        return result;
}

void Box::collisionOccurred(Ball* ball1, Ball* ball2)
{
    std::pair<double, double> v1 = ball1->getVelocityVector();
    Position<double> s1 = ball1->getPosition();

    std::pair<double, double> v2 = ball2->getVelocityVector();
    Position<double> s2 = ball2->getPosition();

    double distance = s1.distance(s2);


    std::pair<double, double> un = std::make_pair((s2.getX() - s1.getX()) / distance,
                                                 (s2.getY() - s1.getY()) / distance);

    std::pair<double, double> ut = std::make_pair(-un.second, un.first);

    double v1n = un.first * v1.first + un.second * v1.second;
    double v1t = ut.first * v1.first + ut.second * v1.second;
    double v2n = un.first * v2.first + un.second * v2.second;
    double v2t = ut.first * v2.first + ut.second * v2.second;

    double v1np = (v1n * (ball1->getWeight() - ball2->getWeight()) + 2*ball2->getWeight() * v2n)
            / (ball1->getWeight() + ball2 ->getWeight());
    double v2np = (v2n * (ball2->getWeight() - ball1->getWeight()) + 2*ball1->getWeight() * v1n)
            / (ball1->getWeight() + ball2 ->getWeight());

    std::pair<double, double> v1nv = std::make_pair(v1np * un.first, v1np * un.second);
    std::pair<double, double> v1tv = std::make_pair(v1t * ut.first, v1t * ut.second);
    std::pair<double, double> v2nv = std::make_pair(v2np * un.first, v2np * un.second);
    std::pair<double, double> v2tv = std::make_pair(v2t * ut.first, v2t * ut.second);


    ball1->setVelocityVector(std::make_pair(v1nv.first + v1tv.first, v1nv.second + v1tv.second));
    ball2->setVelocityVector(std::make_pair(v2nv.first + v2tv.first, v2nv.second + v2tv.second));
}
