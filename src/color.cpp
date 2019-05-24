
#include "color.h"

const Color Color::RED{1, 0, 0}, Color::GREEN{0, 1, 0}, Color::BLUE{0, 0, 1};
const Color Color::MAGENTA{1, 0, 1}, Color::YELLOW{1, 1, 0},
    Color::TURQUOISE{0, 1, 1};
const Color Color::WHITE{1, 1, 1}, Color::BLACK{0, 0, 0};

std::ostream &operator<<(std::ostream &os, const Color &c) {
  return os << "Color(" << c.r << ", " << c.g << ", " << c.b << ")";
}
