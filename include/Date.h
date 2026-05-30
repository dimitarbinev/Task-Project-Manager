#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void setDate(int day, int month, int year);

    string toString() const;

    static Date today();
};

#endif