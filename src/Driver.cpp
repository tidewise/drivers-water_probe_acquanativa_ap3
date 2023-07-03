#include "Driver.hpp"
#include <iostream>
#include <modbus/RTU.hpp>

using namespace water_probe_acquanativa_ap3;

Driver::Driver(int address)
    : m_address(address)
{
    // baud rate default is 9600
    // setInterframeDelay(base::Time::fromMicroseconds(3500));
}

int16_t Driver::readSingleRegister(int register_id)
{
    int16_t value = modbus::Master::readSingleRegister(m_address, false, register_id);
    return value;
}

ProbeMeasurements Driver::getMeasurements()
{
    ProbeMeasurements measurements;

    measurements.time = base::Time::now();
    measurements.oxygen_concentration =
        readSingleRegister(R_DISSOLVED_OXIGEN_MG_L) / std::pow<float>(10, 8);
    measurements.oxygen_saturation =
        readSingleRegister(R_DISSOLVED_OXIGEN_SAT) / std::pow<float>(10, 4);
    measurements.temperature =
        base::Temperature::fromCelsius(readSingleRegister(R_TEMPERATURE) / 100);
    measurements.pH = readSingleRegister(R_PH) / 100.0;
    measurements.conductivity =
        readSingleRegister(R_CONDUCTIVITY) / std::pow<float>(10, 10);
    measurements.salinity = readSingleRegister(R_SALINITY) / 100.0;
    measurements.dissolved_solids = readSingleRegister(R_DISSOLVED_SOLIDS) / std::pow<float>(10, 8);
    measurements.specific_gravity = readSingleRegister(R_SPECIFIC_GRAVITY) / 100.0;
    measurements.oxidation_reduction_potential =
        readSingleRegister(R_ORP) / std::pow<float>(10, 3);
    measurements.turbidity = readSingleRegister(R_TURBITY);
    measurements.height = readSingleRegister(R_HEIGHT);
    measurements.latitude = readSingleRegister(R_LATITUDE) / 100.0;
    measurements.longitude = readSingleRegister(R_LONGITUDE) / 100.0;

    return measurements;
}
