#include <base/Float.hpp>
#include <base/Temperature.hpp>
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

    EXPECT_MODBUS_READ(57, false, 0, {756});
    EXPECT_MODBUS_READ(57, false, 1, {85});
    EXPECT_MODBUS_READ(57, false, 2, {200});
    EXPECT_MODBUS_READ(57, false, 3, {646});
    EXPECT_MODBUS_READ(57, false, 4, {156});
    EXPECT_MODBUS_READ(57, false, 5, {126});
    EXPECT_MODBUS_READ(57, false, 6, {1256});
    EXPECT_MODBUS_READ(57, false, 7, {32});
    EXPECT_MODBUS_READ(57, false, 8, {40});
    EXPECT_MODBUS_READ(57, false, 9, {3});
    EXPECT_MODBUS_READ(57, false, 10, {500});
    EXPECT_MODBUS_READ(57, false, 11, {1});
    EXPECT_MODBUS_READ(57, false, 12, {76});

    auto measurements = driver.getMeasurements();

    ASSERT_FLOAT_EQ(756 * std::pow(10, -5), measurements.oxygen_concentration);
    ASSERT_FLOAT_EQ(85 * std::pow(10, -4), measurements.oxygen_saturation);
    ASSERT_FLOAT_EQ(275.15, measurements.temperature.getKelvin());
    ASSERT_FLOAT_EQ(646 * std::pow(10, -2), measurements.pH);
    ASSERT_FLOAT_EQ(156 * std::pow(10, -6), measurements.conductivity);
    ASSERT_FLOAT_EQ(126 * std::pow(10, -2), measurements.salinity);
    ASSERT_FLOAT_EQ(1256 * std::pow(10, -8), measurements.dissolved_solids);
    ASSERT_FLOAT_EQ(32 * std::pow(10, -2), measurements.specific_gravity);
    ASSERT_FLOAT_EQ(40 * std::pow(10, -3), measurements.oxidation_reduction_potential);
    ASSERT_FLOAT_EQ(3, measurements.turbidity);
    ASSERT_FLOAT_EQ(500, measurements.height);
    ASSERT_FLOAT_EQ(1 * std::pow(10, -2), measurements.latitude);
    ASSERT_FLOAT_EQ(76 * std::pow(10, -2), measurements.longitude);
}
