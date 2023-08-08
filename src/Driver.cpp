#include "Driver.hpp"
#include <iostream>
#include <modbus/RTU.hpp>

using namespace water_probe_acquanativa_ap3;

Driver::Driver(int address)
    : m_address(address)
{
}

uint16_t Driver::readSingleRegister(unsigned int register_id)
{
    return modbus::Master::readSingleRegister(m_address, false, register_id);
}

ProbeMeasurements Driver::getMeasurements()
{
    ProbeMeasurements measurements;

    measurements.time = base::Time::now();
    measurements.oxygen_concentration =
        readSingleRegister(R_OXYGEN_CONCENTRATION) / 100.0 * 1e-6 / 1e-3;
    measurements.oxygen_saturation = readSingleRegister(R_OXYGEN_SATURATION) * 1e-4;
    measurements.temperature =
        base::Temperature::fromCelsius(readSingleRegister(R_TEMPERATURE) / 100.0);
    measurements.pH = readSingleRegister(R_PH) / 100.0;
    measurements.conductivity = readSingleRegister(R_CONDUCTIVITY) / 100.0 * 1e-6 / 1e-2;
    measurements.salinity = readSingleRegister(R_SALINITY) / 100.0 * 1e-3;
    measurements.dissolved_solids = readSingleRegister(R_DISSOLVED_SOLIDS) / 100.0 * 1e-6;
    measurements.specific_gravity = readSingleRegister(R_SPECIFIC_GRAVITY) / 100.0;
    measurements.oxidation_reduction_potential =
        readSingleRegister(R_OXIDATION_REDUCTION_POTENTIAL) * 1e-3;
    measurements.turbidity = readSingleRegister(R_TURBIDITY);
    measurements.height = static_cast<int16_t>(readSingleRegister(R_HEIGHT));
    measurements.latitude = static_cast<int16_t>(readSingleRegister(R_LATITUDE)) / 100.0;
    measurements.longitude =
        static_cast<int16_t>(readSingleRegister(R_LONGITUDE)) / 100.0;

    return measurements;
}
