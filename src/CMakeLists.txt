rock_library(water_probe_acquanativa_ap3
    SOURCES Driver.cpp
    HEADERS Driver.hpp
    DEPS_PKGCONFIG base-types modbus)

rock_executable(water_probe_acquanativa_ap3_bin Main.cpp
    DEPS water_probe_acquanativa_ap3)

