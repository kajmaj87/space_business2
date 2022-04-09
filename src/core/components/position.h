#ifndef SB_COMPONENT_POSITION
#define SB_COMPONENT_POSITION

class Position {
private:
public:
  Position();
  ~Position() = default;
  double x, y;
};

Position::Position() = default;

#endif