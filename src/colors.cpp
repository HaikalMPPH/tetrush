#include "colors.hpp"

std::vector<Color> 
color::GetColor() {
    return {
        color::kEmpty, 
        color::kRed,
        color::kOrange, 
        color::kYellow, 
        color::kGreen, 
        color::kblue, 
        color::kCyan, 
        color::kPurple,
        color::kProjectionGrey
    }; 
}
