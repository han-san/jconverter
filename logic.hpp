#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <optional>
#include <ratio>
#include <string_view>
#include <unordered_map>
#include <variant>

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

using MetersPerLightyear = std::ratio<9'460'730'472'580'800>;

template <typename Rep, typename Period = std::ratio<1>>
using Distance = std::chrono::duration<Rep, Period>;

using Millimeters = Distance<double, std::milli>;
using Centimeters = Distance<double, std::centi>;
using Decimeters = Distance<double, std::deci>;
using Meters = Distance<double>;
using Kilometers = Distance<double, std::kilo>;

using Lightyears = Distance<double, MetersPerLightyear>;

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

class Unit {
public:
  enum class Type { temperature, distance, weight };

  enum class Temperature {
    celsius,
    fahrenheit,
    kelvin,
  };

  enum class Distance {
    millimeter,
    centimeter,
    decimeter,
    meter,
    kilometer,

    lightyear,

    thou,
    barleycorn,
    inch,
    foot,
    yard,
    furlong,
    mile,
    league,

    fathom,
    cable,
    nauticalMile,

    link,
    rod,
  };

  enum class Weight {
    lb,
    gram,
    kilogram,
  };

  // WARNING: The constructor relies on the specific order of Variant's template
  // arguments. If they are reordered the constructor must be updated to reflect
  // the change.
  using Variant = std::variant<Temperature, Distance, Weight>;

  explicit Unit(Variant const unit) : m_unit {unit} {
    m_type = [this] {
      // The order of Variant's template arguments determines which Type should
      // be returned.
      switch (m_unit.index()) {
      case 0:
        return Type::temperature;
      case 1:
        return Type::distance;
      case 2:
        return Type::weight;
      case std::variant_npos:
      default:
        static_assert(std::variant_size_v<Variant> == 3,
                      "Unit's constructor must be updated to reflect a change "
                      "in Unit::Variant's number of template arguments");
        // Unreachable unless the switch doesn't cover all of Variant's
        // possible enumerations or m_unit has thrown an exception that was
        // handled but left it in an invalid state.
        std::terminate();
      }
    }();
  }

private:
  auto friend convert(Unit const& fromUnit, Unit const& toUnit, double value)
      -> std::optional<double>;

  [[nodiscard]] auto type() const noexcept -> Type { return m_type; }

  [[nodiscard]] auto weight() const { return std::get<Weight>(m_unit); }

  [[nodiscard]] auto distance() const { return std::get<Distance>(m_unit); }

  [[nodiscard]] auto temperature() const {
    return std::get<Temperature>(m_unit);
  }

  Type m_type {};
  Variant m_unit {};
};

std::array const unitStrings {
    std::string_view {"Celsius"},       std::string_view {"Fahrenheit"},
    std::string_view {"Kelvin"},

    std::string_view {"Millimeter"},    std::string_view {"Centimeter"},
    std::string_view {"Decimeter"},     std::string_view {"Meter"},
    std::string_view {"Kilometer"},     std::string_view {"Light-year"},
    std::string_view {"Thou"},          std::string_view {"Barleycorn"},
    std::string_view {"Inch"},          std::string_view {"Foot"},
    std::string_view {"Yard"},          std::string_view {"Furlong"},
    std::string_view {"Mile"},          std::string_view {"League"},
    std::string_view {"Fathom"},        std::string_view {"Cable"},
    std::string_view {"Nautical Mile"}, std::string_view {"Link"},
    std::string_view {"Rod"},

    std::string_view {"Pound"},         std::string_view {"Gram"},
    std::string_view {"Kilogram"},
};

auto convert(Unit const& fromUnit, Unit const& toUnit, double value)
    -> std::optional<double>;
