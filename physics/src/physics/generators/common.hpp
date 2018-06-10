#ifndef PHYSICS_GENERATORS_COMMON_HPP___
#define PHYSICS_GENERATORS_COMMON_HPP___

#include "physics/generators/literals.hpp"

// Length, Mass, Time, Current, Temperature, Luminous, Substance

using angle                 = si::unit<unit_data_type, 0, 0, 0, 0, 0, 0, 0>;

using solid_angle           = si::unit<unit_data_type, 0, 0, 0, 0, 0, 0, 0>;

using frequency             = si::unit<unit_data_type, 0, 0,-1, 0, 0, 0, 0>;

using force                 = si::unit<unit_data_type, 1, 1,-2, 0, 0, 0, 0>;

using weight                = si::unit<unit_data_type, 1, 1,-2, 0, 0, 0, 0>;

using pressure              = si::unit<unit_data_type,-1, 1,-2, 0, 0, 0, 0>;

using stress                = si::unit<unit_data_type,-1, 1,-2, 0, 0, 0, 0>;

using energy                = si::unit<unit_data_type, 2, 1,-2, 0, 0, 0, 0>;

using work                  = si::unit<unit_data_type, 2, 1,-2, 0, 0, 0, 0>;

using heat                  = si::unit<unit_data_type, 2, 1,-2, 0, 0, 0, 0>;

using power                 = si::unit<unit_data_type, 2, 1,-3, 0, 0, 0, 0>;

using charge                = si::unit<unit_data_type, 0, 0, 1, 1, 0, 0, 0>;

using voltage               = si::unit<unit_data_type, 2, 1,-3,-1, 0, 0, 0>;

using potential             = si::unit<unit_data_type, 2, 1,-3,-1, 0, 0, 0>;

using capacitance           = si::unit<unit_data_type,-2,-1, 4, 2, 0, 0, 0>;

using resistance            = si::unit<unit_data_type, 2, 1,-3,-2, 0, 0, 0>;

using impedance             = si::unit<unit_data_type, 2, 1,-3,-2, 0, 0, 0>;

using reactance             = si::unit<unit_data_type, 2, 1,-3,-2, 0, 0, 0>;

using conductance           = si::unit<unit_data_type, 2,-1, 3, 2, 0, 0, 0>;

using magnetic_flux         = si::unit<unit_data_type, 2, 1,-2,-1, 0, 0, 0>;

using magnetic_field        = si::unit<unit_data_type, 0, 1,-2,-1, 0, 0, 0>;

using magnetic_flux_density = si::unit<unit_data_type, 0, 1,-2,-1, 0, 0, 0>;

using inductance            = si::unit<unit_data_type, 2, 1,-2,-2, 0, 0, 0>;

using luminous_flux         = si::unit<unit_data_type, 0, 0, 0, 0, 0, 1, 0>;

using luminance             = si::unit<unit_data_type,-2, 0, 0, 0, 0, 1, 0>;

using radioactivity         = si::unit<unit_data_type, 0, 0,-1, 0, 0, 0, 0>;

using absorbed_dose         = si::unit<unit_data_type, 2, 0,-2, 0, 0, 0, 0>;

using equivalent_dose       = si::unit<unit_data_type, 2, 0,-2, 0, 0, 0, 0>;

using catalytic_activity    = si::unit<unit_data_type, 0, 0,-1, 0, 0, 0, 1>;



using area                  = si::unit<unit_data_type, 2, 0, 0, 0, 0, 0, 0>;

using volume                = si::unit<unit_data_type, 3, 0, 0, 0, 0, 0, 0>;

using speed                 = si::unit<unit_data_type, 1, 0,-1, 0, 0, 0, 0>;

using velocity              = si::unit<unit_data_type, 1, 0,-1, 0, 0, 0, 0>;

using acceleration          = si::unit<unit_data_type, 1, 0,-2, 0, 0, 0, 0>;

using angular_velocity      = si::unit<unit_data_type, 0, 0,-1, 0, 0, 0, 0>;

using angular_acceleration  = si::unit<unit_data_type, 0, 0,-2, 0, 0, 0, 0>;

using momentum              = si::unit<unit_data_type, 1, 1,-1, 0, 0, 0, 0>;

using impulse               = si::unit<unit_data_type, 1, 1,-1, 0, 0, 0, 0>;

using angular_momentum      = si::unit<unit_data_type, 2, 1,-2, 0, 0, 0, 0>;

using curvature             = si::unit<unit_data_type,-1, 0, 0, 0, 0, 0, 0>;

using area_density          = si::unit<unit_data_type,-2, 1, 0, 0, 0, 0, 0>;

using volume_density        = si::unit<unit_data_type,-3, 1, 0, 0, 0, 0, 0>;

using molarity              = si::unit<unit_data_type,-3, 0, 0, 0, 0, 0, 1>;

using molar_volume          = si::unit<unit_data_type, 3, 0, 0, 0, 0, 0,-1>;

using resistivity           = si::unit<unit_data_type, 3, 1,-3,-2, 0, 0, 0>;

using linear_mass_density   = si::unit<unit_data_type,-1, 1, 0, 0, 0, 0, 0>;

using linear_charge_density = si::unit<unit_data_type,-1, 0, 1, 1, 0, 0, 0>;

using moment_of_inertia     = si::unit<unit_data_type, 2, 1, 0, 0, 0, 0, 0>;

using radiance              = si::unit<unit_data_type, 0, 1,-3, 0, 0, 0, 0>;



namespace literals {

PHYSICS_GENERATE_LITERALS(unit_data_type, frequency, Hz)

PHYSICS_GENERATE_LITERALS(unit_data_type, force, N)

PHYSICS_GENERATE_LITERALS(unit_data_type, pressure, Pa)

PHYSICS_GENERATE_LITERALS(unit_data_type, energy, J)

PHYSICS_GENERATE_LITERALS(unit_data_type, power, W)

PHYSICS_GENERATE_LITERALS(unit_data_type, charge, C)

PHYSICS_GENERATE_LITERALS(unit_data_type, voltage, V)

PHYSICS_GENERATE_LITERALS(unit_data_type, capacitance, F)

PHYSICS_GENERATE_LITERALS(unit_data_type, resistance, Ohm)

PHYSICS_GENERATE_LITERALS(unit_data_type, conductance, S)

PHYSICS_GENERATE_LITERALS(unit_data_type, magnetic_flux, Wb)

PHYSICS_GENERATE_LITERALS(unit_data_type, magnetic_field, T)

PHYSICS_GENERATE_LITERALS(unit_data_type, inductance, H)

PHYSICS_GENERATE_LITERALS(unit_data_type, luminous_flux, lm)

PHYSICS_GENERATE_LITERALS(unit_data_type, radioactivity, Bq)

PHYSICS_GENERATE_LITERALS(unit_data_type, absorbed_dose, Gy)

PHYSICS_GENERATE_LITERALS(unit_data_type, equivalent_dose, Sv)

PHYSICS_GENERATE_LITERALS(unit_data_type, catalytic_activity, kat)

} // literals

#endif // PHYSICS_GENERATORS_COMMON_HPP___
