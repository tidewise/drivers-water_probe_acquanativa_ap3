// #include <water_probe_acquanativa_ap3/Driver.hpp>
#include "Driver.hpp"
#include <modbus/RTU.hpp>
#include <iostream>

using namespace std;
using namespace water_probe_acquanativa_ap3;

void Driver::prepare() {
    writeSingleRegister(R_CONFIGURATION, 1);

}

void Driver::saveConfiguration() {
    modbus::Master::writeSingleRegister(m_address, R_CONFIG_SAVE, 1);
}

void Driver::enable() {}

void Driver::disable() {}

ProbeMeasures Driver::getMeasures() {
    ProbeMeasures measures;
    measures.dissolved_oxygen_mgL = readSingleRegister<float>(R_DISSOLVED_OXIGEN_MG_L) / 100;
    measures.dissolved_oxygen_sat = readSingleRegister<float>(R_DISSOLVED_OXIGEN_SAT) / 100;
    measures.temperature = readSingleRegister<float>(R_TEMPERATURE) / 100;
    measures.ph = readSingleRegister<float>(R_PH);
    measures.oxidation_reduction = readSingleRegister<float>(R_OXIDATION_REDUCTION_POTENCIAL);
    measures.conductivity = readSingleRegister<float>(R_CONDUCTIVITY);
    measures.salinity = readSingleRegister<float>(R_SALINITY);
    measures.dissolved_solids = readSingleRegister<float>(R_DISSOLVED_SOLIDS);
    measures.turbity = readSingleRegister<float>(R_TURBITY);
    measures.chlorophyll = readSingleRegister<float>(R_CHLOROPHYLL);

    return measures;
}
