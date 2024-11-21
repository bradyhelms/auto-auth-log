#ifndef LOGLINE_H
#define LOGLINE_H

#include <string>


class LogLine {
private: 

  std::string m_timestamp;
  std::string m_hostname;
  std::string m_service;
  int m_pid;
  std::string m_event_desc;

public:

  LogLine(const std::string& line);
  ~LogLine();

  std::string get_timestamp()  const;
  std::string get_hostname()   const;
  std::string get_service()    const;
  std::string get_event_desc() const;
  int         get_pid()        const;

  void display();

  std::string extract_ip() const;
};

#endif // LOGLINE_H
