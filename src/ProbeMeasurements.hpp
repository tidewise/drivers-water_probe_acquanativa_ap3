#ifndef WATER_PROBE_ACQUANATIVA_AP3_PROBE_MEASUREMENTS_HPP
#define WATER_PROBE_ACQUANATIVA_AP3_PROBE_MEASUREMENTS_HPP

#include <base/Float.hpp>
#include <base/Temperature.hpp>

namespace water_probe_acquanativa_ap3 {
    struct ProbeMeasurements {
        base::Time time;
        
        /** Water dissolved oxygen concentration in Kg/L */
        float dissolved_oxygen_mgL = base::unknown<float>();

        /** Water dissolved oxygen % saturation */
        float dissolved_oxygen_sat = base::unknown<float>();

        /** Water temperature in K */
        base::Temperature temperature;

        /** Water pH */
        float ph = base::unknown<float>();

        /** Water conductivity in S/cm*/
        float conductivity = base::unknown<float>();

        /** Water salinity in PSU */
        float salinity = base::unknown<float>();

        /** Water dissolved solids concentration in ppm */
        float dissolved_solids = base::unknown<float>();

        /** Water oxidation reduction potencial in V */
        float specific_gravity = base::unknown<float>();

        /** Water oxidation reduction potencial in V */
        float oxidation_reduction_potencial = base::unknown<float>();

        /** Water turbity in NTU */
        float turbity = base::unknown<float>();
    };
}

#endif