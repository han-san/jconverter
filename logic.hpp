#pragma once

#include <array>
#include <chrono>
#include <optional>
#include <ratio>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

namespace Distance {

// Distance unit ratios
using MetersPerFoot = std::ratio<3048, 10'000>;

using MetersPerInch = std::ratio_divide<MetersPerFoot, std::ratio<12>>;
using MetersPerBarleycorn = std::ratio_divide<MetersPerFoot, std::ratio<36>>;
using MetersPerThou = std::ratio_divide<MetersPerFoot, std::ratio<12'000>>;

using MetersPerYard = std::ratio_multiply<MetersPerFoot, std::ratio<3>>;
using MetersPerChain = std::ratio_multiply<MetersPerFoot, std::ratio<66>>;
using MetersPerFurlong = std::ratio_multiply<MetersPerFoot, std::ratio<660>>;
using MetersPerMile = std::ratio_multiply<MetersPerFoot, std::ratio<5'280>>;
using MetersPerLeague = std::ratio_multiply<MetersPerFoot, std::ratio<15'840>>;

using MetersPerFathom = std::ratio_multiply<std::ratio<1'852>, std::milli>;
using MetersPerCable = std::ratio_multiply<std::ratio<185'200>, std::milli>;
using MetersPerNauticalMile = std::ratio<1'852>;

using MetersPerLink = std::ratio_multiply<MetersPerFoot, std::ratio<66, 100>>;
using MetersPerRod = std::ratio_multiply<MetersPerFoot, std::ratio<66, 4>>;

template <typename Rep, typename Period = std::ratio<1>>
using Distance = std::chrono::duration<Rep, Period>;

using Millimeters = Distance<double, std::milli>;
using Centimeters = Distance<double, std::centi>;
using Meters = Distance<double>;
using Kilometers = Distance<double, std::kilo>;

namespace Imperial {

using Thou = Distance<double, MetersPerThou>;
using Barleycorns = Distance<double, MetersPerBarleycorn>;
using Inches = Distance<double, MetersPerInch>;
using Feet = Distance<double, MetersPerFoot>;
using Yards = Distance<double, MetersPerYard>;
using Chains = Distance<double, MetersPerChain>;
using Furlongs = Distance<double, MetersPerFurlong>;
using Miles = Distance<double, MetersPerMile>;
using Leagues = Distance<double, MetersPerLeague>;
using Fathoms = Distance<double, MetersPerFathom>;
using Cables = Distance<double, MetersPerCable>;
using NauticleMiles = Distance<double, MetersPerNauticalMile>;
using Links = Distance<double, MetersPerLink>;
using Rods = Distance<double, MetersPerRod>;

} // namespace Imperial

} // namespace Distance

namespace Volume {

// Volume unit ratios
using LitersPerPint = std::ratio<56'826'125, 100'000>;

using LitersPerGill = std::ratio_divide<LitersPerPint, std::ratio<4>>;
using LitersPerFluidOunce = std::ratio_divide<LitersPerPint, std::ratio<20>>;

using LitersPerQuart = std::ratio_multiply<LitersPerPint, std::ratio<2>>;
using LitersPerGallon = std::ratio_multiply<LitersPerPint, std::ratio<8>>;

template <typename Rep, typename Period = std::ratio<1>>
using Volume = std::chrono::duration<Rep, Period>;

namespace Imperial {

using FluidOunces = Volume<double, LitersPerFluidOunce>;
using Gills = Volume<double, LitersPerGill>;
using Pints = Volume<double, LitersPerPint>;
using Quarts = Volume<double, LitersPerQuart>;
using Gallons = Volume<double, LitersPerGallon>;

} // namespace Imperial

using Milliliters = Volume<double, std::milli>;
using Centiliters = Volume<double, std::centi>;
using Liters = Volume<double>;

} // namespace Volume

