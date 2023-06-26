#include <gtest/gtest.h>
#include <iodrivers_base/FixtureGTest.hpp>
#include <test_Driver.hpp>
#include <water_probe_acquanativa_ap3/Driver.hpp>

using namespace water_probe_acquanativa_ap3;

struct test_Driver { test_Driver() };

TEST_F(test_Driver, it_reads_probe_parameters) {
    IODRIVERS_BASE_MOCK();

    driver.getMeasurements();

    ProbeMeasurements measurements;
    measurements.temperature = 12;
    measurements.salinity = 30;
}

