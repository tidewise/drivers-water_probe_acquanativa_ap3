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

        enum Registers {
            R_DISSOLVED_OXIGEN_MG_L         = 0,
            R_DISSOLVED_OXIGEN_SAT          = 1,
            R_TEMPERATURE                   = 2,
            R_PH                            = 3,
            R_CONDUCTIVITY                  = 4,
            R_SALINITY                      = 5,
            R_DISSOLVED_SOLIDS              = 6,
            R_SPECIFIC_GRAVITY              = 7,
            R_ORP = 8,
            R_TURBITY                       = 9,
            R_HEIGHT                        = 10,
            R_LATITUDE                      = 11,
            R_LONGITUDE                     = 12

        };

        template<typename T>
        T readSingleRegister(int register_id);

    public:
        Driver(int address);

        ProbeMeasurements getMeasurements();
    };

}

#endif
