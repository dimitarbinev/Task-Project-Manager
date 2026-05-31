#ifndef DATE_H
#define DATE_H

#include <string>

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

    std::string toString() const;

    static Date today();
    static Date parse(const std::string& text);
    static bool isLeapYear(int year);
    static int daysInMonth(int month, int year);

    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
};

#endif
