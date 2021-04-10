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
using LitersPerPint = std::ratio<56'826'125, 100'000'000>;

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
  enum class Type { temperature, distance, weight, volume };

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
    milligram,
    gram,
    hectogram,
    kilogram,
    tonne,

    grain,
    drachm,
    ounce,
    lb,
    stone,
    quarter,
    hundredweight,
    ton,
    slug
  };

  enum class Volume {
    milliliter,
    centiliter,
    liter,

    fluidOunce,
    gill,
    pint,
    quart,
    gallon
  };

  // WARNING: The constructor relies on the specific order of Variant's template
  // arguments. If they are reordered the constructor must be updated to reflect
  // the change.
  using Variant = std::variant<Temperature, Distance, Weight, Volume>;

  explicit constexpr Unit(Variant const unit) : m_unit {unit} {
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
      case 3:
        return Type::volume;
      case std::variant_npos:
      default:
        static_assert(std::variant_size_v<Variant> == 4,
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
  friend auto constexpr convert(Unit const& fromUnit, Unit const& toUnit,
                                double value) -> std::optional<double>;

  [[nodiscard]] auto constexpr type() const noexcept -> Type { return m_type; }

  [[nodiscard]] auto constexpr weight() const {
    return std::get<Weight>(m_unit);
  }

  [[nodiscard]] auto constexpr distance() const {
    return std::get<Distance>(m_unit);
  }

  [[nodiscard]] auto constexpr temperature() const {
    return std::get<Temperature>(m_unit);
  }

  [[nodiscard]] auto constexpr volume() const {
    return std::get<Volume>(m_unit);
  }

  Type m_type {};
  Variant m_unit {};
};

std::array constexpr temperatureStrings {
    std::string_view {"Celsius"},
    std::string_view {"Fahrenheit"},
    std::string_view {"Kelvin"},
};

std::array constexpr distanceStrings {
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
};

std::array constexpr weightStrings {
    std::string_view {"Milligram"}, std::string_view {"Gram"},
    std::string_view {"Hectogram"}, std::string_view {"Kilogram"},
    std::string_view {"Tonne"},     std::string_view {"Grain"},
    std::string_view {"Drachm"},    std::string_view {"Ounce"},
    std::string_view {"Pound"},     std::string_view {"Stone"},
    std::string_view {"Quarter"},   std::string_view {"Hundredweight"},
    std::string_view {"Ton"},       std::string_view {"Slug"},
};

std::array constexpr volumeStrings {
    std::string_view {"Milliliter"}, std::string_view {"Centiliter"},
    std::string_view {"Liter"},      std::string_view {"Fluid Ounce"},
    std::string_view {"Gill"},       std::string_view {"Pint"},
    std::string_view {"Quart"},      std::string_view {"Gallon"},
};

namespace impl {

// Temperatures
auto constexpr kelvin_to_fahrenheit(double const kelvin) -> double {
  return kelvin * 9. / 5. - 459.67;
}

auto constexpr fahrenheit_to_kelvin(double const fahrenheit) -> double {
  return (fahrenheit + 459.67) * 5.0 / 9.0;
}

auto constexpr celsius_to_kelvin(double const celsius) -> double {
  return celsius + 273.15;
}

auto constexpr kelvin_to_celsius(double const kelvin) -> double {
  return kelvin - 273.15;
}

auto constexpr to_meters(Unit::Distance const fromUnit, double const value)
    -> Distance::Meters {
  using namespace Distance;
  switch (fromUnit) {
  case Unit::Distance::millimeter:
    return Millimeters {value};
  case Unit::Distance::centimeter:
    return Centimeters {value};
  case Unit::Distance::decimeter:
    return Decimeters {value};
  case Unit::Distance::meter:
    return Meters {value};
  case Unit::Distance::kilometer:
    return Kilometers {value};
  case Unit::Distance::lightyear:

    return Lightyears {value};
  case Unit::Distance::thou:

    return Imperial::Thou {value};
  case Unit::Distance::barleycorn:
    return Imperial::Barleycorns {value};
  case Unit::Distance::inch:
    return Imperial::Inches {value};
  case Unit::Distance::foot:
    return Imperial::Feet {value};
  case Unit::Distance::yard:
    return Imperial::Yards {value};
  case Unit::Distance::furlong:
    return Imperial::Furlongs {value};
  case Unit::Distance::mile:
    return Imperial::Miles {value};
  case Unit::Distance::league:
    return Imperial::Leagues {value};

  case Unit::Distance::fathom:
    return Imperial::Fathoms {value};
  case Unit::Distance::cable:
    return Imperial::Cables {value};
  case Unit::Distance::nauticalMile:
    return Imperial::NauticleMiles {value};

  case Unit::Distance::link:
    return Imperial::Links {value};
  case Unit::Distance::rod:
    return Imperial::Rods {value};
  }
  // Unreachable unless not all Unit::Distance enumerators are covered in the
  // switch.
  std::terminate();
}

auto constexpr from_meters(Distance::Meters const meters,
                           Unit::Distance const toUnit) -> double {
  using namespace Distance;
  switch (toUnit) {
  case Unit::Distance::millimeter:
    return Millimeters {meters}.count();
  case Unit::Distance::centimeter:
    return Centimeters {meters}.count();
  case Unit::Distance::decimeter:
    return Decimeters {meters}.count();
  case Unit::Distance::meter:
    return meters.count();
  case Unit::Distance::kilometer:
    return Kilometers {meters}.count();

  case Unit::Distance::lightyear:
    return Lightyears {meters}.count();
  case Unit::Distance::thou:

    return Imperial::Thou {meters}.count();
  case Unit::Distance::barleycorn:
    return Imperial::Barleycorns {meters}.count();
  case Unit::Distance::inch:
    return Imperial::Inches {meters}.count();
  case Unit::Distance::foot:
    return Imperial::Feet {meters}.count();
  case Unit::Distance::yard:
    return Imperial::Yards {meters}.count();
  case Unit::Distance::furlong:
    return Imperial::Furlongs {meters}.count();
  case Unit::Distance::mile:
    return Imperial::Miles {meters}.count();
  case Unit::Distance::league:
    return Imperial::Leagues {meters}.count();

  case Unit::Distance::fathom:
    return Imperial::Fathoms {meters}.count();
  case Unit::Distance::cable:
    return Imperial::Cables {meters}.count();
  case Unit::Distance::nauticalMile:
    return Imperial::NauticleMiles {meters}.count();

  case Unit::Distance::link:
    return Imperial::Links {meters}.count();
  case Unit::Distance::rod:
    return Imperial::Rods {meters}.count();
  }
  // Unreachable unless not all Unit::Distance enumerators are covered in the
  // switch.
  std::terminate();
}

auto constexpr to_grams(Unit::Weight const fromUnit, double const value)
    -> Weight::Grams {
  using namespace Weight;
  switch (fromUnit) {
  case Unit::Weight::milligram:
    return Milligrams {value};
  case Unit::Weight::gram:
    return Grams {value};
  case Unit::Weight::hectogram:
    return Hectograms {value};
  case Unit::Weight::kilogram:
    return Kilograms {value};
  case Unit::Weight::tonne:
    return Tonnes {value};

  case Unit::Weight::grain:
    return Imperial::Grains {value};
  case Unit::Weight::drachm:
    return Imperial::Drachms {value};
  case Unit::Weight::ounce:
    return Imperial::Ounces {value};
  case Unit::Weight::lb:
    return Imperial::Pounds {value};
  case Unit::Weight::stone:
    return Imperial::Stones {value};
  case Unit::Weight::quarter:
    return Imperial::Quarters {value};
  case Unit::Weight::hundredweight:
    return Imperial::Hundredweights {value};
  case Unit::Weight::ton:
    return Imperial::Tons {value};
  case Unit::Weight::slug:
    return Imperial::Slugs {value};
  }
  // Unreachable unless not all Unit::Weight enumerators are covered in the
  // switch.
  std::terminate();
}

auto constexpr from_grams(Weight::Grams const grams, Unit::Weight const toUnit)
    -> double {
  using namespace Weight;
  switch (toUnit) {
  case Unit::Weight::milligram:
    return Milligrams {grams}.count();
  case Unit::Weight::gram:
    return Grams {grams}.count();
  case Unit::Weight::hectogram:
    return Hectograms {grams}.count();
  case Unit::Weight::kilogram:
    return Kilograms {grams}.count();
  case Unit::Weight::tonne:
    return Tonnes {grams}.count();

  case Unit::Weight::grain:
    return Imperial::Grains {grams}.count();
  case Unit::Weight::drachm:
    return Imperial::Drachms {grams}.count();
  case Unit::Weight::ounce:
    return Imperial::Ounces {grams}.count();
  case Unit::Weight::lb:
    return Imperial::Pounds {grams}.count();
  case Unit::Weight::stone:
    return Imperial::Stones {grams}.count();
  case Unit::Weight::quarter:
    return Imperial::Quarters {grams}.count();
  case Unit::Weight::hundredweight:
    return Imperial::Hundredweights {grams}.count();
  case Unit::Weight::ton:
    return Imperial::Tons {grams}.count();
  case Unit::Weight::slug:
    return Imperial::Slugs {grams}.count();
  }
  // Unreachable unless not all Unit::Weight enumerators are covered in the
  // switch.
  std::terminate();
}

auto constexpr to_kelvin(Unit::Temperature const fromUnit, double const value)
    -> double {
  switch (fromUnit) {
  case Unit::Temperature::kelvin:
    return value;
  case Unit::Temperature::celsius:
    return celsius_to_kelvin(value);
  case Unit::Temperature::fahrenheit:
    return fahrenheit_to_kelvin(value);
  }
  // Unreachable unless not all Unit::Temperature enumerators are covered in the
  // switch.
  std::terminate();
}

auto constexpr from_kelvin(double const kelvin, Unit::Temperature const toUnit)
    -> double {
  switch (toUnit) {
  case Unit::Temperature::kelvin:
    return kelvin;
  case Unit::Temperature::celsius:
    return kelvin_to_celsius(kelvin);
  case Unit::Temperature::fahrenheit:
    return kelvin_to_fahrenheit(kelvin);
  }
  // Unreachable unless not all Unit::Temperature enumerators are covered in the
  // switch.
  std::terminate();
}

auto constexpr to_liters(Unit::Volume fromUnit, double const value)
    -> Volume::Liters {
  using namespace Volume;
  switch (fromUnit) {
  case Unit::Volume::milliliter:
    return Milliliters {value};
  case Unit::Volume::centiliter:
    return Centiliters {value};
  case Unit::Volume::liter:
    return Liters {value};
  case Unit::Volume::fluidOunce:
    return Imperial::FluidOunces {value};
  case Unit::Volume::gill:
    return Imperial::Gills {value};
  case Unit::Volume::pint:
    return Imperial::Pints {value};
  case Unit::Volume::quart:
    return Imperial::Quarts {value};
  case Unit::Volume::gallon:
    return Imperial::Gallons {value};
  }
  // Unreachable unless not all Unit::Volume enumerators are covered in the
  // switch.
  std::terminate();
}

auto constexpr from_liters(Volume::Liters const liters, Unit::Volume toUnit)
    -> double {
  using namespace Volume;
  switch (toUnit) {
  case Unit::Volume::milliliter:
    return Milliliters {liters}.count();
  case Unit::Volume::centiliter:
    return Centiliters {liters}.count();
  case Unit::Volume::liter:
    return Liters {liters}.count();
  case Unit::Volume::fluidOunce:
    return Imperial::FluidOunces {liters}.count();
  case Unit::Volume::gill:
    return Imperial::Gills {liters}.count();
  case Unit::Volume::pint:
    return Imperial::Pints {liters}.count();
  case Unit::Volume::quart:
    return Imperial::Quarts {liters}.count();
  case Unit::Volume::gallon:
    return Imperial::Gallons {liters}.count();
  }
  // Unreachable unless not all Unit::Volume enumerators are covered in the
  // switch.
  std::terminate();
}

} // namespace impl

auto constexpr convert(Unit::Distance const fromUnit,
                       Unit::Distance const toUnit, double const value)
    -> double {
  using namespace impl;
  return from_meters(to_meters(fromUnit, value), toUnit);
}

auto constexpr convert(Unit::Weight const fromUnit, Unit::Weight const toUnit,
                       double const value) -> double {
  using namespace impl;
  return from_grams(to_grams(fromUnit, value), toUnit);
}

auto constexpr convert(Unit::Temperature const fromUnit,
                       Unit::Temperature const toUnit, double const value)
    -> double {
  using namespace impl;
  return from_kelvin(to_kelvin(fromUnit, value), toUnit);
}

auto constexpr convert(Unit::Volume const fromUnit, Unit::Volume const toUnit,
                       double const value) -> double {
  using namespace impl;
  return from_liters(to_liters(fromUnit, value), toUnit);
}

// returns empty optional if units are of different types (e.g. distance and
// temperature)
auto constexpr convert(Unit const& fromUnit, Unit const& toUnit,
                       double const value) -> std::optional<double> {
  if (fromUnit.type() != toUnit.type()) {
    return std::nullopt;
  }

  switch (fromUnit.type()) {
  case Unit::Type::distance:
    return convert(fromUnit.distance(), toUnit.distance(), value);
  case Unit::Type::weight:
    return convert(fromUnit.weight(), toUnit.weight(), value);
  case Unit::Type::temperature:
    return convert(fromUnit.temperature(), toUnit.temperature(), value);
  case Unit::Type::volume:
    return convert(fromUnit.volume(), toUnit.volume(), value);
  }
  // Unreachable unless not all Unit::Type enumerators are covered in the
  // switch.
  std::terminate();
}
