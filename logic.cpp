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

auto constexpr convert_distance(Unit::Distance const fromUnit,
                                Unit::Distance const toUnit, double const value)
    -> double {
  auto const meters = [fromUnit, value]() -> Distance::Meters {
    switch (fromUnit) {
    case Unit::Distance::millimeter:
      return Distance::Millimeters {value};
    case Unit::Distance::centimeter:
      return Distance::Centimeters {value};
    case Unit::Distance::decimeter:
      return Distance::Decimeters {value};
    case Unit::Distance::meter:
      return Distance::Meters {value};
    case Unit::Distance::kilometer:
      return Distance::Kilometers {value};
    case Unit::Distance::lightyear:

      return Distance::Lightyears {value};
    case Unit::Distance::thou:

      return Distance::Imperial::Thou {value};
    case Unit::Distance::barleycorn:
      return Distance::Imperial::Barleycorns {value};
    case Unit::Distance::inch:
      return Distance::Imperial::Inches {value};
    case Unit::Distance::foot:
      return Distance::Imperial::Feet {value};
    case Unit::Distance::yard:
      return Distance::Imperial::Yards {value};
    case Unit::Distance::furlong:
      return Distance::Imperial::Furlongs {value};
    case Unit::Distance::mile:
      return Distance::Imperial::Miles {value};
    case Unit::Distance::league:
      return Distance::Imperial::Leagues {value};

    case Unit::Distance::fathom:
      return Distance::Imperial::Fathoms {value};
    case Unit::Distance::cable:
      return Distance::Imperial::Cables {value};
    case Unit::Distance::nauticalMile:
      return Distance::Imperial::NauticleMiles {value};

    case Unit::Distance::link:
      return Distance::Imperial::Links {value};
    case Unit::Distance::rod:
      return Distance::Imperial::Rods {value};
    }
  }();

  switch (toUnit) {
  case Unit::Distance::millimeter:
    return Distance::Millimeters {meters}.count();
  case Unit::Distance::centimeter:
    return Distance::Centimeters {meters}.count();
  case Unit::Distance::decimeter:
    return Distance::Decimeters {meters}.count();
  case Unit::Distance::meter:
    return meters.count();
  case Unit::Distance::kilometer:
    return Distance::Kilometers {meters}.count();

  case Unit::Distance::lightyear:
    return Distance::Lightyears {meters}.count();
  case Unit::Distance::thou:

    return Distance::Imperial::Thou {meters}.count();
  case Unit::Distance::barleycorn:
    return Distance::Imperial::Barleycorns {meters}.count();
  case Unit::Distance::inch:
    return Distance::Imperial::Inches {meters}.count();
  case Unit::Distance::foot:
    return Distance::Imperial::Feet {meters}.count();
  case Unit::Distance::yard:
    return Distance::Imperial::Yards {meters}.count();
  case Unit::Distance::furlong:
    return Distance::Imperial::Furlongs {meters}.count();
  case Unit::Distance::mile:
    return Distance::Imperial::Miles {meters}.count();
  case Unit::Distance::league:
    return Distance::Imperial::Leagues {meters}.count();

  case Unit::Distance::fathom:
    return Distance::Imperial::Fathoms {meters}.count();
  case Unit::Distance::cable:
    return Distance::Imperial::Cables {meters}.count();
  case Unit::Distance::nauticalMile:
    return Distance::Imperial::NauticleMiles {meters}.count();

  case Unit::Distance::link:
    return Distance::Imperial::Links {meters}.count();
  case Unit::Distance::rod:
    return Distance::Imperial::Rods {meters}.count();
  }
}

auto constexpr convert_weight(Unit::Weight const fromUnit,
                              Unit::Weight const toUnit, double const value)
    -> double {
  auto const grams = [fromUnit, value]() -> Weight::Grams {
    switch (fromUnit) {
    case Unit::Weight::gram:
      return Weight::Grams {value};
    case Unit::Weight::kilogram:
      return Weight::Kilograms {value};
    case Unit::Weight::lb:
      return Weight::Imperial::Pounds {value};
    }
  }();

  switch (toUnit) {
  case Unit::Weight::gram:
    return grams.count();
  case Unit::Weight::kilogram:
    return Weight::Kilograms {grams}.count();
  case Unit::Weight::lb:
    return Weight::Imperial::Pounds {grams}.count();
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
