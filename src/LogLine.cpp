#include "../include/LogLine.h"
#include "../include/timestamp.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <regex>

LogLine::LogLine(const std::string& line) {
  std::istringstream stream(line);
  std::string token;

  std::string month, day, time;
  stream >> month >> day >> time;
  m_timestamp = month + " " + day + " " + time;
  m_parsed_time = parse_timestamp(m_timestamp);


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

  // Get IP and Check if this is a failed login
  // IP will be empty string if log doesn't contain an IP address
  m_ip = extract_ip();
  if (!m_ip.empty()) {
    if (m_event_desc.substr(0, 15) ==   "Failed password") {
      m_is_failed_login = true;
    } else if (m_event_desc.substr(0, 17) == "Accepted password") {
      m_is_successful_login = true;
    }
  }

}

LogLine::~LogLine() {}

std::string LogLine::get_timestamp()   const { return m_timestamp;       }
std::string LogLine::get_hostname()    const { return m_hostname;        }
std::string LogLine::get_service()     const { return m_service;         }
std::string LogLine::get_event_desc()  const { return m_event_desc;      }
int         LogLine::get_pid()         const { return m_pid;             }
bool        LogLine::is_failed_login() const { return m_is_failed_login; }
bool        LogLine::is_successful_login() const {return m_is_successful_login; }
std::string LogLine::get_ip()          const { return m_ip;              }
std::string LogLine::get_formatted_time() const { 
  std::ostringstream oss;
  oss << std::put_time(&m_parsed_time, "%c");
  return oss.str();
} 
std::tm     LogLine::get_parsed_time()    const { return m_parsed_time; }

void LogLine::display() {
  std::cout << m_timestamp    << " " 
            << m_hostname     << " "
            << m_service      << ""
     << "[" << m_pid          << "]: "
            << m_event_desc   << "\n";
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
