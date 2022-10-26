#include "../include/date.h"

Date createDate(int day, int month, int year) {

    Date date;

    date.day = day;
    date.month = month;
    date.year = year;

    return date;
}