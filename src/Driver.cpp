#include "Driver.hpp"
#include <bit>
#include <bitset>
#include <cstring>
#include <iostream>
#include <modbus/RTU.hpp>
#include <vector>
#include <algorithm>

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
    // measurements.conductivity = readSingleRegister(R_CONDUCTIVITY) / 100.0 * 1e-6 /
    // 1e-2;
    auto conductivity = readSingleRegister(R_CONDUCTIVITY);
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

    measurements.raw_conductivity = conductivity;
    measurements.conductivity =
        calculateConductivity(conductivity, measurements.temperature, measurements.salinity);
    return measurements;
}

Driver::ConductivityWorkaroundResult Driver::calculateConductivityWorkaround(
    uint16_t conductivity,
    base::Temperature temperature)
{

    ConductivityWorkaroundResult result;
    result.conductivity[ConductivityWorkaroundResult::RAW] = conductivity;
    result.conductivity[ConductivityWorkaroundResult::WITH_BIT15] =
        conductivity | 1 << 15;
    result.conductivity[ConductivityWorkaroundResult::INVERTED_WITH_BIT15] =
        ~conductivity | 1 << 15;
    result.conductivity[ConductivityWorkaroundResult::WITH_BIT16] =
        static_cast<uint32_t>(conductivity) | 1 << 16;

    for (int i = 0; i < ConductivityWorkaroundResult::SIZE; ++i) {
        result.salinity[i] = calculateSalinity(result.conductivity[i], temperature);
    }

    return result;
}

float Driver::calculateConductivity(uint16_t conductivity,
    base::Temperature const& temperature,
    float salinity)
{
    auto workaround = calculateConductivityWorkaround(conductivity, temperature);

    auto min_it = std::min_element(
        workaround.salinity,
        workaround.salinity + ConductivityWorkaroundResult::SIZE,
        [salinity](float a, float b) { return abs(a - salinity) < abs(b - salinity); });

    return workaround.conductivity[min_it - workaround.salinity];
}

float Driver::calculateSalinity(float conductivity, base::Temperature const& temperature)
{
    double ratio;
    double ratio_sqr;
    double ds;
    float salinity;

    double a0 = 0.008;
    double a1 = -0.1692;
    double a2 = 25.3851;
    double a3 = 14.0941;
    double a4 = -7.0261;
    double a5 = 2.7081;

    double b0 = 0.0005;
    double b1 = -0.0056;
    double b2 = -0.0066;
    double b3 = -0.0375;
    double b4 = 0.0636;
    double b5 = -0.0144;

    double c0 = 0.6766097;
    double c1 = 0.0200564;
    double c2 = 0.0001104259;
    double c3 = -0.00000069698;
    double c4 = 0.0000000010031;
    float temp_c = temperature.getCelsius();
    if (temp_c <= -50 || temp_c > 100) {
        temp_c = 25;
    }

    ratio = conductivity / 42914;
    ratio = ratio / (c0 + temp_c * (c1 + temp_c * (c2 + temp_c * (c3 + temp_c * c4))));
    ratio_sqr = sqrt(ratio);
    ds = b0 + ratio_sqr *
                  (b1 + ratio_sqr *
                            (b2 + ratio_sqr * (b3 + ratio_sqr * (b4 + ratio_sqr * b5))));
    ds = ds * ((temp_c - 15.0) / (1.0 + 0.0162 * (temp_c - 15.0)));

    return (float)a0 +
           ratio_sqr *
               (a1 + ratio_sqr *
                         (a2 + ratio_sqr * (a3 + ratio_sqr * (a4 + ratio_sqr * a5)))) +
           ds;
}

// Total dissolved solids
// float Driver::calculateTDS(float conductivity)
// {
//     float tds;
//     tds = 0, 65 * conductivity;
//     return tds;
// }