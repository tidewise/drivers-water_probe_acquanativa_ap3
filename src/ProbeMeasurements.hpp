#ifndef WATER_PROBE_ACQUANATIVA_AP3_PROBE_MEASUREMENTS_HPP
#define WATER_PROBE_ACQUANATIVA_AP3_PROBE_MEASUREMENTS_HPP

#include <base/Float.hpp>
#include <base/Temperature.hpp>

namespace water_probe_acquanativa_ap3 {
    struct ProbeMeasurements {
        base::Time time;
        
        /** Water dissolved oxygen concentration in mg/L */
        float dissolved_oxygen_mgL = base::unknown<float>();

        /** Water dissolved oxygen % saturation */
        float dissolved_oxygen_sat = base::unknown<float>();

        /** Water temperature in °C */
        base::Temperature temperature;

        /** Water pH */
        float ph = base::unknown<float>();

        /** Water oxidation reduction potencial in mV */
        float oxidation_reduction_potencial = base::unknown<float>();

        /** Water conductivity in uS/cm*/
        float conductivity = base::unknown<float>();

        /** Water salinity in PSU */
        float salinity = base::unknown<float>();

        /** Water dissolved solids concentration in ppm */
        float dissolved_solids = base::unknown<float>();

        /** Water turbity in NTU */
        float turbity = base::unknown<float>();

        /** Water chlorophyll in ug/L */
        float chlorophyll = base::unknown<float>();
    };
}

#endif