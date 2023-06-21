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
    measurements.ph = readSingleRegister<float>(R_PH);
    measurements.oxidation_reduction_potencial = readSingleRegister<float>(R_OXIDATION_REDUCTION_POTENCIAL) * (10^6);
    measurements.conductivity = readSingleRegister<float>(R_CONDUCTIVITY) * (10^6);
    measurements.salinity = readSingleRegister<float>(R_SALINITY);
    measurements.dissolved_solids = readSingleRegister<float>(R_DISSOLVED_SOLIDS);
    measurements.turbity = readSingleRegister<float>(R_TURBITY);
    measurements.chlorophyll = readSingleRegister<float>(R_CHLOROPHYLL) * (10^9);

    return measurements;
}
