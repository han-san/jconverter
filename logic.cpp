#include <cassert>

#include "logic.hpp"

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

auto static meters_to_miles(double km) -> double
{
    return km * MILES_PER_METER;
}

auto static kelvin_to_fahrenheit(double kelvin) -> double
{
    return kelvin * 9. / 5. - 459.67;
}

auto static fahrenheit_to_kelvin(double fahrenheit) -> double
{
    return (fahrenheit + 459.67) * 5.0 / 9.0;
}

auto static lbs_to_grams(double lbs) -> double
{
    return lbs / LBS_PER_GRAM;
}

auto static grams_to_lbs(double grams) -> double
{
    return grams * LBS_PER_GRAM;
}

auto convert_meter(double value, Convert direction, DistanceUnit unit) -> double
{
    switch (unit) {
        case DistanceUnit::METERS: {
            return value;
        } break;
        case DistanceUnit::MILES: {
            return (direction == Convert::FROM) ? miles_to_meters(value) : meters_to_miles(value);
        } break;
        case DistanceUnit::FEET: {
            return (direction == Convert::FROM) ? feet_to_meters(value) : meters_to_feet(value);
        } break;
        case DistanceUnit::INCHES: {
            return (direction == Convert::FROM) ? inches_to_meters(value) : meters_to_inches(value);
        } break;
        default: {
            assert(false);
            return 1.;
        } break;
    }
};
