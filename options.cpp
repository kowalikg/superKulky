#include "illegalargumentexception.h"
#include "options.h"
#include "toosmallrangeexception.h"
#include <QtDebug>


int Options::getBall_amount() const
{
    return ball_amount;
}

int Options::getNumber_from() const
{
    return number_from;
}

int Options::getNumber_to() const
{
    return number_to;
}



Options::Options()
{

}

Options::Options(int result_amount, int ball_amount, int number_from, int number_to)
{
    if (number_from > number_to) throw IllegalArgumentException();
    if (ball_amount > number_to - number_from + 1) throw TooSmallRangeException();
    if (result_amount > ball_amount) throw IllegalArgumentException();
    this->result_amount = result_amount;
    this->ball_amount = ball_amount;
    this->number_from = number_from;
    this->number_to = number_to;
}

int Options::getResult_amount() const
{
    return result_amount;
}

