#ifndef SB_COMPONENTS
#define SB_COMPONENTS

#include "constants.h"
#include <cmath>
#include <entt/entt.hpp>
#include <vector>
#include <string>

namespace components {

struct GameState {
    bool running;
};

struct Position {
  double x, y;
};

struct Mass {
  double mass;
};

struct OrbitingBodies {
  std::vector<entt::entity> orbiters;
};

struct Orbit {
  entt::entity orbitingAround;
  double period;
  double radius;
  double currentAngle{0.0};

  Orbit(entt::entity me, entt::entity it, std::shared_ptr<entt::registry> &registry) {
    using namespace components;
    using namespace constants;
    const auto [myMass, myPosition] = registry->get<Mass, Position>(me);
    const auto [itsMass, itsPosition] = registry->get<Mass, Position>(it);

    radius = std::sqrt((std::pow(myPosition.x - itsPosition.x, 2.0) +
                        std::pow(myPosition.y - itsPosition.y, 2.0)));
    period =
        2 * math::PI *
        std::sqrt(std::pow(radius, 3.0) / (physics::GRAVITATIONAL_CONSTANT *
                                           (myMass.mass + itsMass.mass)));
    orbitingAround = it;
  };
};

struct Time {
  int year;
  int month;
  int day;
  int hour;
  int minutes;
  int seconds;

  int updatesPerSecond;
  int currentSecondsPerTickIndex;
  static const int TICK_LEVELS = 11;
  const int secondsPerTick[TICK_LEVELS] {1, 5, 15, 30, 60, 120, 300, 600, 900, 1800, 3600};

  void nextTick() {
      seconds += secondsLastTick();
      if(seconds > 3600) {
          addHour();
          seconds -= 3600;
      }
      minutes = seconds / 60;
  }

  constexpr int secondsLastTick() { return secondsPerTick[currentSecondsPerTickIndex]; }

  void increaseSecondsPerTick(){
      if(currentSecondsPerTickIndex < TICK_LEVELS - 1) {
          currentSecondsPerTickIndex++;
      }
  }
  void decreaseSecondsPerTick(){
      if(currentSecondsPerTickIndex > 0) {
          currentSecondsPerTickIndex--;
      }
  }

  void addHour() {
    if (hour < 23) {
      hour++;
    } else {
      hour = 0;
      addDay();
    }
  }
  void addDay() {
    if (day < 30) {
      day++;
    } else {
      day = 1;
      addMonth();
    }
  }
  void addMonth() {
    if (month < 12) {
      month++;
    } else {
      month = 1;
      year++;
    }
  }
};

struct TimeStats {
    int simulationSpeed;
    int bestSimulationSpeed;
    constexpr double simulationEfficiency(Time& time){
        return (double)(simulationSpeed)/(time.updatesPerSecond * time.secondsLastTick());
    }
};

struct Camera {
  int offset_x, offset_y;
  double zoom;
};

} // namespace components

namespace events {

struct key_pressed {
  std::string key;
};

struct mouse_drag {
  int x;
  int y;
};

struct zoom {
  int x;
  int y;
  double scale;
};

} // namespace events

#endif