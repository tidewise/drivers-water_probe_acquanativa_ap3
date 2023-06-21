// #include <water_probe_acquanativa_ap3/Driver.hpp>
#include "Driver.hpp"
#include <modbus/RTU.hpp>
#include <iostream>

using namespace std;
using namespace water_probe_acquanativa_ap3;

Driver::Driver(int address) : m_address(address) {
    // baud rate default is 9600
    // setInterframeDelay(base::Time::fromMicroseconds(10));
}

void Driver::prepare() {
    writeSingleRegister(R_CONFIGURATION, 1);

}

void Driver::saveConfiguration() {
    modbus::Master::writeSingleRegister(m_address, R_CONFIG_SAVE, 1);
}

void Driver::enable() {}

void Driver::disable() {}

ProbeMeasurements Driver::getMeasurements () {
    ProbeMeasurements measurements ;
    measurements.time = base::Time::now();
    measurements.dissolved_oxygen_mgL = readSingleRegister<float>(R_DISSOLVED_OXIGEN_MG_L) / 100 * 1000;
    measurements.dissolved_oxygen_sat = readSingleRegister<float>(R_DISSOLVED_OXIGEN_SAT) / 100;
    measurements.temperature = base::Temperature::fromCelsius(readSingleRegister<float>(R_TEMPERATURE) / 100);
    measurements.ph = readSingleRegister<float>(R_PH) / 100;
    measurements.conductivity = readSingleRegister<float>(R_CONDUCTIVITY) / 100 * (10^6);
    measurements.salinity = readSingleRegister<float>(R_SALINITY) / 100;
    measurements.dissolved_solids = readSingleRegister<float>(R_DISSOLVED_SOLIDS) / 100;
    measurements.specific_gravity = readSingleRegister<float>(R_SPECIFIC_GRAVITY) / 100;
    measurements.oxidation_reduction_potencial = readSingleRegister<float>(R_OXIDATION_REDUCTION_POTENCIAL) / 100 * (10^6);
    measurements.turbity = readSingleRegister<float>(R_TURBITY);

    return measurements;
}
