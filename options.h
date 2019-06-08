#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDebugStateSaver>
#include <qstring.h>



class Options
{
    int result_amount;
    int ball_amount;
    int number_from;
    int number_to;
public:
    Options();
    Options(int, int, int, int);
    int getResult_amount() const;
    int getBall_amount() const;
    int getNumber_from() const;
    int getNumber_to() const;
    friend QDebug operator<<(QDebug debug, const Options &o)
    {
        QDebugStateSaver saver(debug);
        debug.nospace() << "Options: result: " << o.result_amount
                        << ", ball: " << o.ball_amount
                        << ", from: " << o.number_from
                        << ", to: " << o.number_to;

        return debug;
    }
};


#endif // OPTIONS_H
