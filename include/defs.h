#ifndef DEFS_H
#define DEFS_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

// ================================= Logging ==================================
#ifdef LOG
static auto program_start_time = std::chrono::high_resolution_clock::now();
inline void log(const std::string &type, const std::string &msg) {
  const auto nano =
      static_cast<std::chrono::nanoseconds>(
          std::chrono::high_resolution_clock::now() - program_start_time)
          .count();
  std::cout << std::setw(10) << std::left << nano << " : " << type << " " << msg
            << std::endl;
}
#define INFO(s)                                                                \
  log("[INFO]", std::string{} + __FILE__ + " (" + __FUNCTION__ + ":" +         \
                    std::to_string(__LINE__) + ") >> " + (s))
#define ERROR(s)                                                               \
  log("[ERROR]", std::string{} + __FILE__ + " (" + __FUNCTION__ + ":" +        \
                     std::to_string(__LINE__) + ") >> " + (s))
#else
inline void info(const std::string &msg) {}
inline void error(const std::string &msg) {}
#define INFO(s)
#define ERROR(s)
#endif // ifdef LOG
       // ================================= Logging
       // ==================================

#endif /* end of include guard: DEFS_H */
