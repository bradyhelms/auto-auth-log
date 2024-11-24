#include "../include/LogLine.h"
#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <getopt.h>

typedef struct {
  std::string origin_ip;
  int num_attempts;
  std::string port;
  std::string service;
} fail_sum;

enum Options : std::uint32_t {
  FAILSSUM      = 1 << 0,
  FAILFULL      = 1 << 1,
  PRINTLOG      = 1 << 2,
};

void debug_print_LogLine(const LogLine& log);
void print_failed_logins(const std::vector<LogLine> logs);
void usage();

int main(int argc, char** argv) {

  // Parse Command line options
  
  if (argc == 1) {
    std::cerr << "No options given. Use -h for a list of options.\n";
    exit(1);
  }

  std::uint32_t OPTIONS = 0;
  opterr = 0;
  int opt;

  while ((opt = getopt(argc, argv, "fFlh")) != -1) {
    switch(opt) {
      case 'f':
        OPTIONS |= FAILSSUM; 
        break;
      case 'F':
        OPTIONS |= FAILFULL;
        break;
      case 'l':
        OPTIONS |= PRINTLOG;
        break;
      case 'h':
        usage();
        exit(0);
        break;
      default:
        std::cerr << "Invalid command line options entered.\n" 
                  << "(use -h for a list of options)" << std::endl;
        exit(1);
    }
  }

  // TODO: implement distro agnostic filepath
  std::string filepath = "/var/log/secure";
  std::fstream log_file;
  log_file.open(filepath, std::ios::in);

  if (!log_file.is_open()) {
    std::cerr << "Error opening log file at " << filepath << "! (sudo?)" << std::endl;
  }

  std::vector<LogLine> logs;
  std::string line;

  while (getline(log_file, line)) {
    LogLine log = LogLine(line);
    logs.push_back(log);
  }
  
  if ((OPTIONS & FAILSSUM) && !(OPTIONS & FAILFULL)) {

    print_failed_logins(logs);
  }

  if (OPTIONS & FAILFULL) {
    // do something
    std::cout << "Feature not implemented yet, stay tuned\n";
  }

  if (OPTIONS & PRINTLOG) {
    for (auto& log : logs) {
      log.display();
    }
  }


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

void usage() {
  std::cout << "Usage:          sudo ./log_parser [OPTIONS]\n"
            << "Options:\n"
            << "    -f          Print login failure summary\n"
            << "    -F          Print full login failures\n"
            << "    -l          Print entire log file\n";
}
