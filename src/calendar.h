#ifndef _calendar_h
#define _calendar_h

#include <string>
#include <ostream>
#include "map.h"

/*
 * We couldn't use enums b/c they screw-up ++ and -- operations in implementaion
enum Month {
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};
*/

// we made it short b/c we want to overload the Date() constructor
// and that can't happen if both versions have the same signature
typedef short Month;

const Month JANUARY=1;
const Month FEBRUARY=2;
const Month MARCH=3;
const Month APRIL=4;
const Month MAY=5;
const Month JUNE=6;
const Month JULY=7;
const Month AUGUST=8;
const Month SEPTEMBER=9;
const Month OCTOBER=10;
const Month NOVEMBER=11;
const Month DECEMBER=12;

class Date {
public:
    Date();
    Date(Month month, int day, int year);
    Date(int day, Month month, int year);

    int daysInMonth();
    bool isLeapYear();

    int getDay() const;
    Month getMonth() const;
    int getYear() const;

    std::string toString() const;

    Date operator+(int days);
    Date operator-(int days);
    int operator-(const Date & c);

    void operator+=(int days);
    void operator-=(int days);

    // pre-increment
    Date operator++();
    // post-increment
    Date operator++(int);

    Date operator--();
    Date operator--(int);

private:
    friend bool operator==(const Date & c1, const Date & c2);
    friend bool operator!=(const Date & c1, const Date & c2);

    friend bool operator<(const Date & c1, const Date & c2);
    friend bool operator<=(const Date & c1, const Date & c2);
    friend bool operator>(const Date & c1, const Date & c2);
    friend bool operator>=(const Date & c1, const Date & c2);

    int day;
    Month month;
    int year;

    Map<Month, std::string> MONTH_2_STR;

    /**
     * Private helper methods
     */
    void initDate(int day, Month month, int year);
    friend Date addDaysToDate(const Date & date, int days);
};

std::ostream & operator<<(std::ostream & os, const Date & c);

bool operator==(const Date & c1, const Date & c2);
bool operator!=(const Date & c1, const Date & c2);

bool operator<(const Date & c1, const Date & c2);
bool operator<=(const Date & c1, const Date & c2);
bool operator>(const Date & c1, const Date & c2);
bool operator>=(const Date & c1, const Date & c2);

#endif
