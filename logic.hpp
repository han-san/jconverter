#pragma once

#include <unordered_map>
#include <unordered_set>
#include <optional>

auto const MILES_PER_METER = 0.0006213711922;
auto const LBS_PER_GRAM = 0.0022046226218;
auto const FEET_PER_METER = 3.280839895;
auto const INCHES_PER_METER = 39.3700787402;

enum class Unit {
    CELSIUS,
    FAHRENHEIT,
    KELVIN,

    KILOMETER,
    METER,
    MILE,
    FOOT,
    INCH,

    LB,
    GRAM,
    KILOGRAM,
};

auto const temperatures = std::unordered_set<Unit> {
    Unit::CELSIUS,
    Unit::FAHRENHEIT,
    Unit::KELVIN,
};

auto const distances = std::unordered_set<Unit> {
    Unit::KILOMETER,
    Unit::METER,
    Unit::MILE,
    Unit::FOOT,
    Unit::INCH,
};


auto const weights = std::unordered_set<Unit> {
    Unit::LB,
    Unit::KILOGRAM,
    Unit::GRAM,
};

auto const unitTypes = {
    &temperatures,
    &distances,
    &weights,
};

auto const stringToUnitMap = std::unordered_map<std::string_view, Unit> {
    { "celsius", Unit::CELSIUS },
    { "c", Unit::CELSIUS },
    { "fahrenheit", Unit::FAHRENHEIT },
    { "f", Unit::FAHRENHEIT },
    { "kelvin", Unit::KELVIN },
    { "k", Unit::KELVIN },

    { "meter", Unit::METER },
    { "meters", Unit::METER },
    { "m", Unit::METER },
    { "km", Unit::KILOMETER },
    { "kilometer", Unit::KILOMETER },
    { "kilometers", Unit::KILOMETER },
    { "mile", Unit::MILE },
    { "miles", Unit::MILE },
    { "foot", Unit::FOOT },
    { "feet", Unit::FOOT },
    { "inch", Unit::INCH },
    { "inches", Unit::INCH },

    { "pound", Unit::LB },
    { "pounds", Unit::LB },
    { "lbs", Unit::LB },
    { "lb", Unit::LB },
    { "gram", Unit::GRAM },
    { "g", Unit::GRAM },
    { "grams", Unit::GRAM },
    { "kg", Unit::KILOGRAM },
    { "kilogram", Unit::KILOGRAM },
    { "kilograms", Unit::KILOGRAM },
};

auto convert(Unit fromUnit, Unit toUnit, double value) -> std::optional<double>;
