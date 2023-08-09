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
              << "Temperature:  " << measurings.temperature.getCelsius() << " C\n"
              << "pH: " << measurings.pH << "\n"
              << "Conductivity: " << measurings.conductivity / 1e-6 * 1e-2 << " uS/cm\n"
              << "Salinity: " << measurings.salinity * 1000 << " ppt\n"
              << "Dissolved solids: " << measurings.dissolved_solids * 1e6 << " ppm\n"
              << "Specific gravity: " << measurings.specific_gravity << "\n"
              << "ORP: " << measurings.oxidation_reduction_potential << " V\n"
              << "Turbidity: " << measurings.turbidity << " NTU\n"
              << "Height: " << measurings.height << " m\n"
              << "Latitude: " << measurings.latitude << " °\n"
              << "Longitude: " << measurings.longitude << " °\n";

    auto workaround = driver.calculateConductivityWorkaround(
        measurings.raw_conductivity, measurings.temperature
    );

    std::cout << "Conductivity calculations:\n"
              << "Conductivities:\n"
              << "raw: " << workaround.conductivity[0] << "\n"
              << "with_bit15: " << workaround.conductivity[1] << "\n"
              << "inverted_with_bit15: " << workaround.conductivity[2] << "\n"
              << "with_bit16: " << workaround.conductivity[3] << "\n"
              << "Salinities:\n"
              << "raw: " << workaround.salinity[0] << "\n"
              << "with_bit15: " << workaround.salinity[1] << "\n"
              << "inverted_with_bit15: " << workaround.salinity[2] << "\n"
              << "with_bit16: " << workaround.salinity[3] << "\n";

    driver.close();

    return 0;
}
