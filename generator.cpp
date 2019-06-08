#include "generator.h"
#include <random>
#include <cmath>

Generator::Generator(int fieldSize)
{
    this->fieldSize = fieldSize;
    this->options = Options();
}
Type Generator::types[] = {Type::FLUFF, Type::WOOD, Type::COPPER, Type::GOLD, Type::URAN};
void Generator::setOptions(const Options &value)
{
    options = value;
}

Ball Generator::newBall(int number, std::list<Ball> balls)
{
    Ball newBall;
    newBall.setNumber(number);
    newBall.setType(types[rand() % 5]);
    newBall.setRadius(rand() % 20 + 20);
    newBall.setWeight(getWeight(newBall.getType(), newBall.getRadius()));
    newBall.setPosition(generateFreePosition(newBall, balls));
    newBall.setVelocityVector(std::make_pair((rand() % 21 - 10) / 10.0, (rand() % 21 - 10) / 10.0));
    return newBall;
}

list<Ball> Generator::generate()
{
    srand(time(NULL));
    list<Ball> balls;
    auto numbers = generate_random_numbers();
    for (auto number = numbers.begin(); number != numbers.end(); number++){
        balls.push_back(newBall(*number, balls));
    }
    return balls;
}
unordered_set<int> Generator::generate_random_numbers(){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(options.getNumber_from(), options.getNumber_to()); // define the range

    unordered_set<int> numbers;
    while (numbers.size() < options.getBall_amount())
    {
        numbers.insert(distr(eng));
    }
    return numbers;
}

Position<double> Generator::generateFreePosition(Ball newBall, list<Ball> balls)
{
    bool selected = false;
    bool isOnThisPlace = false;
    int i = 0;
    while(!selected){
        i++;
        double newX = randomCoordinate(newBall.getRadius());
        double newY = randomCoordinate(newBall.getRadius());
        Position<double> newPosition = Position<double>(newX, newY);
        for (auto ball = balls.begin(); ball != balls.end(); ball++){
            if (newPosition.distance(ball->getPosition()) < newBall.getRadius() + ball->getRadius()){
                isOnThisPlace = true;
                break;
            }
        }
        if (!isOnThisPlace) {
            selected = true;
            return newPosition;
        }
        isOnThisPlace = false;
    }
    return Position<double>();
}

double Generator::getWeight(Type type, int radius)
{
    return 4 / 3 * pow(radius, 3) * type;
}

double Generator::randomCoordinate(int radius)
{
    return rand() % ((fieldSize - 50) - 2 * radius) + radius;
}


