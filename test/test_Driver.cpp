#include <base/Temperature.hpp>
#include <gtest/gtest.h>
#include <iodrivers_base/FixtureGTest.hpp>
#include <water_probe_acquanativa_ap3/Driver.hpp>

#include "Helpers.hpp"

using namespace water_probe_acquanativa_ap3;

struct DriverAddress : public Driver {
    DriverAddress() : Driver(57) {
    }
};

struct DriverTest : public testing::Test,
                     public iodrivers_base::Fixture<DriverAddress>,
                     public Helpers<DriverTest>  {
    DriverTest()
        : Helpers<DriverTest>(*this) {
    }
};


TEST_F(DriverTest, it_reads_probe_parameters) {
    IODRIVERS_BASE_MOCK();

    EXPECT_MODBUS_READ(1, false, 0, { 756 });
    EXPECT_MODBUS_READ(1, false, 1, { 85 });
    EXPECT_MODBUS_READ(1, false, 2, { 200 });
    EXPECT_MODBUS_READ(1, false, 3, { 646 });
    EXPECT_MODBUS_READ(1, false, 4, { 156 });
    EXPECT_MODBUS_READ(1, false, 5, { 126 });
    EXPECT_MODBUS_READ(1, false, 6, { 1256 });
    EXPECT_MODBUS_READ(1, false, 7, { 32 });
    EXPECT_MODBUS_READ(1, false, 8, { 40 });
    EXPECT_MODBUS_READ(1, false, 9, { 3 });
    EXPECT_MODBUS_READ(1, false, 10, { 500 });
    EXPECT_MODBUS_READ(1, false, 11, { 1 });
    EXPECT_MODBUS_READ(1, false, 12, { 76 });

    auto measurements = driver.getMeasurements();
    // double d_temperature = base::Temperature::celsius2Kelvin(measurements.temperature);

    ASSERT_FLOAT_EQ(756, measurements.concentration);
    ASSERT_FLOAT_EQ(85, measurements.saturation);
    // ASSERT_DOUBLE_EQ(200, measurements.temperature);
    ASSERT_FLOAT_EQ(646, measurements.ph);
    ASSERT_FLOAT_EQ(156, measurements.conductivity);
    ASSERT_FLOAT_EQ(126, measurements.salinity);
    ASSERT_FLOAT_EQ(1256, measurements.dissolved_solids);
    ASSERT_FLOAT_EQ(32, measurements.specific_gravity);
    ASSERT_FLOAT_EQ(40, measurements.ORP);
    ASSERT_FLOAT_EQ(3, measurements.turbity);
    ASSERT_FLOAT_EQ(500, measurements.height);
    ASSERT_FLOAT_EQ(1, measurements.latitude);
    ASSERT_FLOAT_EQ(76, measurements.longitude);
}