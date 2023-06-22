// #include <water_probe_acquanativa_ap3/Driver.hpp>
#include "Driver.hpp"
#include <modbus/RTU.hpp>
#include <iostream>

using namespace water_probe_acquanativa_ap3;

Driver::Driver(int address) : m_address(address) {
    // baud rate default is 9600
    setInterframeDelay(base::Time::fromMicroseconds(10));
}

template<typename T>
T decodeRegister(uint16_t value);

template<> uint16_t decodeRegister(uint16_t value) {
    return value;
}

template<> int16_t decodeRegister(uint16_t value) {
    return reinterpret_cast<int16_t&>(value);
}

template<> float decodeRegister(uint16_t value) {
    return static_cast<float>(decodeRegister<int16_t>(value));
}

template<typename T>
T Driver::readSingleRegister(int register_id) {
    uint16_t value = modbus::Master::readSingleRegister(m_address, false, register_id);
    return decodeRegister<T>(value);
}

ProbeMeasurements Driver::getMeasurements () {
    ProbeMeasurements measurements ;
    float scale = std::pow(10,6) / 100.0;

    measurements.time = base::Time::now();
    measurements.dissolved_oxygen_mgL = readSingleRegister<float>(R_DISSOLVED_OXIGEN_MG_L) / 100 * 1000;
    measurements.dissolved_oxygen_sat = readSingleRegister<float>(R_DISSOLVED_OXIGEN_SAT) / 100;
    measurements.temperature = base::Temperature::fromCelsius(readSingleRegister<float>(R_TEMPERATURE) / 100);
    measurements.ph = readSingleRegister<float>(R_PH) / 100;
    measurements.conductivity = readSingleRegister<float>(R_CONDUCTIVITY) * scale;
    measurements.salinity = readSingleRegister<float>(R_SALINITY) / 100;
    measurements.dissolved_solids = readSingleRegister<float>(R_DISSOLVED_SOLIDS) / 100;
    measurements.specific_gravity = readSingleRegister<float>(R_SPECIFIC_GRAVITY) / 100;
    measurements.oxidation_reduction_potencial = readSingleRegister<float>(R_OXIDATION_REDUCTION_POTENCIAL) * scale;
    measurements.turbity = readSingleRegister<float>(R_TURBITY);

    return measurements;
}
