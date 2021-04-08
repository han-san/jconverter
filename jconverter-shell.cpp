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

auto main(int argc, char** argv) -> int {
  if (argc != 3 && argc != 4) {
    cerr << "Usage: " << argv[0] << " [From] [To] [Value | -]\n\n";
    cerr << "Available units:\n";
    for (auto unit : unitStrings) {
      cerr << '\t' << unit << '\n';
    }
    return EXIT_FAILURE;
  }

  auto const fromString = string_view {argv[1]};
  auto const toString = string_view {argv[2]};

  // If the value arg is omitted or "-" get the string from stdin
  auto const valueString = [argc, argv]() -> string {
    if ((argc == 3) || ("-"sv == argv[3])) {
      auto tmp = string {};
      std::cin >> tmp;
      return tmp;
    }
    return argv[3];
  }();

  auto const stringToUnit =
      [](string_view const unitString) -> std::optional<Unit> {
    try {
      return Unit {string {unitString}};
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

  double value;
  try {
    value = stod(valueString);
  } catch (const std::invalid_argument&) {
    cerr << "[Value] is not a valid number (" << valueString << ").\n";
    return EXIT_FAILURE;
  } catch (const std::out_of_range&) {
    cerr << "[Value] is out of range for a double (" << valueString << ").\n";
    return EXIT_FAILURE;
  }

  auto const result = convert(*fromUnit, *toUnit, value);

  if (result) {
    std::cout << *result << '\n';
  } else {
    cerr << "ERR: Units are of different types.";
  }
}
