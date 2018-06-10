#ifndef PHYSICS_GENERATORS_BASE_HPP___
#define PHYSICS_GENERATORS_BASE_HPP___

#include "physics/generators/literals.hpp"

// Length, Mass, Time, Current, Temperature, Luminous, Substance

using scalar      = si::unit<unit_data_type, 0, 0, 0, 0, 0, 0, 0>;

using length      = si::unit<unit_data_type, 1, 0, 0, 0, 0, 0, 0>;

using mass        = si::unit<unit_data_type, 0, 1, 0, 0, 0, 0, 0>;

using time        = si::unit<unit_data_type, 0, 0, 1, 0, 0, 0, 0>;

using current     = si::unit<unit_data_type, 0, 0, 0, 1, 0, 0, 0>;

using temperature = si::unit<unit_data_type, 0, 0, 0, 0, 1, 0, 0>;

using luminous    = si::unit<unit_data_type, 0, 0, 0, 0, 0, 1, 0>;

using substance   = si::unit<unit_data_type, 0, 0, 0, 0, 0, 0, 1>;



namespace literals {

PHYSICS_GENERATE_LITERALS(unit_data_type, length, m)

PHYSICS_GENERATE_LITERALS(unit_data_type, mass, g)

PHYSICS_GENERATE_LITERALS(unit_data_type, time, s)

PHYSICS_GENERATE_LITERALS(unit_data_type, current, A)

PHYSICS_GENERATE_LITERALS(unit_data_type, temperature, K)

PHYSICS_GENERATE_LITERALS(unit_data_type, luminous, cd)

PHYSICS_GENERATE_LITERALS(unit_data_type, substance, mol)

} // literals

#endif // PHYSICS_GENERATORS_BASE_HPP___
