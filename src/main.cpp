#include "../include/LogLine.h"
#include <iostream>
#include <string>
#include <fstream>

void debug_print_LogLine(const LogLine& log);

int main(int argc, char** argv) {

  // TODO: implement distro agnostic filepath
  std::string filepath = "/var/log/secure";
  std::fstream log_file;
  log_file.open(filepath, std::ios::in);

  if (!log_file.is_open()) {
    std::cerr << "Error opening log file at " << filepath << "! (sudo?)" << std::endl;
  }

  std::string line;

   
  // testing timestamp comparisons
  std::tm time1;
  std::tm time2;
  int flag = 0;
  while (std::getline(log_file, line)) {
    LogLine log = LogLine(line);
    switch(flag) {
      case 0:
        time1 = log.get_parsed_time();
        break;
      case 1:
        time2 = log.get_parsed_time();
        break;
      case 2:
        break;

    }
    flag++;

    if (flag == 2) {
      break;
    }
  }

  if (is_earlier_time(time1, time2)) {
    std::cout << "Time1 is earlier than time2" << std::endl;
  }
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

