#include "LogLine.h"
#include <sstream>
#include <iostream>
#include <regex>

LogLine::LogLine(const std::string& line) {
  std::istringstream stream(line);
  std::string token;

  std::string month, day, time;
  stream >> month >> day >> time;
  m_timestamp = month + " " + day + " " + time;

  stream >> m_hostname;

  std::getline(stream, token, '[');
  m_service = token;
  // Leading whitespace
  m_service.erase(0, m_service.find_first_not_of(" "));


  stream >> m_pid;
  stream.ignore(); // closing bracket
  
  stream.ignore(); // Colon
  stream >> std::ws;
  
  std::getline(stream, m_event_desc);
}

LogLine::~LogLine() {}

std::string LogLine::get_timestamp()  const { return m_timestamp;  }
std::string LogLine::get_hostname()   const { return m_hostname;   }
std::string LogLine::get_service()    const { return m_service;    }
std::string LogLine::get_event_desc() const { return m_event_desc; }
int         LogLine::get_pid()        const { return m_pid;        }

void LogLine::display() {
  std::cout << m_timestamp    << " " 
            << m_hostname     << " "
            << m_service      << ""
     << "[" << m_pid          << "]: "
            << m_event_desc   << std::endl;
}

std::string LogLine::extract_ip() const {
  std::regex ip_re(R"((\d{1,3}\.){3}\d{1,3})");
//  std::regex ip_re(R"(^((25[0-5]|(2[0-4]|1\d|[1-9]?)\d)\.?\b){4}$)");

  std::smatch match;
  if (std::regex_search(m_event_desc, match, ip_re)) {
    return match.str(0);
  }
  return "";
}
