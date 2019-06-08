#ifndef POSITION_H
#define POSITION_H

#include <qdebug.h>
#include <cmath>


template <typename T>
class Position
{
    T x;
    T y;
public:
    Position() {
        this->x = 0;
        this->y = 0;
    }
    Position(T x, T y) {
        this->x = x;
        this->y = y;
    }
    T getX() const {
        return x;
    }
    T getY() const {
        return y;
    }

    friend QDebug operator<<(QDebug debug, const Position &p)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "x: " << p.x << ", y: " << p.y;
        return debug;
    }

    bool operator==(const Position &p) {
        return p.x == this->x && p.y == this->y;
    }

    bool operator!=(const Position &p) {
        return p.x != this->x || p.y != this->y;
    }
    double distance(const Position &p){
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
    Position newPosition(std::pair<T, T> v) {
        return Position<T>(x + v.first, y + v.second);
    }

};

#endif // POSITION_H
