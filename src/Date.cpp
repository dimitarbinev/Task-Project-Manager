#include "Date.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <tuple>

Date::Date() : day(1), month(1), year(2026) {
}

Date::Date(int day, int month, int year) {
    setDate(day, month, year);
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

bool Date::isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int Date::daysInMonth(int month, int year) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Month must be between 1 and 12.");
    }

    static const int daysPerMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (month == 2 && isLeapYear(year)) {
        return 29;
    }

    return daysPerMonth[month - 1];
}

void Date::setDate(int day, int month, int year) {
    if (year < 1900) {
        throw std::invalid_argument("Year must be at least 1900.");
    }

    if (month < 1 || month > 12) {
        throw std::invalid_argument("Month must be between 1 and 12.");
    }

    const int maxDay = daysInMonth(month, year);
    if (day < 1 || day > maxDay) {
        throw std::invalid_argument("Invalid day for the given month and year.");
    }

    this->day = day;
    this->month = month;
    this->year = year;
}

std::string Date::toString() const {
    std::ostringstream output;

    output << std::setw(2) << std::setfill('0') << day << "."
           << std::setw(2) << std::setfill('0') << month << "."
           << year;

    return output.str();
}

Date Date::today() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    if (localTime == nullptr) {
        throw std::runtime_error("Could not get current date.");
    }

    return Date(localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}

Date Date::parse(const std::string& text) {
    std::istringstream input(text);
    int day = 0;
    int month = 0;
    int year = 0;
    char firstDot = '\0';
    char secondDot = '\0';

    input >> day >> firstDot >> month >> secondDot >> year;

    if (!input || firstDot != '.' || secondDot != '.' || !input.eof()) {
        throw std::invalid_argument("Date must be in format dd.mm.yyyy.");
    }

    return Date(day, month, year);
}

bool Date::operator<(const Date& other) const {
    return std::tie(year, month, day) < std::tie(other.year, other.month, other.day);
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}
