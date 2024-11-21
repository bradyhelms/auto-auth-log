#include "LogLine.h"
#include <iostream>
#include <string>
#include <fstream>

void debug_print_LogLine(const LogLine log);

int main(int argc, char** argv) {

  std::string filepath = "/var/log/secure";
  std::fstream log_file;
  log_file.open(filepath, std::ios::in);

  if (!log_file.is_open()) {
    std::cerr << "Error opening log file at " << filepath << "! (sudo?)" << std::endl;
  }

  std::string line;

  while (std::getline(log_file, line)) {
    LogLine log = LogLine(line);
    std::string ip = log.extract_ip();
    if (!ip.empty()) {
      std::cout << ip << std::endl;
    } 
  }

  log_file.close();
  return 0;

}

void debug_print_LogLine(const LogLine log) {
  std::cout << "Timestamp:          " << log.get_timestamp()  << "\n";
  std::cout << "Hostname:           " << log.get_hostname()   << "\n";
  std::cout << "Service:            " << log.get_service()    << "\n";
  std::cout << "PID:                " << log.get_pid()        << "\n";
  std::cout << "Event Description:  " << log.get_event_desc() << "\n";
}

