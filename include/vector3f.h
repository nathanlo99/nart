#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <cmath>
#include <iostream>

template <typename T> struct Vector {
  T x, y, z;
  using type = T;
  constexpr T dot(const Vector<T> &other) const;
  constexpr T norm() const;
  constexpr Vector<T> normalize() const;
  constexpr Vector<T> cross(const Vector<T> &v) const;

  std::string to_string() const;
};

template <typename T> constexpr Vector<T> operator+(Vector<T> a, Vector<T> b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}
template <typename T> constexpr Vector<T> operator-(Vector<T> a, Vector<T> b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename T> constexpr Vector<T> operator*(Vector<T> a, double c) {
  return {c * a.x, c * a.y, c * a.z};
}
template <typename T> constexpr Vector<T> operator*(double c, Vector<T> a) {
  return {c * a.x, c * a.y, c * a.z};
}

template <typename T> constexpr bool operator==(Vector<T> a, Vector<T> b) {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}
template <typename T> constexpr bool operator!=(Vector<T> a, Vector<T> b) {
  return !(a == b);
}

template <typename T> constexpr T Vector<T>::dot(const Vector<T> &other) const {
  return x * other.x + y * other.y + z * other.z;
}
template <typename T> constexpr T Vector<T>::norm() const {
  return sqrt(dot(*this));
}
template <typename T> constexpr Vector<T> Vector<T>::normalize() const {
  const T nm = norm();
  return {x / nm, y / nm, z / nm};
}

template <typename T>
constexpr Vector<T> Vector<T>::cross(const Vector<T> &v) const {
  return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

template <typename T> std::string Vector<T>::to_string() const {
  return "<" + std::to_string(x) + ", " + std::to_string(y) + ", " +
         std::to_string(z) + ">";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &vec) {
  return os << vec.to_string();
}

#define Vector3f Vector<double>
#endif /* end of include guard: VECTOR3F_H */
