#ifndef DEFS_H
#define DEFS_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <tuple>
#include <type_traits>
#include <vector>

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

// ================================= Logging ==================================

template <class T>
constexpr
    typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    fequal(T x, T y, int ulp = 2) {
  return std::abs(x - y) <=
             std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp ||
         std::abs(x - y) < std::numeric_limits<T>::min();
}

template <class T>
constexpr
    typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    fzero(T x, int ulp = 2) {
  return std::abs(x) <= std::numeric_limits<T>::epsilon() * ulp;
}

// ============================================================================

template <typename T> T random() {
  static auto seed =
      std::chrono::system_clock().now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  static std::uniform_real_distribution<T> distribution(0.0, 1.0);
  return distribution(generator);
}

// ============================================================================

template <typename S, typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::tuple<S, T, U> &x) {
  return os << "(" << std::get<0>(x) << ", " << std::get<1>(x) << ", "
            << std::get<2>(x) << ")";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  if (v.empty())
    return os << "[]";
  os << "[" << v[0];
  for (unsigned i = 1; i < v.size(); ++i)
    os << v[i];
  return os << "]";
}

#endif /* end of include guard: DEFS_H */
