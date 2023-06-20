#include <boost/test/unit_test.hpp>
#include <water_probe_acquanativa_ap3/Dummy.hpp>

using namespace water_probe_acquanativa_ap3;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    water_probe_acquanativa_ap3::DummyClass dummy;
    dummy.welcome();
}
