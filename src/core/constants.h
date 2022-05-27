#ifndef SB_CONSTANTS
#define SB_CONSTANTS

namespace constants {

namespace physics {

const auto GRAVITATIONAL_CONSTANT = 6.67430151515151515e-11;
constexpr auto ASTRONOMICAL_UNIT = 1.495978707e11;
constexpr double operator ""_au(long double au) {
  return au*ASTRONOMICAL_UNIT;
};

} // namespace physics

namespace math {

const double PI = 3.141592653589793238463;

}

} // namespace constants
#endif
