#include "Driver.hpp"
#include <bit>
#include <bitset>
#include <cstring>
#include <iostream>
#include <modbus/RTU.hpp>
#include <vector>

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

    measurements.conductivity =
        conductivityCheck(conductivity, measurements.temperature, measurements.salinity);
    return measurements;
}

float Driver::conductivityCheck(uint16_t conductivity,
    base::Temperature temperature,
    float salinity)
{
    float temp = temperature.getCelsius();

    // caso 0: valor sem mudanca
    float case_0 = conductivity;
    std::cout << "case_0: " << case_0;

    // caso 1: trocar o último bit (bit15)
    std::bitset<16> bit_case_1{conductivity};
    bit_case_1 = bit_case_1.flip(15);
    float case_1 = bit_case_1.to_ulong();
    std::cout << "case_1: " << case_1;

    // caso 2: inverter todos os bits
    std::bitset<16> bit_case_2{conductivity};
    bit_case_2.flip();
    float case_2 = bit_case_2.to_ulong();
    std::cout << "case_2: " << case_2;

    // caso 3: inverter todos os bits e bit15 para 1 (negativo)
    std::bitset<16> m_case_3{conductivity};
    m_case_3.flip();
    m_case_3.set(15, true);
    float case_3 = m_case_3.to_ulong();
    std::cout << "case_3: " << case_3;

    float error0 = abs(calculateSalinity(case_0, temp) - salinity);
    float error1 = abs(calculateSalinity(case_1, temp) - salinity);
    float error2 = abs(calculateSalinity(case_2, temp) - salinity);
    float error3 = abs(calculateSalinity(case_3, temp) - salinity);

    std::map<float, float> aux_map = {
        {error0, case_0},
        {error1, case_1},
        {error2, case_2},
        {error3, case_3}
    };

    std::map<float, float>::iterator it = aux_map.begin();
    return it->second;
}

float Driver::calculateSalinity(float conductivity, float temperature)
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
    double temp_c = 25;

    if ((temperature > -50 && temperature <= 100)) {
        ratio = conductivity / 42914;
        ratio =
            ratio /
            (c0 + temperature *
                      (c1 + temperature * (c2 + temperature * (c3 + temperature * c4))));
        ratio_sqr = sqrt(ratio);
        ds = b0 +
             ratio_sqr *
                 (b1 + ratio_sqr *
                           (b2 + ratio_sqr * (b3 + ratio_sqr * (b4 + ratio_sqr * b5))));
        ds = ds * ((temperature - 15.0) / (1.0 + 0.0162 * (temperature - 15.0)));

        salinity =
            (float)a0 +
            ratio_sqr *
                (a1 + ratio_sqr *
                          (a2 + ratio_sqr * (a3 + ratio_sqr * (a4 + ratio_sqr * a5)))) +
            ds;
    }
    else {

        ratio = conductivity / 42914;
        ratio =
            ratio / (c0 + temp_c * (c1 + temp_c * (c2 + temp_c * (c3 + temp_c * c4))));
        ratio_sqr = sqrt(ratio);
        ds = b0 +
             ratio_sqr *
                 (b1 + ratio_sqr *
                           (b2 + ratio_sqr * (b3 + ratio_sqr * (b4 + ratio_sqr * b5))));
        ds = ds * ((temp_c - 15.0) / (1.0 + 0.0162 * (temp_c - 15.0)));

        salinity =
            (float)a0 +
            ratio_sqr *
                (a1 + ratio_sqr *
                          (a2 + ratio_sqr * (a3 + ratio_sqr * (a4 + ratio_sqr * a5)))) +
            ds;
    }

    if (salinity < 0)
        return 0;
    else
        return salinity;
}


// Total dissolved solids
// float Driver::calculateTDS(float conductivity)
// {
//     float tds;
//     tds = 0, 65 * conductivity;
//     return tds;
// }