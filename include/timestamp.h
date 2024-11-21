#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <string>
#include <ctime>

std::tm parse_timestamp(const std::string& timestamp);
bool is_time_equal(const std::tm& lhs, const std::tm& rhs);
bool is_earlier_time(const std::tm& lhs, const std::tm& rhs);

#endif
