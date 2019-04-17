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
// Gets the current time, in nanoseconds (as a std::chrono::time_point)
inline auto get_time() { return std::chrono::high_resolution_clock::now(); }

#ifdef LOG
static auto program_start_time = get_time();
inline void log(const std::string &type, const std::string &msg) {
  const auto nano =
      std::chrono::nanoseconds(get_time() - program_start_time).count();
  std::cout << std::setw(15) << std::left << nano << " : " << type << " " << msg
            << std::endl;
}
// Gets the number of nanoseconds since the program started
inline long long nano_time() {
  return std::chrono::nanoseconds(get_time() - program_start_time).count();
}
// Gets the number of milliseconds since the program started
inline long long milli_time() { return nano_time() / 1000000; }
#define INFO(s)                                                                \
  log("[INFO]", std::string{} + __FILE__ + " (" + __FUNCTION__ + ":" +         \
                    std::to_string(__LINE__) + ") >> " + (s))
#define ERROR(s)                                                               \
  log("[ERROR]", std::string{} + __FILE__ + " (" + __FUNCTION__ + ":" +        \
                     std::to_string(__LINE__) + ") >> " + (s))
#else
#define INFO(s)
#define ERROR(s)
#endif // ifdef LOG

// ================================= Logging ==================================

// Returns true if the floating point values x and y are equal to 'ulp' ulps
// NOTE: ALWAYS use this when comparing floating point values, the compiler will
// complain otherwise (for good reason)
template <class T>
constexpr inline
    typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    fequal(const T x, const T y, const int ulp = 2) {
  return std::abs(x - y) <=
             std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp ||
         std::abs(x - y) < std::numeric_limits<T>::min();
}

// Returns true if the floating-point value x is equal to 0 to 'ulp' ulps
// NOTE: ALWAYS use this when comparing a floating value to 0, this is an
// optimization to the above function
template <class T>
constexpr inline
    typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    fzero(const T x, const int ulp = 2) {
  return std::abs(x) <= std::numeric_limits<T>::epsilon() * ulp;
}

// ============================================================================

// Returns a random value of floating-point type T between 0 and 1
template <typename T = float> T inline random() {
  static const auto seed =
      std::chrono::system_clock().now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  static std::uniform_real_distribution<T> distribution(0.0, 1.0);
  return distribution(generator);
}
template <typename T> T inline random(T min, T max) {
  return min + random<T>() * (max - min);
}

// ============================================================================

// Quality-of-life debugging functions to print tuples and vectors (assumes that
// operator<< is overloaded for all types)
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
    os << ", " << v[i];
  return os << "]";
}

#endif /* end of include guard: DEFS_H */
