#ifndef GENERATOR_H
#define GENERATOR_H

#include "ball.h"
#include "options.h"

#include <unordered_set>

class Generator
{   
private:
Options options;
unordered_set<int> generate_random_numbers();
int fieldSize;
static Type types[];
Ball newBall(int, list<Ball>);
Position<double> generateFreePosition(Ball, list<Ball>);
double getWeight(Type, int);
double randomCoordinate(int);
public:
Generator(int);
void setOptions(const Options &value);
list<Ball> generate();
};


#endif // GENERATOR_H