namespace Weight {

// Weight unit ratios
using GramsPerPound = std::ratio<45'359'237, 100'000>;
using GramsPerOunce = std::ratio_divide<GramsPerPound, std::ratio<16>>;
using GramsPerDrachm = std::ratio_divide<GramsPerPound, std::ratio<256>>;
using GramsPerGrain = std::ratio_divide<GramsPerPound, std::ratio<7000>>;
using GramsPerStone = std::ratio_multiply<GramsPerPound, std::ratio<14>>;
using GramsPerQuarter = std::ratio_multiply<GramsPerPound, std::ratio<28>>;
using GramsPerHundredweight =
    std::ratio_multiply<GramsPerPound, std::ratio<112>>;
using GramsPerTon = std::ratio_multiply<GramsPerPound, std::ratio<2240>>;
using GramsPerSlug = std::ratio<1'459'390'294, 100'000>;

template <typename Rep, typename Period = std::ratio<1>>
using Weight = std::chrono::duration<Rep, Period>;

namespace Imperial {

using Grains = Weight<double, GramsPerGrain>;
using Drachms = Weight<double, GramsPerDrachm>;
using Ounces = Weight<double, GramsPerOunce>;
using Pounds = Weight<double, GramsPerPound>;
using Stones = Weight<double, GramsPerStone>;
using Quarters = Weight<double, GramsPerQuarter>;
using Hundredweights = Weight<double, GramsPerHundredweight>;
using Tons = Weight<double, GramsPerTon>;
using Slugs = Weight<double, GramsPerSlug>;

} // namespace Imperial

using Milligrams = Weight<double, std::milli>;
using Grams = Weight<double>;
using Hectograms = Weight<double, std::hecto>;
using Kilograms = Weight<double, std::kilo>;
using Tonnes = Weight<double, std::mega>;

} // namespace Weight

auto const MILES_PER_METER = 0.0006213711922;
auto const LBS_PER_GRAM = 0.0022046226218;
auto const FEET_PER_METER = 3.280839895;
auto const INCHES_PER_METER = 39.3700787402;

enum class UnitTypes { temperature, distance, weight };

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

auto const unitStrings = std::array {
    std::string_view {"Celsius"},  std::string_view {"Fahrenheit"},
    std::string_view {"Kelvin"},

    std::string_view {"Meter"},    std::string_view {"Kilometer"},
    std::string_view {"Mile"},     std::string_view {"Foot"},
    std::string_view {"Inch"},

    std::string_view {"Pound"},    std::string_view {"Gram"},
    std::string_view {"Kilogram"},
};

auto const temperatures = std::unordered_set<Unit> {
    Unit::CELSIUS,
    Unit::FAHRENHEIT,
    Unit::KELVIN,
};

auto const distances = std::unordered_set<Unit> {
    Unit::KILOMETER, Unit::METER, Unit::MILE, Unit::FOOT, Unit::INCH,
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
    {"celsius", Unit::CELSIUS},
    {"c", Unit::CELSIUS},
    {"fahrenheit", Unit::FAHRENHEIT},
    {"f", Unit::FAHRENHEIT},
    {"kelvin", Unit::KELVIN},
    {"k", Unit::KELVIN},

    {"meter", Unit::METER},
    {"meters", Unit::METER},
    {"m", Unit::METER},
    {"km", Unit::KILOMETER},
    {"kilometer", Unit::KILOMETER},
    {"kilometers", Unit::KILOMETER},
    {"mile", Unit::MILE},
    {"miles", Unit::MILE},
    {"foot", Unit::FOOT},
    {"feet", Unit::FOOT},
    {"inch", Unit::INCH},
    {"inches", Unit::INCH},

    {"pound", Unit::LB},
    {"pounds", Unit::LB},
    {"lbs", Unit::LB},
    {"lb", Unit::LB},
    {"gram", Unit::GRAM},
    {"g", Unit::GRAM},
    {"grams", Unit::GRAM},
    {"kg", Unit::KILOGRAM},
    {"kilogram", Unit::KILOGRAM},
    {"kilograms", Unit::KILOGRAM},
};

auto convert(Unit fromUnit, Unit toUnit, double value) -> std::optional<double>;
