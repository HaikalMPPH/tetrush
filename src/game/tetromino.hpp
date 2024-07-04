#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "block.hpp"

// L
class el : public ::block {
public:
    el();
private:
};

// J
class jay : public ::block {
public:
    jay();
};

// I
class straight : public ::block {
public:
    straight();
};

// []
class square : public ::block {
public:
    square();
};

// T
class tee : public ::block {
public:
    tee();
};

// S
class skew_s : public ::block {
public:
    skew_s();
};

// Z
class skew_z : public ::block {
public:
    skew_z();
};

#endif
