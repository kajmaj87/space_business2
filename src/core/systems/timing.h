#ifndef SB_SYSTEMS_TIMING
#define SB_SYSTEMS_TIMING
#include <entt/entt.hpp>
#include "../components.h"

class TimingSystem {
private:
    
public:
    TimingSystem() = default;
    ~TimingSystem() = default;
    static void update(entt::registry &registry);
    static void init(entt::registry &registry);
};

#endif