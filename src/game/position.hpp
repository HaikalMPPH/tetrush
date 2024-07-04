#ifndef POSITION_HPP
#define POSITION_HPP


class position {
public:
    int row;
    int col;

    position(int row, int col) 
        : row {row}
        , col {col}
    {}
};

#endif // POSITION_HPP
