#include <cctype>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

#include "logic.hpp"

auto main(int argc, char** argv) -> int
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " [From] [To] [Value]\n\n";
        std::cerr << "Available units:\n";
        for (auto unit : unitStrings) {
            std::cerr << '\t' << unit << '\n';
        }
        return EXIT_FAILURE;
    }

    auto const fromString = std::string_view{argv[1]};
    auto const toString = std::string_view{argv[2]};
    auto const valueString = std::string{argv[3]};

    auto const stringToUnit = [] (std::string unitString) -> std::optional<Unit> {
        for (auto& c : unitString) {
            c = std::tolower(c);
        }
        try {
            return stringToUnitMap.at(unitString);
        } catch (const std::out_of_range& e) {
            return {};
        }
    };

    auto const fromUnit = stringToUnit(std::string{fromString});
    if (!fromUnit) {
        std::cerr << "[From] is not a valid unit (" << fromString << ").\n";
        return EXIT_FAILURE;
    }

    auto const toUnit = stringToUnit(std::string{toString});
    if (!toUnit) {
        std::cerr << "[To] is not a valid unit (" << toString << ").\n";
        return EXIT_FAILURE;
    }

    double value;
    try {
        value = stod(valueString);
    } catch (const std::invalid_argument& e) {
        std::cerr << "[Value] is not a valid number (" << valueString << ").\n";
        return EXIT_FAILURE;
    } catch (const std::out_of_range& e) {
        std::cerr << "[Value] is out of range for a double (" << valueString << ").\n";
        return EXIT_FAILURE;
    }

    auto const result = convert(*fromUnit, *toUnit, value);

    if (result) {
        std::cout << *result << '\n';
    } else {
        std::cerr << "ERR: Units are of different types.";
    }
}
