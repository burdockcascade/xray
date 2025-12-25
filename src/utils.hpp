#pragma once

#include <ranges>
#include <raylib.h>

/** Parse a color from a string representation.
 *
 * Supports:
 * - Hex format: "#RRGGBB" or "#AARRGGBB"
 * - Named colors: "RED", "GREEN", "BLUE", "BLACK", "WHITE", "YELLOW", "ORANGE", "PURPLE", "GRAY"
 *
 * @param colorStr The string representation of the color.
 * @return The parsed Color object. Defaults to BLACK if parsing fails.
 */
inline Color ParseColor(const std::string& colorStr) {

    if (colorStr.front() == '#') {
        const unsigned int hexColor = std::stoul(colorStr.substr(1), nullptr, 16);
        return ::GetColor(hexColor);
    }

    // convert to uppercase for case-insensitive comparison
    std::string uppercased = colorStr
        | std::views::transform([](unsigned char c) { return std::toupper(c); })
        | std::ranges::to<std::string>();

    if (uppercased == "RED") return ::RED;
    if (uppercased == "GREEN") return ::GREEN;
    if (uppercased == "BLUE") return ::BLUE;
    if (uppercased == "BLACK") return ::BLACK;
    if (uppercased == "WHITE") return ::WHITE;
    if (uppercased == "YELLOW") return ::YELLOW;
    if (uppercased == "ORANGE") return ::ORANGE;
    if (uppercased == "PURPLE") return ::PURPLE;
    if (uppercased == "GRAY") return ::GRAY;

    // Default
    return BLACK;
}
