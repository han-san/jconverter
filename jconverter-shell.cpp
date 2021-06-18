#include "convertfromstrings.hpp"

#include <iostream>
#include <string>
#include <string_view>

using namespace std::string_view_literals;
using std::cerr;
using std::string;
using std::string_view;

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

  auto const fromString = string_view {argv[1]};
  auto const toString = string_view {argv[2]};

  // If the value arg is omitted or "-" get the string from stdin
  auto const valueString = [argc, argv]() -> string {
    if ((argc == 3) || ("-"sv == argv[3])) {
      string tmp;
      std::cin >> tmp;
      return tmp;
    }
    return argv[3];
  }();

  auto const maybeValue = convert(fromString, toString, valueString);
  if (!maybeValue) {
    return EXIT_FAILURE;
  }
  std::cout << *maybeValue << '\n';
}
