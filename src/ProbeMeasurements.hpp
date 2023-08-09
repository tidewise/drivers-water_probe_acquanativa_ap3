#ifndef WATER_PROBE_ACQUANATIVA_AP3_PROBE_MEASUREMENTS_HPP
#define WATER_PROBE_ACQUANATIVA_AP3_PROBE_MEASUREMENTS_HPP

#include <base/Float.hpp>
#include <base/Temperature.hpp>
#include <base/Time.hpp>

namespace water_probe_acquanativa_ap3 {
    struct ProbeMeasurements {
        base::Time time;

        /** Water dissolved oxygen concentration in Kg/m³ */
        float oxygen_concentration = base::unknown<float>();

        /** Water dissolved oxygen % saturation e.g. 0.1 = 10% */
        float oxygen_saturation = base::unknown<float>();

        /** Water temperature in K */
        base::Temperature temperature;

        /** Water pH */
        float pH = base::unknown<float>();

        /** Water conductivity in S/m*/
        uint16_t raw_conductivity = 0;

        /** Water conductivity in S/m*/
        float conductivity = base::unknown<float>();

        /** Water salinity (fractional [0, 1]) */
        float salinity = base::unknown<float>();

        /** Water dissolved solids concentration (fractional [0, 1])*/
        float dissolved_solids = base::unknown<float>();

        /** Water specific gravity */
        float specific_gravity = base::unknown<float>();

        /** Oxidation reduction potential in V */
        float oxidation_reduction_potential = base::unknown<float>();

        /** Water turbidity in Nephelometric Turbidity Unit (NTU)*/
        float turbidity = base::unknown<float>();

        /** Sensor height in m */
        float height = base::unknown<float>();

        /** Sensor latitude */
        float latitude = base::unknown<float>();

        /** Sensor longitude */
        float longitude = base::unknown<float>();
    };
}

#endif
