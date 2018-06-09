#ifndef PHYSICS_GENERATE_HPP___
#define PHYSICS_GENERATE_HPP___

#include "literal_generator.hpp"

namespace base {

using scalar_t      = unit<unit_data_type, 0, 0, 0, 0, 0, 0, 0>;

using length_t      = unit<unit_data_type, 1, 0, 0, 0, 0, 0, 0>;

using mass_t        = unit<unit_data_type, 0, 1, 0, 0, 0, 0, 0>;

using time_t        = unit<unit_data_type, 0, 0, 1, 0, 0, 0, 0>;

using current_t     = unit<unit_data_type, 0, 0, 0, 1, 0, 0, 0>;

using temperature_t = unit<unit_data_type, 0, 0, 0, 0, 1, 0, 0>;

using luminous_t    = unit<unit_data_type, 0, 0, 0, 0, 0, 1, 0>;

using substance_t   = unit<unit_data_type, 0, 0, 0, 0, 0, 0, 1>;

} // base



namespace literals {

PHYSICS_GENERATE_LITERALS(unit_data_type, base::length_t, m)

PHYSICS_GENERATE_LITERALS(unit_data_type, base::mass_t, g)

PHYSICS_GENERATE_LITERALS(unit_data_type, base::time_t, s)

PHYSICS_GENERATE_LITERALS(unit_data_type, base::current_t, A)

PHYSICS_GENERATE_LITERALS(unit_data_type, base::temperature_t, K)

PHYSICS_GENERATE_LITERALS(unit_data_type, base::luminous_t, cd)

PHYSICS_GENERATE_LITERALS(unit_data_type, base::substance_t, mol)

} // literals

#endif // PHYSICS_GENERATE_HPP___
