#ifndef WATER_PROBE_ACQUANATIVA_AP3_DRIVER_HPP_
#define WATER_PROBE_ACQUANATIVA_AP3_DRIVER_HPP_

#include <base/Float.hpp>
#include <modbus/Master.hpp>
#include <water_probe_acquanativa_ap3/ProbeMeasurements.hpp>

namespace water_probe_acquanativa_ap3 {
    /**
     * Driver for the Acquanativa Acqua Probe AP3 sensor
     */
    class Driver : public modbus::Master {
        // the default address has to be 57
        int m_address;

        uint16_t readSingleRegister(unsigned int register_id);

    public:
        enum Registers {
            R_OXYGEN_CONCENTRATION = 0,
            R_OXYGEN_SATURATION = 1,
            R_TEMPERATURE = 2,
            R_PH = 3,
            R_CONDUCTIVITY = 4,
            R_SALINITY = 5,
            R_DISSOLVED_SOLIDS = 6,
            R_SPECIFIC_GRAVITY = 7,
            R_OXIDATION_REDUCTION_POTENTIAL = 8,
            R_TURBIDITY = 9,
            R_HEIGHT = 10,
            R_LATITUDE = 11,
            R_LONGITUDE = 12
        };

        Driver(int address);

        ProbeMeasurements getMeasurements();
        static float calculateSalinity(float conductivity, base::Temperature const& temperature);
        static float calculateConductivity(uint16_t conductivity,
            base::Temperature const& temperature,
            float salinity);
        float calculateTDS(uint16_t conductivity);

        struct ConductivityWorkaroundResult {
            enum Attempts {
                RAW, WITH_BIT15, INVERTED_WITH_BIT15, WITH_BIT16,
                SIZE
            };

            float conductivity[SIZE];
            float salinity[SIZE];
        };

        static ConductivityWorkaroundResult calculateConductivityWorkaround(
            uint16_t conductivity,
            base::Temperature temperature);
    };

}

#endif
