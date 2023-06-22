#include <iostream>
#include <water_probe_acquanativa_ap3/Driver.hpp>

using namespace water_probe_acquanativa_ap3;

int main(int argc, char** argv)
{
    std::cout << "start program" <<std::endl;
    std::string uri = argv[1];
    int id = std::atoi(argv[2]);

    Driver driver(id);
    driver.openURI(uri);
    std::cout << "start LEITURA" << std::endl;
    auto measurings = driver.getMeasurements();
    std::cout << "Measures: \n"
              << "Time: " << measurings.time << "\n"
              << "DO:  " << measurings.dissolved_oxygen_mgL << " Kg/L\n"
              << "DO:  " << measurings.dissolved_oxygen_sat << " %\n"
              << "Temperature:  " << measurings.temperature << " K\n"
              << "pH: " << measurings.ph << "\n"
              << "Conductivity: " << measurings.conductivity << "S/m\n"
              <<"Salinity: " << measurings.salinity << "PSU\n"
              << "Dissolved solids: " << measurings.dissolved_solids << "ppm\n"
              << "Specific gravity: " << measurings.specific_gravity << "\n"
              << "ORP: " << measurings.oxidation_reduction_potencial << " V\n"
              << "Turbity: " << measurings.turbity << " NTU\n" << std::endl;

    driver.close();

    return 0;
}
