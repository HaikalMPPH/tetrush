#include "colors.hpp"

std::vector<Color> 
colors::get_color() {
    return {
        colors::empty, 
        colors::red,
        colors::orange, 
        colors::yellow, 
        colors::green, 
        colors::blue, 
        colors::magenta, 
        colors::purple,
        colors::grey
    }; 
}
