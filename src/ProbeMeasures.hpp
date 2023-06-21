#ifndef WATER_PROBE_ACQUANATIVA_AP3_PROBE_MEASURES_HPP
#define WATER_PROBE_ACQUANATIVA_AP3_PROBE_MEASURES_HPP

#include <base/Float.hpp>

namespace water_probe_acquanativa_ap3 {
    struct ProbeMeasures {
        /** Motor nominal current */
        float dissolved_oxygen_mgL = base::unknown<float>();

        /** Motor nominal speed */
        float dissolved_oxygen_sat = base::unknown<float>();

        /** Motor nominal speed */
        float temperature = base::unknown<float>();

        /** Motor nominal current */
        float ph = base::unknown<float>();

        /** Motor nominal current */
        float oxidation_reduction = base::unknown<float>();

        /** Motor nominal torque */
        float conductivity = base::unknown<float>();

        /** Motor power in W */
        float salinity = base::unknown<float>();

        /** Motor nominal torque */
        float dissolved_solids = base::unknown<float>();

        /** Motor power in W */
        float turbity = base::unknown<float>();

        /** Motor power in W */
        float chlorophyll = base::unknown<float>();
    };
}

#endif