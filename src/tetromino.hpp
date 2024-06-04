#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "block.hpp"

// L
class el_c : public block_c {
public:
    el_c();
private:
};

// J
class jay_c : public block_c {
public:
    jay_c();
};

// I
class straight_c : public block_c {
public:
    straight_c();
};

// O
class square_c : public block_c {
public:
    square_c();
};

// T
class tee_c : public block_c {
public:
    tee_c();
};

// S
class skews_c : public block_c {
public:
    skews_c();
};

// Z
class skewz_c : public block_c {
public:
    skewz_c();
};

#endif
