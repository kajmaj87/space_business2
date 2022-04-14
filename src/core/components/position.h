#ifndef SB_COMPONENT_POSITION
#define SB_COMPONENT_POSITION

class Position {
private:
public:
  Position(double x, double y) : x{x}, y{y} {};
  ~Position() = default;
  double x{}, y{};
};


#endif