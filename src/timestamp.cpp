#include "../include/timestamp.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>

std::tm parse_timestamp(const std::string& timestamp) {

  std::tm tm = {};
  std::istringstream ss(timestamp);

  ss >> std::get_time(&tm, "%b %d %H:%M:%S");
  if (ss.fail()) {
    throw std::runtime_error("Failed to parse timestamp");
  }

  std::time_t t = std::time(nullptr);
  std::tm* current_tm = std::localtime(&t);
  // This just assumes the log is in the current year. TODO fix
  // Sounds like a problem for January :D
  // Maybe check if the date is later than the current date? 
  tm.tm_year = current_tm->tm_year;

  return tm;
} 

bool is_time_equal(const std::tm& lhs, const std::tm& rhs) {
  std::time_t time1 = std::mktime(const_cast<std::tm*>(&lhs));
  std::time_t time2 = std::mktime(const_cast<std::tm*>(&rhs));

  return time1 == time2;
}

// Returns true if lhs is earlier than rhs
bool is_earlier_time(const std::tm& lhs, const std::tm& rhs) {
  std::time_t time1 = std::mktime(const_cast<std::tm*>(&lhs));
  std::time_t time2 = std::mktime(const_cast<std::tm*>(&rhs));

  return time1 < time2;
}
