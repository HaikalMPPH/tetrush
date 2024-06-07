#include "colors.hpp"

std::vector<Color> 
color::GetColor() {
    return {
        color::kEmpty, 
        color::kRed,
        color::kOrange, 
        color::kYellow, 
        color::kGreen, 
        color::kBlue, 
        color::kCyan, 
        color::kPurple,
        color::kProjectionGrey
    }; 
}
