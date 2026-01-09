#include "date_checker.h"

// Array of days in each month for non-leap years
static const int days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

bool is_leap_year(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int get_days_in_month(int month, int year) {
    if (month < 1 || month > 12) return -1; // Invalid month
    if (month == 2 && is_leap_year(year)) return 29;
    return days_in_month[month - 1];
}
