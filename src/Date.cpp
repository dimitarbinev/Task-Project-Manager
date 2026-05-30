#include "../include/Date.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

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

void Date::setDate(int day, int month, int year) {
    if (year < 1900) {
        throw std::invalid_argument("Year must be at least 1900.");
    }

    if (month < 1 || month > 12) {
        throw std::invalid_argument("Month must be between 1 and 12.");
    }

    if (day < 1 || day > 31) {
        throw std::invalid_argument("Day must be between 1 and 31.");
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

    return Date(
        localTime->tm_mday,
        localTime->tm_mon + 1,
        localTime->tm_year + 1900
    );
}