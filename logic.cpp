#include <optional>

#include "logic.hpp"

// Temperatures
auto static kelvin_to_fahrenheit(double kelvin) -> double {
  return kelvin * 9. / 5. - 459.67;
}

auto static fahrenheit_to_kelvin(double fahrenheit) -> double {
  return (fahrenheit + 459.67) * 5.0 / 9.0;
}

auto static celsius_to_kelvin(double celsius) -> double {
  return celsius + 273.15;
}

auto static kelvin_to_celsius(double kelvin) -> double {
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
}

auto constexpr convert_distance(Unit::Distance const fromUnit,
                                Unit::Distance const toUnit, double const value)
    -> double {
  return from_meters(to_meters(fromUnit, value), toUnit);
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
}

auto constexpr convert_weight(Unit::Weight const fromUnit,
                              Unit::Weight const toUnit, double const value)
    -> double {

  return from_grams(to_grams(fromUnit, value), toUnit);
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
}

auto constexpr convert_temperature(Unit::Temperature const fromUnit,
                                   Unit::Temperature const toUnit,
                                   double const value) -> double {
  return from_kelvin(to_kelvin(fromUnit, value), toUnit);
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
}

auto constexpr convert_volume(Unit::Volume const fromUnit,
                              Unit::Volume const toUnit, double const value)
    -> double {
  return from_liters(to_liters(fromUnit, value), toUnit);
}

// returns empty optional if units are of different types (e.g. distance and
// temperature)
auto convert(Unit const& fromUnit, Unit const& toUnit, double const value)
    -> std::optional<double> {
  if (fromUnit.type() != toUnit.type()) {
    return std::nullopt;
  }

  switch (fromUnit.type()) {
  case Unit::Type::distance:
    return convert_distance(fromUnit.distance(), toUnit.distance(), value);
  case Unit::Type::weight:
    return convert_weight(fromUnit.weight(), toUnit.weight(), value);
  case Unit::Type::temperature:
    return convert_temperature(fromUnit.temperature(), toUnit.temperature(),
                               value);
  case Unit::Type::volume:
    return convert_volume(fromUnit.volume(), toUnit.volume(), value);
  }
}
