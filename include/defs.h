#ifndef DEFS_H
#define DEFS_H

#include <ctime>
#include <iomanip>
#include <iostream>

// ================================= Logging ==================================
#define INFO                                                                   \
  std::cout << std::put_time(std::localtime(&time_now),                        \
                             "%y-%m-%d %OH:%OM:%OS")                           \
            << " [INFO] " << __FILE__ << "(" << __FUNCTION__ << ":"            \
            << __LINE__ << ") >> "
#define ERROR                                                                  \
  std::cout << std::put_time(std::localtime(&time_now),                        \
                             "%y-%m-%d %OH:%OM:%OS")                           \
            << " [ERROR] " << __FILE__ << "(" << __FUNCTION__ << ":"           \
            << __LINE__ << ") >> "

static std::time_t time_now = std::time(nullptr);
// ================================= Logging ==================================

#endif /* end of include guard: DEFS_H */
