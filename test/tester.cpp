
#include "defs.h"
#include "vector3.h"

size_t num_tests = 0;
#define assert(expr)                                                           \
  (num_tests++, ((expr) || (printf("[ERROR] Test failed: %s (%s:%d)\n", #expr, \
                                   __FILE__, __LINE__),                        \
                            exit(1), true)))

void test_vec3() {
  const vec3 a{3, 1, 4}, b{1, 5, 9}, c{0, 0, 1};
  assert((a + b == vec3{4, 6, 13}));
  assert((a - b == vec3{2, -4, -5}));
  assert((2.f * a == vec3{6, 2, 8}));
  assert((a * 2.f == vec3{6, 2, 8}));
  assert((fequal(a.dot(b), 44.0)));
  assert((fequal(a.dot(a), 26.0)));
  assert((c.normalize() == c));
  assert(((2.f * c).normalize() == c));
  assert(((-1.f * c).normalize() != c));

  const vec3 d{2, 5, 14}, e{8, 9, 12};
  assert((d.normalize() == vec3{2. / 15, 5. / 15, 14. / 15}));
  assert((e.normalize() == vec3{8. / 17, 9. / 17, 12. / 17}));
  assert((fequal(d.dot(e), 229.0)));
  assert((fequal(e.dot(d), 229.0)));
  assert((fequal(d.dot(d), 225.0)));
  assert((fequal(e.dot(e), 289.0)));

  const vec3 f = a.cross(b).normalize();
  assert((a.cross(b) == vec3{-11, -23, 14}));
  assert((fzero(a.normalize().dot(f))));
  assert((fzero(b.normalize().dot(f))));

  const vec3 g = d.cross(e).normalize();
  assert((d.cross(e) == vec3{-66, 88, -22}));
  assert((fzero(d.normalize().dot(g))));
  assert((fzero(e.normalize().dot(g))));

  const vec3 x{3, 8, 5}, y{2, 7, 4}, z{6, 3, 5};
  // Gram-Schmidt (bigger ULPS used to compensate for bad precision)
  const vec3 u1 = x.normalize();
  const vec3 u2 = (y - y.dot(u1) * u1).normalize();
  const vec3 u3 = (z - (z.dot(u1) * u1) - (z.dot(u2) * u2)).normalize();
  assert((fequal(u1.norm(), 1.0)));
  assert((fequal(u2.norm(), 1.0)));
  assert((fequal(u3.norm(), 1.0)));
  assert((fzero(u1.dot(u2), 128)));
  assert((fzero(u1.dot(u3), 128)));
  assert((fzero(u2.dot(u3), 128)));
}

int main() {
  INFO("Starting tests...");
  test_vec3();
  INFO("All " + std::to_string(num_tests) + " tests passed");
  return 0;
}
