#include "convertfromstrings.hpp"

#include "logic.hpp"

#include <algorithm>
#include <cctype>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <iostream>

using std::cerr;
using std::string;
using std::string_view;

auto convert(string_view const fromString, string_view const toString,
             string const& valueString) -> std::optional<double> {
  VariantMap const vmap;

  auto const stringToUnit = [&vmap](string unitString) -> std::optional<Unit> {
    try {
      std::transform(unitString.begin(), unitString.end(), unitString.begin(),
                     [](char unsigned c) { return std::tolower(c); });
      return Unit {vmap.at(unitString)};
    } catch (const std::out_of_range&) {
      return std::nullopt;
    }
  };

  auto const fromUnit = stringToUnit(string {fromString});
  if (!fromUnit) {
    cerr << "[From] is not a valid unit (" << fromString << ").\n";
    return std::nullopt;
  }

  auto const toUnit = stringToUnit(string {toString});
  if (!toUnit) {
    cerr << "[To] is not a valid unit (" << toString << ").\n";
    return std::nullopt;
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
    return std::nullopt;
  }

  auto const result = convert(*fromUnit, *toUnit, *value);
  if (!result) {
    cerr << "ERR: Units are of different types.";
  }
  return result;
}
