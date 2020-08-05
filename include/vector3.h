
#pragma once

#include <cmath>
#include <iostream>
#include <string>

// A 3-element mathematical vector
template <typename T> struct vec3_impl {
  union {
    struct {
      T x, y, z;
    };
    struct {
      T r, g, b;
    };
    T data[3];
  };
  using type = T;
  vec3_impl() noexcept : vec3_impl(0.0f, 0.0f, 0.0f) {}
  vec3_impl(T x, T y, T z) noexcept : x{x}, y{y}, z{z} {}
  vec3_impl(const vec3_impl &other) noexcept
      : x{other.x}, y{other.y}, z{other.z} {}
  vec3_impl &operator=(const vec3_impl &other) noexcept {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }
  T &operator[](size_t idx) noexcept { return data[idx]; }
  const T &operator[](size_t idx) const noexcept { return data[idx]; }
  constexpr T dot(const vec3_impl<T> &other) const noexcept;
  constexpr T norm() const noexcept;
  constexpr T norm2() const noexcept;
  constexpr vec3_impl<T> normalize() const;
  constexpr vec3_impl<T> cross(const vec3_impl<T> &v) const noexcept;

  std::string to_string() const noexcept;
};

template <typename T>
constexpr vec3_impl<T> operator+(const vec3_impl<T> a,
                                 const vec3_impl<T> b) noexcept {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}
template <typename T>
constexpr vec3_impl<T> operator-(const vec3_impl<T> a,
                                 const vec3_impl<T> b) noexcept {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename T>
constexpr vec3_impl<T> operator*(const vec3_impl<T> a, const float c) noexcept {
  return {c * a.x, c * a.y, c * a.z};
}
template <typename T>
constexpr vec3_impl<T> operator*(const float c, const vec3_impl<T> a) noexcept {
  return {c * a.x, c * a.y, c * a.z};
}

template <typename T>
constexpr vec3_impl<T> operator/(const vec3_impl<T> a, const float c) noexcept {
  return {a.x / c, a.y / c, a.z / c};
}

template <typename T>
constexpr bool operator==(const vec3_impl<T> a, const vec3_impl<T> b) noexcept {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}
template <typename T>
constexpr bool operator!=(const vec3_impl<T> a, const vec3_impl<T> b) noexcept {
  return !(a == b);
}

template <typename T>
constexpr T vec3_impl<T>::dot(const vec3_impl<T> &other) const noexcept {
  return x * other.x + y * other.y + z * other.z;
}
template <typename T> constexpr T vec3_impl<T>::norm() const noexcept {
  return sqrt(dot(*this));
}
template <typename T> constexpr T vec3_impl<T>::norm2() const noexcept {
  return dot(*this);
}

template <typename T>
constexpr vec3_impl<T> min(const vec3_impl<T> a, const vec3_impl<T> b) {
  return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
}
template <typename T>
constexpr vec3_impl<T> max(const vec3_impl<T> a, const vec3_impl<T> b) {
  return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
}

template <typename T> constexpr vec3_impl<T> vec3_impl<T>::normalize() const {
  const T nm = norm();
  return {x / nm, y / nm, z / nm};
}

template <typename T>
constexpr vec3_impl<T>
vec3_impl<T>::cross(const vec3_impl<T> &v) const noexcept {
  return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

template <typename T> std::string vec3_impl<T>::to_string() const noexcept {
  return "<" + std::to_string(x) + ", " + std::to_string(y) + ", " +
         std::to_string(z) + ">";
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const vec3_impl<T> &vec) noexcept {
  return os << vec.to_string();
}
