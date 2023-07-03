#include <iostream>
#include <water_probe_acquanativa_ap3/Driver.hpp>

using namespace water_probe_acquanativa_ap3;

int main(int argc, char** argv)
{
    std::string uri = argv[1];
    int id = std::atoi(argv[2]);

    Driver driver(id);
    driver.openURI(uri);

    auto measurings = driver.getMeasurements();
    std::cout << "Measures: \n"
              << "Time: " << measurings.time << "\n"
              << "DO:  " << measurings.oxygen_concentration << " Kg/L\n"
              << "DO:  " << measurings.oxygen_saturation << " %\n"
              << "Temperature:  " << measurings.temperature.getKelvin() << " K\n"
              << "pH: " << measurings.pH << "\n"
              << "Conductivity: " << measurings.conductivity << " S/m\n"
              << "Salinity: " << measurings.salinity << " ppt\n"
              << "Dissolved solids: " << measurings.dissolved_solids << " \n"
              << "Specific gravity: " << measurings.specific_gravity << "\n"
              << "ORP: " << measurings.oxidation_reduction_potential << " V\n"
              << "Turbidity: " << measurings.turbidity << " NTU\n"
              << "Height: " << measurings.height << " m\n"
              << "Latitude: " << measurings.latitude << " °\n"
              << "Longitude: " << measurings.longitude << " °\n";

    driver.close();

    return 0;
}
