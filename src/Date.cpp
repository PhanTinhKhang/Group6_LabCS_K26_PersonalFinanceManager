#include "../include/Date.h"
#include <iomanip>
#include <sstream>

bool Date::isLeapYear(int y){
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}
int Date::getDaysInMonth(int m, int y){
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(y) ? 29 : 28;
        default:
            return 0;
    }
}
Date::Date() : day(1), month(1), year(2026) {};
Date::Date(int d, int m, int y) {
    if (!setDate(d, m, y)) {
        day = 1;
        month = 1;
        year = 2026;
    }
}
bool Date::setDate(int d, int m, int y){
    if (y<1900 || y>2100) return false;
    if (m<1 || m>12) return false;
    if (d<1 || d>getDaysInMonth(m,y)) return false;

    day = d;
    month =m;
    year = y;
    return true;
}

int Date::getDay() const {return day;}
int Date::getMonth() const {return month;}
int Date::getYear() const {return year;}

bool Date::isBefore(const Date& other) const {
    if (year!= other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day< other.day;
}

bool Date::isEqual(const Date& other) const{
    return (day == other.day && month == other.month && year ==other.year);
}

bool Date::isInRange(const Date& from, const Date& to) const{
    return (from.isBefore(*this) || from.isEqual(*this)) && (this->isBefore(to) || this->isEqual(to));
}

bool Date::isSameMonth(const Date& other) const{
    return (year==other.year && month == other.month);
}

std::string Date::toString() const{
    std::ostringstream oss;
    oss << (day < 10? "0" : "") << day << "/" << (month < 10? "0" : "") << month << "/" << year;
    return oss.str();
}

Date Date::fromString(const std::string& str) {
    int d,m,y;
    char sep1, sep2;
    std::stringstream ss(str);
    if (ss >> d >> sep1 >> m >> sep2 >> y){
        if ((sep1 == '/' || sep1 == '-') && (sep2 == '/' || sep2 == '-')) {
            Date temp;
            if (temp.setDate(d, m ,y)) {
                return temp;
            }
        }
    }
    return Date(1,1,2026);
}

std::ostream& operator<< (std::ostream& os, const Date& dt) {
    os << dt.toString();
    return os;
}
