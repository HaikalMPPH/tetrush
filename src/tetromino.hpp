#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "block.hpp"

// L
class El : public Block {
public:
    El();
private:
};

// J
class Jay : public Block {
public:
    Jay();
};

// I
class Straight : public Block {
public:
    Straight();
};

// O
class Square : public Block {
public:
    Square();
};

// T
class Tee : public Block {
public:
    Tee();
};

// S
class SkewS : public Block {
public:
    SkewS();
};

// Z
class SkewZ : public Block {
public:
    SkewZ();
};

#endif
