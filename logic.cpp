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
    case Unit::Distance::meter:
      return Distance::Meters {value};
    case Unit::Distance::kilometer:
      return Distance::Meters {Distance::Kilometers {value}};
    case Unit::Distance::mile:
      return Distance::Meters {Distance::Imperial::Miles {value}};
    case Unit::Distance::foot:
      return Distance::Meters {Distance::Imperial::Feet {value}};
    case Unit::Distance::inch:
      return Distance::Meters {Distance::Imperial::Inches {value}};
    }
  }();

  switch (toUnit) {
  case Unit::Distance::meter:
    return meters.count();
  case Unit::Distance::kilometer:
    return Distance::Kilometers {meters}.count();
  case Unit::Distance::mile:
    return Distance::Imperial::Miles {meters}.count();
  case Unit::Distance::foot:
    return Distance::Imperial::Feet {meters}.count();
  case Unit::Distance::inch:
    return Distance::Imperial::Inches {meters}.count();
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
