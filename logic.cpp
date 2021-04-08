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

auto constexpr convert_weight(Unit::Weight const fromUnit,
                              Unit::Weight const toUnit, double const value)
    -> double {
  using namespace Weight;
  auto const grams = [fromUnit, value]() -> Grams {
    switch (fromUnit) {
    case Unit::Weight::gram:
      return Grams {value};
    case Unit::Weight::kilogram:
      return Kilograms {value};
    case Unit::Weight::lb:
      return Imperial::Pounds {value};
    }
  }();

  switch (toUnit) {
  case Unit::Weight::gram:
    return grams.count();
  case Unit::Weight::kilogram:
    return Kilograms {grams}.count();
  case Unit::Weight::lb:
    return Imperial::Pounds {grams}.count();
  }
}

auto constexpr convert_temperature(Unit::Temperature const fromUnit,
                                   Unit::Temperature const toUnit,
                                   double const value) -> double {
  auto const kelvin = [fromUnit, value]() -> double {
    switch (fromUnit) {
    case Unit::Temperature::kelvin:
      return value;
    case Unit::Temperature::celsius:
      return celsius_to_kelvin(value);
    case Unit::Temperature::fahrenheit:
      return fahrenheit_to_kelvin(value);
    }
  }();

  switch (toUnit) {
  case Unit::Temperature::kelvin:
    return kelvin;
  case Unit::Temperature::celsius:
    return kelvin_to_celsius(kelvin);
  case Unit::Temperature::fahrenheit:
    return kelvin_to_fahrenheit(kelvin);
  }
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
  }
}
