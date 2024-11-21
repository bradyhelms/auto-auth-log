#ifndef LOGLINE_H
#define LOGLINE_H

#include <string>
#include "timestamp.h"


class LogLine {
private: 

  std::string m_timestamp;
  std::tm m_parsed_time;
  std::string m_hostname;
  std::string m_service;
  int m_pid;
  std::string m_event_desc;
  std::string m_ip;

  bool m_is_failed_login = false;

public:

  LogLine(const std::string& line);
  ~LogLine();

  std::string get_timestamp()       const;
  std::string get_formatted_time()  const; 
  std::tm     get_parsed_time()     const;
  std::string get_hostname()        const;
  std::string get_service()         const;
  std::string get_event_desc()      const;
  int         get_pid()             const;
  bool        is_failed_login()     const;
  std::string get_ip()              const;

  void display();
  std::string extract_ip() const;
};

#endif // LOGLINE_H
