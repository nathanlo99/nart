#ifndef COLOR_H
#define COLOR_H

#include <algorithm>

struct Color {
  float r = 0, g = 0, b = 0;
  static const Color RED, GREEN, BLUE, MAGENTA, TURQUOISE, YELLOW, WHITE, BLACK;

  // TODO better clamping algorithm
  constexpr Color clamp() const noexcept {
    return Color{std::clamp(r, 0.0f, 1.0f), std::clamp(g, 0.0f, 1.0f),
                 std::clamp(b, 0.0f, 1.0f)};
  }
};

constexpr Color operator+(const Color &a, const Color &b) noexcept {
  return Color{a.r + b.r, a.g + b.g, a.b + b.b};
}

constexpr Color operator*(const float c, const Color &a) noexcept {
  return Color{static_cast<float>(c * a.r), static_cast<float>(c * a.g),
               static_cast<float>(c * a.b)};
}

constexpr Color operator*(const double c, const Color &a) noexcept {
  return Color{static_cast<float>(c * a.r), static_cast<float>(c * a.g),
               static_cast<float>(c * a.b)};
}

constexpr Color operator/(const Color &a, const double n) noexcept {
  if (n <= 0)
    return a;
  return {static_cast<float>(a.r / n), static_cast<float>(a.g / n),
          static_cast<float>(a.b / n)};
}

#endif /* end of include guard: COLOR_H */
