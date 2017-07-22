#include "calendar.h"
#include "strlib.h"

Date addDaysToDate(const Date & date, int days);

Date::Date() {
    initDate(1, JANUARY, 1990);
}

Date::Date(int day, Month month, int year) {
    initDate(day, month, year);
}

Date::Date(Month month, int day, int year) {
    initDate(day, month, year);
}

void Date::initDate(int day, Month month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;

    MONTH_2_STR[JANUARY] = "Jan";
    MONTH_2_STR[FEBRUARY] = "Feb";
    MONTH_2_STR[MARCH] = "Mar";
    MONTH_2_STR[APRIL] = "Apr";
    MONTH_2_STR[MAY] = "May";
    MONTH_2_STR[JUNE] = "Jun";
    MONTH_2_STR[JULY] = "Jul";
    MONTH_2_STR[AUGUST] = "Aug";
    MONTH_2_STR[SEPTEMBER] = "Sep";
    MONTH_2_STR[OCTOBER] = "Oct";
    MONTH_2_STR[NOVEMBER] = "Nov";
    MONTH_2_STR[DECEMBER] = "Dec";
}

int Date::daysInMonth() {
    switch (month) {
    case FEBRUARY: return isLeapYear() ? 29 : 28;

    case SEPTEMBER:
    case APRIL:
    case JUNE:
    case NOVEMBER:
        return 30;

    default:
        return 31;
    }
}

bool Date::isLeapYear() {
    if (year % 4 != 0)
        return false;
    if (year % 100 != 0)
        return true;
    if (year % 400 == 0)
        return true;
    return false;
}

int Date::getDay() const {
    return day;
}

Month Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

std::string Date::toString() const {
    return integerToString(day) + "-" +
            MONTH_2_STR[month] + "-" +
            integerToString(year);
}

Date Date::operator+(int days) {
    return addDaysToDate(*this, days);
}

Date Date::operator-(int days) {
    return addDaysToDate(*this, -1 * days);
}

int Date::operator-(const Date & other) {
    int duration = 0;
    Date furthur, closer;

    if (*this == other) {
        return 0;
    } else if (*this > other) {
        furthur = *this;
        closer = other;
    } else {
        furthur = other;
        closer = *this;
    }

    while(closer++ < furthur) {
        duration++;
    }

    return duration;
}

void Date::operator+=(int days) {
    *this = addDaysToDate(*this, days);
}

void Date::operator-=(int days) {
    *this = addDaysToDate(*this, -1 * days);
}

Date Date::operator++() {
    *this = addDaysToDate(*this, 1);
    return *this;
}

Date Date::operator++(int) {
    Date save = *this;
    *this = addDaysToDate(*this, 1);
    return save;
}

Date Date::operator--() {
    *this = addDaysToDate(*this, -1);
    return *this;
}

Date Date::operator--(int) {
    Date save = *this;
    *this = addDaysToDate(*this, -1);
    return save;
}

std::ostream & operator<<(std::ostream & os, const Date & c) {
    return os << c.toString();
}

bool operator==(const Date & c1, const Date & c2) {
    return (c1.day == c2.day) &&
            (c1.month == c2.month) &&
            (c1.year == c2.year);
}

bool operator!=(const Date & c1, const Date & c2) {
    return !(c1 == c2);
}

bool operator<(const Date & c1, const Date & c2) {
    return (c1.year < c2.year) ||
            (c1.month < c2.month) ||
            (c1.day < c2.day);
}

bool operator<=(const Date & c1, const Date & c2) {
    return (c1 == c2) || (c1 < c2);
}

bool operator>(const Date & c1, const Date & c2) {
    return (c1.year > c2.year) ||
            (c1.month > c2.month) ||
            (c1.day > c2.day);
}

bool operator>=(const Date & c1, const Date & c2) {
    return (c1 == c2) || (c1 > c2);
}

Date addDaysToDate(const Date & date, int days) {
    Date new_date = date;
    if (days >= 0) {
        while (days-- > 0) {
            new_date.day++;
            if (new_date.day > new_date.daysInMonth()) {
                new_date.day = 1;
                if (++new_date.month > DECEMBER) {
                    new_date.month = JANUARY;
                    new_date.year++;
                }
            }
        }
    } else {
        days = abs(days);
        while (days-- > 0) {
            if (--new_date.day == 0) {
                if (--new_date.month < JANUARY) {
                    new_date.month = DECEMBER;
                    new_date.year--;
                }
                new_date.day = new_date.daysInMonth();
            }

        }
    }

    return new_date;
}
