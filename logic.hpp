#pragma once

auto const MILES_PER_METER = 0.0006213711922;
auto const LBS_PER_GRAM = 0.0022046226218;
auto const FEET_PER_METER = 3.280839895;
auto const INCHES_PER_METER = 39.3700787402;

enum class DistanceUnit {
    METERS,
    MILES,
    FEET,
    INCHES,
};

enum class Convert {
    FROM,
    TO,
};

auto convert_meter(double value, Convert direction, DistanceUnit unit) -> double;
