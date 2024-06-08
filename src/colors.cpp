#include "colors.hpp"

std::vector<Color> 
Colors::GetColor() {
    return {
        Colors::Empty, 
        Colors::Red,
        Colors::Orange, 
        Colors::Yellow, 
        Colors::Green, 
        Colors::Blue, 
        Colors::Cran, 
        Colors::Purple,
        Colors::ProjectionGrey
    }; 
}
