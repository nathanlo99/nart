#ifndef VECTOR3F_H
#define VECTOR3F_H

#include "defs.h"
#include <cmath>
#include <iostream>
#include <string>

// A 3-element mathematical vector
template <typename T> struct Vector3 {
  union {
    struct {
      T x = 0, y = 0, z = 0;
    };
    T data[3];
  };
  using type = T;
  Vector3() noexcept {}
  Vector3(T x, T y, T z) noexcept : x{x}, y{y}, z{z} {}
  Vector3(const Vector3 &other) noexcept : x{other.x}, y{other.y}, z{other.z} {}
  Vector3 &operator=(const Vector3 &other) noexcept {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }
  T &operator[](size_t idx) noexcept { return data[idx]; }
  const T &operator[](size_t idx) const noexcept { return data[idx]; }
  constexpr T dot(const Vector3<T> &other) const noexcept;
  constexpr T norm() const noexcept;
  constexpr T norm2() const noexcept;
  constexpr Vector3<T> normalize() const;
  constexpr Vector3<T> cross(const Vector3<T> &v) const noexcept;

  std::string to_string() const noexcept;
};

template <typename T>
constexpr Vector3<T> operator+(const Vector3<T> a,
                               const Vector3<T> b) noexcept {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}
template <typename T>
constexpr Vector3<T> operator-(const Vector3<T> a,
                               const Vector3<T> b) noexcept {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename T>
constexpr Vector3<T> operator*(const Vector3<T> a, const double c) noexcept {
  return {c * a.x, c * a.y, c * a.z};
}
template <typename T>
constexpr Vector3<T> operator*(const double c, const Vector3<T> a) noexcept {
  return {c * a.x, c * a.y, c * a.z};
}

template <typename T>
constexpr bool operator==(const Vector3<T> a, const Vector3<T> b) noexcept {
  return fequal(a.x, b.x, 2) && fequal(a.y, b.y, 2) && fequal(a.z, b.z, 2);
}
template <typename T>
constexpr bool operator!=(const Vector3<T> a, const Vector3<T> b) noexcept {
  return !(a == b);
}

template <typename T>
constexpr T Vector3<T>::dot(const Vector3<T> &other) const noexcept {
  return x * other.x + y * other.y + z * other.z;
}
template <typename T> constexpr T Vector3<T>::norm() const noexcept {
  return sqrt(dot(*this));
}
template <typename T> constexpr T Vector3<T>::norm2() const noexcept {
  return dot(*this);
}

template <typename T>
constexpr Vector3<T> min(const Vector3<T> a, const Vector3<T> b) {
  return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
}
template <typename T>
constexpr Vector3<T> max(const Vector3<T> a, const Vector3<T> b) {
  return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
}

template <typename T> constexpr Vector3<T> Vector3<T>::normalize() const {
  const T nm = norm();
  if (fzero(nm))
    return *this;
  return {x / nm, y / nm, z / nm};
}

template <typename T>
constexpr Vector3<T> Vector3<T>::cross(const Vector3<T> &v) const noexcept {
  return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

template <typename T> std::string Vector3<T>::to_string() const noexcept {
  return "<" + std::to_string(x) + ", " + std::to_string(y) + ", " +
         std::to_string(z) + ">";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector3<T> &vec) noexcept {
  return os << vec.to_string();
}

// Overload 'Vector3f' and the associated accuracy to which we perform
// calculations
using Vector3f = Vector3<double>;
#define accuracy 0.00001

#endif /* end of include guard: VECTOR3F_H */
