#include "colors.hpp"

std::vector<Color> 
color::get_color() {
    return {
        color::Empty, 
        color::Red,
        color::Orange, 
        color::Yellow, 
        color::Green, 
        color::Blue, 
        color::Cyan, 
        color::Purple
    }; 
}
