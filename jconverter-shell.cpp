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

      {"milligram", Unit::Weight::milligram},
      {"milligrams", Unit::Weight::milligram},
      {"mg", Unit::Weight::milligram},
      {"gram", Unit::Weight::gram},
      {"grams", Unit::Weight::gram},
      {"g", Unit::Weight::gram},
      {"hectogram", Unit::Weight::hectogram},
      {"hectograms", Unit::Weight::hectogram},
      {"hg", Unit::Weight::hectogram},
      {"kilogram", Unit::Weight::kilogram},
      {"kilograms", Unit::Weight::kilogram},
      {"kg", Unit::Weight::kilogram},
      {"tonne", Unit::Weight::tonne},
      {"tonnes", Unit::Weight::tonne},
      {"grain", Unit::Weight::grain},
      {"grains", Unit::Weight::grain},
      {"drachm", Unit::Weight::drachm},
      {"drachms", Unit::Weight::drachm},
      {"ounce", Unit::Weight::ounce},
      {"ounces", Unit::Weight::ounce},
      {"pound", Unit::Weight::lb},
      {"pounds", Unit::Weight::lb},
      {"lbs", Unit::Weight::lb},
      {"lb", Unit::Weight::lb},
      {"stone", Unit::Weight::stone},
      {"stones", Unit::Weight::stone},
      {"quarter", Unit::Weight::quarter},
      {"quarters", Unit::Weight::quarter},
      {"hundredweight", Unit::Weight::hundredweight},
      {"hundredweights", Unit::Weight::hundredweight},
      {"ton", Unit::Weight::ton},
      {"tons", Unit::Weight::ton},
      {"slug", Unit::Weight::slug},
      {"slugs", Unit::Weight::slug},

      {"milliliter", Unit::Volume::milliliter},
      {"milliliters", Unit::Volume::milliliter},
      {"ml", Unit::Volume::milliliter},
      {"centiliter", Unit::Volume::centiliter},
      {"centiliters", Unit::Volume::centiliter},
      {"cl", Unit::Volume::centiliter},
      {"liter", Unit::Volume::liter},
      {"liters", Unit::Volume::liter},
      {"l", Unit::Volume::liter},
      {"fluidounce", Unit::Volume::fluidOunce},
      {"fluidounces", Unit::Volume::fluidOunce},
      {"fluid-ounce", Unit::Volume::fluidOunce},
      {"fluid-ounces", Unit::Volume::fluidOunce},
      {"fluid ounce", Unit::Volume::fluidOunce},
      {"fluid ounces", Unit::Volume::fluidOunce},
      {"gill", Unit::Volume::gill},
      {"gills", Unit::Volume::gill},
      {"pint", Unit::Volume::pint},
      {"pints", Unit::Volume::pint},
      {"quart", Unit::Volume::quart},
      {"quarts", Unit::Volume::quart},
      {"gallon", Unit::Volume::gallon},
      {"gallons", Unit::Volume::gallon},
  };
};

auto static print_usage(string_view const programName) -> void {
  cerr << "Usage: " << programName << " [From] [To] [Value | -]\n\n";
  cerr << "Available units:\n";
  cerr << "\t[Temperature]:\n";
  for (auto const unit : temperatureStrings) {
    cerr << '\t' << unit << '\n';
  }
  cerr << "\n\t[Distance]:\n";
  for (auto const unit : distanceStrings) {
    cerr << '\t' << unit << '\n';
  }
  cerr << "\n\t[Weight]:\n";
  for (auto const unit : weightStrings) {
    cerr << '\t' << unit << '\n';
  }
  cerr << "\n\t[Volume]:\n";
  for (auto const unit : volumeStrings) {
    cerr << '\t' << unit << '\n';
  }
}

auto main(int argc, char** argv) -> int {
  if (argc != 3 && argc != 4) {
    print_usage(argv[0]);
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
