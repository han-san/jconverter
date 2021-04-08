#include <cctype>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

#include "logic.hpp"

using namespace std::string_view_literals;
using std::cerr;
using std::string;
using std::string_view;

class VariantMap {
public:
  [[nodiscard]] auto at(std::string_view const str) const -> Unit::Variant {
    return m_map.at(str);
  }

private:
  std::unordered_map<std::string_view, Unit::Variant> const m_map {
      {"celsius", Unit::Temperature::celsius},
      {"c", Unit::Temperature::celsius},
      {"fahrenheit", Unit::Temperature::fahrenheit},
      {"f", Unit::Temperature::fahrenheit},
      {"kelvin", Unit::Temperature::kelvin},
      {"k", Unit::Temperature::kelvin},

      {"millimeter", Unit::Distance::millimeter},
      {"millimeters", Unit::Distance::millimeter},
      {"mm", Unit::Distance::millimeter},
      {"centimeter", Unit::Distance::centimeter},
      {"centimeters", Unit::Distance::centimeter},
      {"cm", Unit::Distance::centimeter},
      {"decimeter", Unit::Distance::decimeter},
      {"decimeters", Unit::Distance::decimeter},
      {"dm", Unit::Distance::decimeter},
      {"meter", Unit::Distance::meter},
      {"meters", Unit::Distance::meter},
      {"m", Unit::Distance::meter},
      {"km", Unit::Distance::kilometer},
      {"kilometer", Unit::Distance::kilometer},
      {"kilometers", Unit::Distance::kilometer},
      {"lightyear", Unit::Distance::lightyear},
      {"lightyears", Unit::Distance::lightyear},
      {"light-year", Unit::Distance::lightyear},
      {"light-years", Unit::Distance::lightyear},
      {"ly", Unit::Distance::lightyear},
      {"thou", Unit::Distance::thou},
      {"thou", Unit::Distance::thou},
      {"barleycorn", Unit::Distance::barleycorn},
      {"barleycorns", Unit::Distance::barleycorn},
      {"inch", Unit::Distance::inch},
      {"inches", Unit::Distance::inch},
      {"foot", Unit::Distance::foot},
      {"feet", Unit::Distance::foot},
      {"yard", Unit::Distance::yard},
      {"yards", Unit::Distance::yard},
      {"y", Unit::Distance::yard},
      {"furlong", Unit::Distance::furlong},
      {"furlongs", Unit::Distance::furlong},
      {"mile", Unit::Distance::mile},
      {"miles", Unit::Distance::mile},
      {"league", Unit::Distance::league},
      {"leagues", Unit::Distance::league},
      {"fathom", Unit::Distance::fathom},
      {"fathoms", Unit::Distance::fathom},
      {"cable", Unit::Distance::cable},
      {"cables", Unit::Distance::cable},
      {"nauticalmile", Unit::Distance::nauticalMile},
      {"nauticalmiles", Unit::Distance::nauticalMile},
      {"nautical", Unit::Distance::nauticalMile},
      {"nauticals", Unit::Distance::nauticalMile},
      {"link", Unit::Distance::link},
      {"links", Unit::Distance::link},
      {"rod", Unit::Distance::rod},
      {"rods", Unit::Distance::rod},

      {"pound", Unit::Weight::lb},
      {"pounds", Unit::Weight::lb},
      {"lbs", Unit::Weight::lb},
      {"lb", Unit::Weight::lb},
      {"gram", Unit::Weight::gram},
      {"g", Unit::Weight::gram},
      {"grams", Unit::Weight::gram},
      {"kg", Unit::Weight::kilogram},
      {"kilogram", Unit::Weight::kilogram},
      {"kilograms", Unit::Weight::kilogram},
  };
};

auto main(int argc, char** argv) -> int {
  if (argc != 3 && argc != 4) {
    cerr << "Usage: " << argv[0] << " [From] [To] [Value | -]\n\n";
    cerr << "Available units:\n";
    for (auto unit : unitStrings) {
      cerr << '\t' << unit << '\n';
    }
    return EXIT_FAILURE;
  }

  string_view const fromString {argv[1]};
  string_view const toString {argv[2]};

  // If the value arg is omitted or "-" get the string from stdin
  auto const valueString = [argc, argv]() -> string {
    if ((argc == 3) || ("-"sv == argv[3])) {
      string tmp;
      std::cin >> tmp;
      return tmp;
    }
    return argv[3];
  }();

  VariantMap vmap;

  auto const stringToUnit =
      [&vmap](string_view const unitString) -> std::optional<Unit> {
    try {
      return Unit {vmap.at(unitString)};
    } catch (const std::out_of_range&) {
      return {};
    }
  };

  auto const fromUnit = stringToUnit(fromString);
  if (!fromUnit) {
    cerr << "[From] is not a valid unit (" << fromString << ").\n";
    return EXIT_FAILURE;
  }

  auto const toUnit = stringToUnit(toString);
  if (!toUnit) {
    cerr << "[To] is not a valid unit (" << toString << ").\n";
    return EXIT_FAILURE;
  }

  auto const value = [&valueString]() -> std::optional<double> {
    try {
      return stod(valueString);
    } catch (const std::invalid_argument&) {
      cerr << "[Value] is not a valid number (" << valueString << ").\n";
      return std::nullopt;
    } catch (const std::out_of_range&) {
      cerr << "[Value] is out of range for a double (" << valueString << ").\n";
      return std::nullopt;
    }
  }();

  if (!value) {
    return EXIT_FAILURE;
  }
  auto const result = convert(*fromUnit, *toUnit, *value);

  if (result) {
    std::cout << *result << '\n';
  } else {
    cerr << "ERR: Units are of different types.";
  }
}
