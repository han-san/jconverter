#include <iostream>
#include <charconv>
#include <optional>
#include <string_view>

#include "logic.hpp"

auto main(int argc, char** argv) -> int
{
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " [From] [To] [Value]\n";
        return 1;
    }

    auto fromString = std::string_view{argv[1]};
    auto toString = std::string_view{argv[2]};
    auto valueString = std::string_view{argv[3]};

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

    auto const value = std::strtod(valueString.data(), nullptr);
    if (!value) {
        std::cerr << "[value] is not a valid number (" << valueString << ").\n";
        return 1;
    }

    auto result = convert(*from, *to, value);

    if (result) {
        std::cout << *result << '\n';
    } else {
        std::cerr << "ERR: Units are of different types.";
    }
}
