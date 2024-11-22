#include "../include/LogLine.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

typedef struct {
  std::string origin_ip;
  int num_attempts;
  std::string port;
  std::string service;
} fail_sum;

void debug_print_LogLine(const LogLine& log);
void print_failed_logins(const std::vector<LogLine> logs);

int main(int argc, char** argv) {

  // TODO: implement distro agnostic filepath
  std::string filepath = "/var/log/secure";
  std::fstream log_file;
  log_file.open(filepath, std::ios::in);

  if (!log_file.is_open()) {
    std::cerr << "Error opening log file at " << filepath << "! (sudo?)" << std::endl;
  }

  // TESTING
  std::vector<LogLine> logs;
  std::string line;
  
  while (getline(log_file, line)) {
    LogLine log = LogLine(line);
    logs.push_back(log);
  }

  print_failed_logins(logs);

  // END TESTING


  log_file.close();
  return 0;

}

void debug_print_LogLine(const LogLine& log) {
  std::cout << "Timestamp:          " << log.get_timestamp()  << "\n";
  std::cout << "Hostname:           " << log.get_hostname()   << "\n";
  std::cout << "Service:            " << log.get_service()    << "\n";
  std::cout << "PID:                " << log.get_pid()        << "\n";
  std::cout << "Event Description:  " << log.get_event_desc() << "\n";
}

void print_failed_logins(const std::vector<LogLine> logs) {
  std::vector<fail_sum> fails;

  // This is not a good algorithm, high time complexity
  // TODO: fix
  bool found = false;
  for (auto& log : logs) {
    if (log.is_failed_login()) {
      for (auto& fail : fails) {
        if (fail.origin_ip == log.get_ip()) {
          fail.num_attempts++;
          found = true;
          break;
        }
      }
      // matching entry not found
      if (!found) {
        fail_sum new_fail;
        new_fail.num_attempts = 1;
        new_fail.origin_ip = log.get_ip();
        fails.push_back(new_fail);
      }
    }
  }

  std::cout << "Origin IP:\tNum Attempts:" << std::endl;
  for (auto fail : fails) {
    std::cout << fail.origin_ip << "\t" <<fail.num_attempts << "\n";
  }
}
