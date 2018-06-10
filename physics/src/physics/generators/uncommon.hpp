#ifndef PHYSICS_GENERATORS_UNCOMMON_HPP___
#define PHYSICS_GENERATORS_UNCOMMON_HPP___

#include "physics/generators/literals.hpp"

// Length, Mass, Time, Current, Temperature, Luminous, Substance

using volumetric_flow       = si::unit<unit_data_type, 3, 0,-1, 0, 0, 0, 0>;

using jerk                  = si::unit<unit_data_type, 1, 0,-3, 0, 0, 0, 0>;

using jolt                  = si::unit<unit_data_type, 1, 0,-3, 0, 0, 0, 0>;

using snap                  = si::unit<unit_data_type, 1, 0,-4, 0, 0, 0, 0>;

using jounce                = si::unit<unit_data_type, 1, 0,-4, 0, 0, 0, 0>;

using torque                = si::unit<unit_data_type, 2, 1,-2, 0, 0, 0, 0>;

using moment_of_force       = si::unit<unit_data_type, 2, 1,-2, 0, 0, 0, 0>;

using yank                  = si::unit<unit_data_type, 1, 1,-3, 0, 0, 0, 0>;



namespace literals {

} // literals

#endif // PHYSICS_GENERATORS_UNCOMMON_HPP___
