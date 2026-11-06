#ifndef DATE_H
#define DATE_H
#include <string>
#include <iostream>
class Date {
private:
    int day, month, year;
    
public:
    Date();
    Date(int d, int m, int y);
    static bool isLeapYear(int y);
    static int getDaysInMonth(int m, int y);
    
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool setDate(int d, int m, int y);
    bool isEqual(const Date& other) const;
    bool isBefore(const Date& other) const;
    bool isInRange(const Date& from, const Date& to) const;

    bool isSameMonth(const Date& other) const;

    std::string toString() const;
    static Date fromString(const std::string& str);

};
std::ostream& operator<<(std::ostream& os, const Date& dt);

#endif