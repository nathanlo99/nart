
#include "defs.h"
#include "vector3f.h"

size_t num_tests = 0;
#define assert(expr)                                                           \
  (num_tests++, ((expr) || (printf("[ERROR] Test failed: %s (%s:%d)\n", #expr, \
                                   __FILE__, __LINE__),                        \
                            exit(1), true)))

void test_vector3f() {
  Vector3f a{3, 1, 4}, b{1, 5, 9}, c{0, 0, 1};
  assert((a + b == (Vector3f){4, 6, 13}));
  assert((a - b == (Vector3f){2, -4, -5}));
  assert((2.f * a == (Vector3f){6, 2, 8}));
  assert((a * 2.f == (Vector3f){6, 2, 8}));
  assert((a.dot(b) == 44));
  assert((a.dot(a) == 26));
  assert((c.normalize() == c));
  assert(((2.f * c).normalize() == c));
  assert(((-1.f * c).normalize() != c));

  Vector3f d{2, 5, 14}, e{8, 9, 12};
  assert((d.normalize() == (Vector3f){2. / 15, 5. / 15, 14. / 15}));
  assert((e.normalize() == (Vector3f){8. / 17, 9. / 17, 12. / 17}));
  assert((d.dot(e) == 229));
  assert((e.dot(d) == 229));
  assert((d.dot(d) == 225));
  assert((e.dot(e) == 289));

  Vector3f f = a.cross(b).normalize();
  assert((a.cross(b) == (Vector3f){-11, -23, 14}));
  assert((a.normalize().dot(f) == 0));
  assert((b.normalize().dot(f) == 0));

  Vector3f g = d.cross(e).normalize();
  assert((d.cross(e) == (Vector3f){-66, 88, -22}));
  assert((std::abs(d.normalize().dot(g)) < 1e-5));
  assert((std::abs(e.normalize().dot(g)) < 1e-5));

  Vector3f x{3, 8, 5}, y{2, 7, 4}, z{6, 3, 5};
  // Gram-Schmidt
  Vector3f u1 = x.normalize();
  Vector3f u2 = (y - y.dot(u1) * u1).normalize();
  Vector3f u3 = (z - (z.dot(u1) * u1) - (z.dot(u2) * u2)).normalize();
  assert((u1.norm() == 1));
  assert((u2.norm() == 1));
  assert((u3.norm() == 1));
  assert((std::abs(u1.dot(u2)) < 1e-5)); // Running into floating point problems
  assert((std::abs(u1.dot(u3)) < 1e-5));
  assert((std::abs(u2.dot(u3)) < 1e-5));
}

int main() {
  INFO("Starting tests...");
  test_vector3f();
  INFO("All " + std::to_string(num_tests) + " tests passed");
  return 0;
}
