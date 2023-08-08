#include <gtest/gtest.h>
#include <iodrivers_base/FixtureGTest.hpp>
#include <water_probe_acquanativa_ap3/Driver.hpp>

#include "Helpers.hpp"

using namespace water_probe_acquanativa_ap3;

struct DriverAddress : public Driver {
    DriverAddress()
        : Driver(57)
    {
    }
};

struct DriverTest : public testing::Test,
                    public iodrivers_base::Fixture<DriverAddress>,
                    public Helpers<DriverTest> {
    DriverTest()
        : Helpers<DriverTest>(*this)
    {
    }
};

TEST_F(DriverTest, it_reads_and_converts_probe_parameters)
{
    IODRIVERS_BASE_MOCK();

    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_OXYGEN_CONCENTRATION, {756});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_OXYGEN_SATURATION, {85});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_TEMPERATURE, {200});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_PH, {646});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_CONDUCTIVITY, {156});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_SALINITY, {126});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_DISSOLVED_SOLIDS, {1256});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_SPECIFIC_GRAVITY, {32});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_OXIDATION_REDUCTION_POTENTIAL, {40});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_TURBIDITY, {3});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_HEIGHT, {500});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_LATITUDE, {1});
    EXPECT_MODBUS_READ(57, false, Driver::Registers::R_LONGITUDE, {76});

    auto measurements = driver.getMeasurements();

    ASSERT_FLOAT_EQ(756 / 100.0 * 1e-6 / 1e-3, measurements.oxygen_concentration);
    ASSERT_FLOAT_EQ(85 * 1e-4, measurements.oxygen_saturation);
    ASSERT_FLOAT_EQ(275.15, measurements.temperature.getKelvin());
    ASSERT_FLOAT_EQ(646 / 100.0, measurements.pH);
    ASSERT_FLOAT_EQ(156 / 100.0 * 1e-6 / 1e-2, measurements.conductivity);
    ASSERT_FLOAT_EQ(126 / 100.0 * 1e-3, measurements.salinity);
    ASSERT_FLOAT_EQ(1256 / 100.0 * 1e-6, measurements.dissolved_solids);
    ASSERT_FLOAT_EQ(32 / 100.0, measurements.specific_gravity);
    ASSERT_FLOAT_EQ(40 * 1e-3, measurements.oxidation_reduction_potential);
    ASSERT_FLOAT_EQ(3, measurements.turbidity);
    ASSERT_FLOAT_EQ(500, measurements.height);
    ASSERT_FLOAT_EQ(1 / 100.0, measurements.latitude);
    ASSERT_FLOAT_EQ(76 / 100.0, measurements.longitude);
}
