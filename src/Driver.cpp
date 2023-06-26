// #include <water_probe_acquanativa_ap3/Driver.hpp>
#include "Driver.hpp"
#include <modbus/RTU.hpp>
#include <iostream>

using namespace water_probe_acquanativa_ap3;

Driver::Driver(int address) : m_address(address) {
    // baud rate default is 9600
    // setInterframeDelay(base::Time::fromMicroseconds(3500));
}

template<typename T>
T decodeRegister(int16_t value);

template<> uint8_t decodeRegister(int16_t value) {
    return value;
}

template<> int16_t decodeRegister(int16_t value) {
    return reinterpret_cast<int16_t&>(value);
}

template<> float decodeRegister(int16_t value) {
    return static_cast<float>(decodeRegister<int16_t>(value));
}

template<typename T>
T Driver::readSingleRegister(int register_id) {
    int16_t value = modbus::Master::readSingleRegister(m_address, false, register_id);
    return decodeRegister<T>(value);
}

ProbeMeasurements Driver::getMeasurements () {
    ProbeMeasurements measurements;

    measurements.time = base::Time::now();
    measurements.concentration = readSingleRegister<float>(R_DISSOLVED_OXIGEN_MG_L) / std::pow(10,5);
    measurements.saturation = readSingleRegister<float>(R_DISSOLVED_OXIGEN_SAT) / 100;
    measurements.temperature = base::Temperature::fromCelsius(readSingleRegister<float>(R_TEMPERATURE) / 100);
    measurements.ph = readSingleRegister<float>(R_PH) / 100;
    measurements.conductivity = readSingleRegister<float>(R_CONDUCTIVITY) / std::pow(10,10);
    measurements.salinity = readSingleRegister<float>(R_SALINITY) / 100;
    measurements.dissolved_solids = readSingleRegister<float>(R_DISSOLVED_SOLIDS) / 100;
    measurements.specific_gravity = readSingleRegister<float>(R_SPECIFIC_GRAVITY) / 100;
    measurements.oxidation_reduction_potencial = readSingleRegister<float>(R_OXIDATION_REDUCTION_POTENCIAL) / std::pow(10,3);
    measurements.turbity = readSingleRegister<float>(R_TURBITY);
    measurements.height = readSingleRegister<float>(R_HEIGHT);
    measurements.latitude = readSingleRegister<float>(R_LATITUDE) / 100;
    measurements.longitude = readSingleRegister<float>(R_LONGITUDE) / 100;

    return measurements;
}
