#include "colors.hpp"

std::vector<Color> 
Colors::getColor() {
    return {
        Colors::kEmpty, 
        Colors::kRed,
        Colors::kOrange, 
        Colors::kYellow, 
        Colors::kGreen, 
        Colors::kBlue, 
        Colors::kCyan, 
        Colors::kPurple,
        Colors::kProjectionGrey
    }; 
}
