#ifndef VECTOR3F_H
#define VECTOR3F_H

#include "defs.h"
#include <cmath>
#include <iostream>

// A 3-element mathematical vector
template <typename T> struct Vector {
  T x = 0, y = 0, z = 0;
  using type = T;
  Vector() noexcept {}
  Vector(T x, T y, T z) noexcept : x{x}, y{y}, z{z} {}
  Vector(const Vector &other) noexcept : x{other.x}, y{other.y}, z{other.z} {}
  Vector &operator=(const Vector &other) noexcept {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }
  constexpr T dot(const Vector<T> &other) const noexcept;
  constexpr T norm() const noexcept;
  constexpr Vector<T> normalize() const;
  constexpr Vector<T> cross(const Vector<T> &v) const noexcept;

  std::string to_string() const noexcept;
};

template <typename T>
constexpr Vector<T> operator+(const Vector<T> a, const Vector<T> b) noexcept {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}
template <typename T>
constexpr Vector<T> operator-(const Vector<T> a, const Vector<T> b) noexcept {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename T>
constexpr Vector<T> operator*(const Vector<T> a, const double c) noexcept {
  return {c * a.x, c * a.y, c * a.z};
}
template <typename T>
constexpr Vector<T> operator*(const double c, const Vector<T> a) noexcept {
  return {c * a.x, c * a.y, c * a.z};
}

template <typename T>
constexpr bool operator==(const Vector<T> a, const Vector<T> b) noexcept {
  return fequal(a.x, b.x, 2) && fequal(a.y, b.y, 2) && fequal(a.z, b.z, 2);
}
template <typename T>
constexpr bool operator!=(const Vector<T> a, const Vector<T> b) noexcept {
  return !(a == b);
}

template <typename T>
constexpr T Vector<T>::dot(const Vector<T> &other) const noexcept {
  return x * other.x + y * other.y + z * other.z;
}
template <typename T> constexpr T Vector<T>::norm() const noexcept {
  return sqrt(dot(*this));
}

template <typename T> constexpr Vector<T> Vector<T>::normalize() const {
  const T nm = norm();
  // if (fzero(nm))
  //   return *this;
  return {x / nm, y / nm, z / nm};
}

template <typename T>
constexpr Vector<T> Vector<T>::cross(const Vector<T> &v) const noexcept {
  return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

template <typename T> std::string Vector<T>::to_string() const noexcept {
  return "<" + std::to_string(x) + ", " + std::to_string(y) + ", " +
         std::to_string(z) + ">";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &vec) noexcept {
  return os << vec.to_string();
}

// Overload 'Vector3f' and the associated accuracy to which we perform
// calculations
using Vector3f = Vector<double>;
#define accuracy 0.00001

#endif /* end of include guard: VECTOR3F_H */
