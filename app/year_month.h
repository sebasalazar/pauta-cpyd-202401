#ifndef YEAR_MONTH_H
#define YEAR_MONTH_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <sstream>

class YearMonth {
public:
    YearMonth();
    YearMonth(int year, int month);
    YearMonth(const YearMonth& orig);
    virtual ~YearMonth();
    int GetMonth() const;
    int GetYear() const;
    int GetYearMonth() const;
    std::string toString() const;

    bool operator==(const YearMonth& other) const;
    bool operator!=(const YearMonth& other) const;
    bool operator<(const YearMonth& other) const;
    bool operator<=(const YearMonth& other) const;
    bool operator>(const YearMonth& other) const;
    bool operator>=(const YearMonth& other) const;
    YearMonth& operator=(const YearMonth& right);
private:
    int month;
    int year;
    void validate(int year, int month);
};

#endif /* YEAR_MONTH_H */

