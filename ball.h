#ifndef BALL_H
#define BALL_H
#include <position.h>
#include<iostream>
#include <qcolor.h>
#include <qdebug.h>
#include <type.h>
using namespace std;
class Ball
{
    double weight = 1;
    int radius = 1;
    int number;
    Type type;
    pair<double, double> velocityVector;
    Position<double> position;
    bool operator==(const Ball &b);
    bool operator!=(const Ball &b);
public:
    Ball();
    Ball(Position<double>, pair<int,int>, int, int);
    friend QDebug operator<<(QDebug debug, const Ball &b)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "Ball: position: " << b.position
                        << ", velocity: " << b.velocityVector
                        << ", radius: " << b.radius
                        << ", number: " << b.number;

        return debug;
    }
    void setNumber(int value);
    int getNumber() const;
    double getWeight() const;
    void setWeight(double value);
    int getRadius() const;
    void setRadius(int value);
    pair<double, double> getVelocityVector() const;
    void setVelocityVector(const pair<double, double> &value);
    Type getType() const;
    void setType(const Type &value);
    Position<double> getPosition() const;
    void setPosition(const Position<double> &value);
};

#endif // BALL_H
