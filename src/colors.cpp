#include "colors.hpp"

std::vector<Color> 
color::get_color() {
    return {
        color::empty, 
        color::red,
        color::orange, 
        color::yellow, 
        color::green, 
        color::blue, 
        color::cyan, 
        color::purple,
        color::projection_grey
    }; 
}
