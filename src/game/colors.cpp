#include "colors.hpp"

std::vector<Color> 
colors::get_color() {
    return {
        colors::kEmpty, 
        colors::kRed,
        colors::kOrange, 
        colors::kYellow, 
        colors::kGreen, 
        colors::kBlue, 
        colors::kCyan, 
        colors::kPurple,
        colors::kProjectionGrey
    }; 
}
