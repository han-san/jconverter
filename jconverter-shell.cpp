#include <iostream>
#include <charconv>
#include <optional>
#include <string_view>
#include <string>

#include "logic.hpp"

auto main(int argc, char** argv) -> int
{
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " [From] [To] [Value]\n";
        return 1;
    }

    auto fromString = std::string_view{argv[1]};
    auto toString = std::string_view{argv[2]};
    auto valueString = std::string{argv[3]};

    auto stringToUnit = [] (std::string_view unitString) -> std::optional<Unit> {
        try {
            return stringToUnitMap.at(unitString);
        } catch (const std::out_of_range& e) {
            return {};
        }
    };

    auto const from = stringToUnit(fromString);
    if (!from) {
        std::cerr << "[From] is not a valid unit (" << fromString << ").\n";
        return 1;
    }

    auto const to = stringToUnit(toString);
    if (!to) {
        std::cerr << "[To] is not a valid unit (" << toString << ").\n";
        return 1;
    }

    double value;
    try {
        value = stod(valueString);
    } catch (const std::invalid_argument& e) {
        std::cerr << "[Value] is not a valid number (" << valueString << ").\n";
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "[Value] is out of range for a double (" << valueString << ").\n";
        return 1;
    }

    auto result = convert(*from, *to, value);

    if (result) {
        std::cout << *result << '\n';
    } else {
        std::cerr << "ERR: Units are of different types.";
    }
}
