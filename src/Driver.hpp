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
        int m_address;

        enum Registers {
            R_DISSOLVED_OXIGEN_MG_L         = 1,
            R_DISSOLVED_OXIGEN_SAT          = 2,
            R_TEMPERATURE                   = 3,
            R_PH                            = 4,
            R_CONDUCTIVITY                  = 5,
            R_SALINITY                      = 6,
            R_DISSOLVED_SOLIDS              = 7,
            R_SPECIFIC_GRAVITY              = 8,
            R_OXIDATION_REDUCTION_POTENCIAL = 9,
            R_TURBITY = 10
        };

        template<typename T>
        T readSingleRegister(int register_id);

    public:
        Driver(int address);

        ProbeMeasurements getMeasurements();
    };

}

#endif
