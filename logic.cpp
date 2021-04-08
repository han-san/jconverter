#include <optional>
#include <unordered_set>

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

auto constexpr static unit_type_of(Unit const u) -> UnitType {
  switch (u) {
  case Unit::celsius:
  case Unit::fahrenheit:
  case Unit::kelvin:
    return UnitType::temperature;
  case Unit::kilometer:
  case Unit::meter:
  case Unit::mile:
  case Unit::foot:
  case Unit::inch:
    return UnitType::distance;
  case Unit::lb:
  case Unit::gram:
  case Unit::kilogram:
    return UnitType::weight;
  }
}

auto constexpr convert_distance(Unit const fromUnit, Unit const toUnit,
                                double const value) -> double {
  auto const meters = [fromUnit, value]() -> Distance::Meters {
    switch (fromUnit) {
    case Unit::meter:
      return Distance::Meters {value};
    case Unit::kilometer:
      return Distance::Meters {Distance::Kilometers {value}};
    case Unit::mile:
      return Distance::Meters {Distance::Imperial::Miles {value}};
    case Unit::foot:
      return Distance::Meters {Distance::Imperial::Feet {value}};
    case Unit::inch:
      return Distance::Meters {Distance::Imperial::Inches {value}};
    }
  }();

  switch (toUnit) {
  case Unit::meter:
    return meters.count();
  case Unit::kilometer:
    return Distance::Kilometers {meters}.count();
  case Unit::mile:
    return Distance::Imperial::Miles {meters}.count();
  case Unit::foot:
    return Distance::Imperial::Feet {meters}.count();
  case Unit::inch:
    return Distance::Imperial::Inches {meters}.count();
  }
}

auto constexpr convert_weight(Unit const fromUnit, Unit const toUnit,
                              double const value) -> double {
  auto const grams = [fromUnit, value]() -> Weight::Grams {
    switch (fromUnit) {
    case Unit::gram:
      return Weight::Grams {value};
    case Unit::kilogram:
      return Weight::Kilograms {value};
    case Unit::lb:
      return Weight::Imperial::Pounds {value};
    }
  }();

  switch (toUnit) {
  case Unit::gram:
    return grams.count();
  case Unit::kilogram:
    return Weight::Kilograms {grams}.count();
  case Unit::lb:
    return Weight::Imperial::Pounds {grams}.count();
  }
}

auto constexpr convert_temperature(Unit const fromUnit, Unit const toUnit,
                                   double const value) -> double {
  auto const kelvin = [fromUnit, value]() -> double {
    switch (fromUnit) {
    case Unit::kelvin:
      return value;
    case Unit::celsius:
      return celsius_to_kelvin(value);
    case Unit::fahrenheit:
      return fahrenheit_to_kelvin(value);
    }
  }();

  switch (toUnit) {
  case Unit::kelvin:
    return kelvin;
  case Unit::celsius:
    return kelvin_to_celsius(kelvin);
  case Unit::fahrenheit:
    return kelvin_to_fahrenheit(kelvin);
  }
}

// returns empty optional if units are of different types (e.g. distance and
// temperature)
auto convert(Unit const fromUnit, Unit const toUnit, double const value)
    -> std::optional<double> {
  auto const fromUnitType = unit_type_of(fromUnit);
  auto const toUnitType = unit_type_of(toUnit);
  if (fromUnitType != toUnitType) {
    return std::nullopt;
  }

  switch (fromUnitType) {
  case UnitType::distance:
    return convert_distance(fromUnit, toUnit, value);
  case UnitType::weight:
    return convert_weight(fromUnit, toUnit, value);
  case UnitType::temperature:
    return convert_temperature(fromUnit, toUnit, value);
  }
}
