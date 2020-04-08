#include <cassert>

#include "logic.hpp"

// Distances
auto static inches_to_meters(double inches) -> double
{
    return inches / INCHES_PER_METER;
}

auto static meters_to_inches(double meters) -> double
{
    return meters * INCHES_PER_METER;
}

auto static feet_to_meters(double feet) -> double
{
    return feet / FEET_PER_METER;
}

auto static meters_to_feet(double meters) -> double
{
    return meters * FEET_PER_METER;
}

auto static miles_to_meters(double miles) -> double
{
    return miles / MILES_PER_METER;
}

auto static meters_to_miles(double meters) -> double
{
    return meters * MILES_PER_METER;
}

auto static meters_to_kilometers(double meters) -> double
{
    return meters / 1000.;
}

auto static kilometers_to_meters(double kilometers) -> double
{
    return kilometers * 1000.;
}

// Temperatures
auto static kelvin_to_fahrenheit(double kelvin) -> double
{
    return kelvin * 9. / 5. - 459.67;
}

auto static fahrenheit_to_kelvin(double fahrenheit) -> double
{
    return (fahrenheit + 459.67) * 5.0 / 9.0;
}

auto static celsius_to_kelvin(double celsius) -> double {
    return celsius + 273.15;
}

auto static kelvin_to_celsius(double kelvin) -> double {
    return kelvin - 273.15;
}

// Weights
auto static lbs_to_grams(double lbs) -> double
{
    return lbs / LBS_PER_GRAM;
}

auto static grams_to_lbs(double grams) -> double
{
    return grams * LBS_PER_GRAM;
}

auto static grams_to_kilograms(double grams) -> double
{
    return grams / 1000.;
}

auto static kilograms_to_grams(double kilograms) -> double
{
    return kilograms * 1000.;
}

auto contains(std::unordered_set<Unit> const& unitSet, Unit unit) {
    return unitSet.find(unit) != unitSet.cend();
}

// returns empty optional if units are of different types (e.g. distance and temperature)
auto convert(Unit fromUnit, Unit toUnit, double value) -> std::optional<double>
{
    for (auto unitType : unitTypes) {
        if (contains(*unitType, fromUnit) && !contains(*unitType, toUnit)) {
            return {};
        }
    }

    auto const base = [value, fromUnit] () {
        switch (fromUnit) {
            // Distances
            case Unit::METER: {
                return value;
            } break;
            case Unit::KILOMETER: {
                return kilometers_to_meters(value);
            } break;
            case Unit::MILE: {
                return miles_to_meters(value);
            } break;
            case Unit::FOOT: {
                return feet_to_meters(value);
            } break;
            case Unit::INCH: {
                return inches_to_meters(value);
            } break;

            // Temperatures
            case Unit::KELVIN: {
                return value;
            } break;
            case Unit::CELSIUS: {
                return celsius_to_kelvin(value);
            } break;
            case Unit::FAHRENHEIT: {
                return fahrenheit_to_kelvin(value);
            } break;

            // Weight
            case Unit::GRAM: {
                return value;
            } break;
            case Unit::KILOGRAM: {
                return kilograms_to_grams(value);
            } break;
            case Unit::LB: {
                return lbs_to_grams(value);
            } break;
        }
    }();

    auto const result = [base, toUnit] () {
        switch (toUnit) {
            // Distances
            case Unit::METER: {
                return base;
            } break;
            case Unit::KILOMETER: {
                return meters_to_kilometers(base);
            } break;
            case Unit::MILE: {
                return meters_to_miles(base);
            } break;
            case Unit::FOOT: {
                return meters_to_feet(base);
            } break;
            case Unit::INCH: {
                return meters_to_inches(base);
            } break;

            // Temperatures
            case Unit::KELVIN: {
                return base;
            } break;
            case Unit::CELSIUS: {
                return kelvin_to_celsius(base);
            } break;
            case Unit::FAHRENHEIT: {
                return kelvin_to_fahrenheit(base);
            } break;

            // Weight
            case Unit::GRAM: {
                return base;
            } break;
            case Unit::KILOGRAM: {
                return grams_to_kilograms(base);
            } break;
            case Unit::LB: {
                return grams_to_lbs(base);
            } break;
        }
    }();

    return result;
}
