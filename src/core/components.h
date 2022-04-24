#ifndef SB_COMPONENTS
#define SB_COMPONENTS

#include <entt/entt.hpp>
#include <cmath>
#include <vector>
#include "constants.h"

namespace components {

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
        double currentAngle {0.0};

        Orbit(entt::entity me, entt::entity orbitingAround, entt::registry& registry){
            using namespace components;
            using namespace constants;
            const auto [myMass, myPosition] = registry.get<Mass, Position>(me);
            const auto [itsMass, itsPosition] = registry.get<Mass, Position>(orbitingAround);

            radius = std::sqrt((std::pow(myPosition.x - itsPosition.x, 2.0) + std::pow(myPosition.y - itsPosition.y, 2.0)));
            period = 2 * math::PI * std::sqrt(std::pow(radius, 3.0)/(physics::GRAVITATIONAL_CONSTANT * (myMass.mass + itsMass.mass))); 

            // add me to the orbiting bodies list of the parent
            if (registry.all_of<OrbitingBodies>(orbitingAround)){
                auto parent = registry.get<OrbitingBodies>(orbitingAround);
                parent.orbiters.push_back(me);
            } else {
                registry.emplace<OrbitingBodies>(orbitingAround, std::vector {me});
            }
        };

    };

    struct Time {
        int ticks;
        int year;
        int month;
        int day;
        int hour;

        void nextTick(){
            ticks++;
            addHour();
        }

        constexpr auto secondsLastTick(){
            return 3600;
        }

        void addHour(){
            if(hour < 23){
                hour++;
            } else {
                hour = 0;
                addDay();
            }
        }
        void addDay(){
            if(day<30){
                day++;
            } else {
                day = 1;
                addMonth();
            }
        }
        void addMonth(){
            if(month<12){
                month++;
            } else {
                month = 1;
                year++;
            }
        }
    };

}

#endif