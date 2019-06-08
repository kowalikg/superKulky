#ifndef BOX_H
#define BOX_H

#include "ball.h"

#include <qgraphicsscene.h>

class Box
{
    int SIZE;
    int LINE_WIDTH;
    int LINE_HEIGTH;
    std::list<Ball> balls;
    std::list<Ball> result;
    bool checkIfFree(int x, int y, int r);
    void collisionOccurred(Ball*, Ball*);
public:
    Box(int, int, int, std::list<Ball>);
    Box();
    list<Ball> move();
    std::list<Ball> getResult() const;


    void detectCollision();

private:
    bool isYHit(int x, int y, int r);
    std::list<std::pair<Ball *, Ball *> > getPairs();
    void fillResult();
    void detectWalls();
    void calculateNewPositions();
};

#endif // BOX_H
