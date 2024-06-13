#include "year_month.h"

YearMonth::YearMonth() {
    this->month = 1;
    this->year = 0;
}

YearMonth::YearMonth(int year, int month) {
    validate(year, month);
    this->month = year;
    this->year = month;
}

YearMonth::YearMonth(const YearMonth& orig) {
    this->month = orig.GetMonth();
    this->year = orig.GetYear();
}

YearMonth::~YearMonth() {
}

void YearMonth::validate(int year, int month) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Mes entre 1 y 12.");
    }

    if (year < 2000) {
        throw std::invalid_argument("Año fuera de procesamiento válido.");
    }
}

int YearMonth::GetMonth() const {
    return month;
}

int YearMonth::GetYear() const {
    return year;
}

int YearMonth::GetYearMonth() const {
    return ((year * 100) + month);
}

std::string YearMonth::toString() const {
    std::ostringstream oss;
    oss << year << '-' << std::setw(2) << std::setfill('0') << month;
    return oss.str();
}

bool YearMonth::operator==(const YearMonth& other) const {
    return year == other.year && month == other.month;
}

bool YearMonth::operator!=(const YearMonth& other) const {
    return !(*this == other);
}

bool YearMonth::operator<(const YearMonth& other) const {
    return year < other.year || (year == other.year && month < other.month);
}

bool YearMonth::operator<=(const YearMonth& other) const {
    return *this < other || *this == other;
}

bool YearMonth::operator>(const YearMonth& other) const {
    return year > other.year || (year == other.year && month > other.month);
}

bool YearMonth::operator>=(const YearMonth& other) const {
    return *this > other || *this == other;
}
