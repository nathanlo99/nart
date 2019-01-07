#ifndef COLOR_H
#define COLOR_H

struct Color {
  float r = 0, g = 0, b = 0;
  static const Color RED, GREEN, BLUE, MAGENTA, TURQUOISE, YELLOW, WHITE, BLACK;
};

constexpr Color operator+(const Color &a, const Color &b) noexcept {
  return Color{a.r + b.r, a.g + b.g, a.b + b.b};
}

constexpr Color operator/(const Color &a, const float n) noexcept {
  if (n <= 0)
    return a;
  return {a.r / n, a.g / n, a.b / n};
}

#endif /* end of include guard: COLOR_H */
