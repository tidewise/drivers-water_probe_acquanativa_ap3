#ifndef WATER_PROBE_ACQUANATIVA_AP3_DRIVER_HPP_
#define WATER_PROBE_ACQUANATIVA_AP3_DRIVER_HPP_

#include <base/Float.hpp>
#include <modbus/Master.hpp>
#include <water_probe_acquanativa_ap3/ProbeMeasures.hpp>

namespace water_probe_acquanativa_ap3 {
    /**
     * Driver for the Acquanativa Acqua Probe AP3 sensor
     */
    class Driver : public modbus::Master {
        int m_address;

        enum Registers {
            R_CONFIGURATION                 = 0,
            R_DISSOLVED_OXIGEN_MG_L         = 1,
            R_DISSOLVED_OXIGEN_SAT          = 2,
            R_TEMPERATURE                   = 3,
            R_PH                            = 4,
            R_OXIDATION_REDUCTION_POTENCIAL = 5,
            R_CONDUCTIVITY                  = 6,
            R_SALINITY                      = 7,
            R_DISSOLVED_SOLIDS              = 8,
            R_TURBITY                       = 9,
            R_CHLOROPHYLL                   = 10,

            R_CONFIG_SAVE                   = 30
        };

        template<typename T>
        T readSingleRegister(int register_id);

        template<typename T>
        void writeSingleRegister(int register_id, T value);

    public:
        Driver(int address);

        /** Prepare the unit to receive control from the driver without enabling power */
        void prepare();

        /** Save the current configuration*/
        void saveConfiguration();

        /** Enable the sensor control and give control to the serial interface */
        void enable();

        /**
         * Disable the sensor control and give control away from to the serial
         * interface
         */
        void disable();

        ProbeMeasures getMeasures();


    };

}

#endif
