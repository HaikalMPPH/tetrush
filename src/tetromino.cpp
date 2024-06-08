#include "tetromino.hpp"
#include "position.hpp"


El::El() 
{
    _colorId = 1;
    //  . . #
    //  # # #
    //  . . .
    _cells[0] = {
                                        Position(0, 2),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //              
    };

    // . # .
    // . # .
    // . # #
    _cells[1] = {
                        Position(0, 1),
                        Position(1, 1),
                        Position(2, 1), Position(2, 2)
    };

    // . . .
    // # # #
    // # . .
    _cells[2] = {
        //              
        Position(1, 0), Position(1, 1), Position(1, 2),
        Position(2, 0),
    };

    // # # .
    // . # .
    // . # .
    _cells[3] = {
        Position(0, 0), Position(0, 1),
                        Position(1, 1),
                        Position(2, 1)
    };

    Move(0, 3);
}



Jay::Jay()
{
    _colorId = 2;
    //  # . .
    //  # # #
    //  . . .
    _cells[0] = {
        Position(0, 0),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //              
    };

    // . # #
    // . # .
    // . # .
    _cells[1] = {
                        Position(0, 1), Position(0, 2),
                        Position(1, 1),
                        Position(2, 1),
    };

    // . . .
    // # # #
    // . . #
    _cells[2] = {
        //              
        Position(1, 0), Position(1, 1), Position(1, 2),
                                        Position(2, 2),
    };

    // . # .
    // . # .
    // # # .
    _cells[3] = {
                        Position(0, 1),
                        Position(1, 1),
        Position(2, 0), Position(2, 1)
    };
    Move(0, 3);
}



Straight::Straight() 
{
    _colorId = 3;

    // . . . .
    // # # # #
    // . . . .
    // . . . .
    _cells[0] = {
        //
        Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)
        //
        //
    };

    // . . # .
    // . . # .
    // . . # .
    // . . # .
    _cells[1] = {
                                        Position(0, 2),
                                        Position(1, 2),
                                        Position(2, 2),
                                        Position(3, 2)
    };

    // . . . .
    // . . . .
    // # # # #
    // . . . .
    _cells[2] = {
        // 
        // 
        Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)
        //
    };


    //  . # . .
    //  . # . .
    //  . # . .
    //  . # . .
    _cells[3] = {
            Position(0, 1),
            Position(1, 1),
            Position(2, 1),
            Position(3, 1)
    };
    Move(-1, 3);
}

Square::Square() {
    _colorId = 4;

    // All rotation are the same.
    // # #
    // # #
    _cells[0] = 
    _cells[1] = 
    _cells[2] = 
    _cells[3] = {
        Position(0, 0), Position(0, 1),
        Position(1, 0), Position(1, 1)
    };
    Move(0, 4);
}

Tee::Tee() {
    _colorId = 5;

    // . # .
    // # # #
    // . . .
    _cells[0] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //
    };

    // . # .
    // . # #
    // . # .
    _cells[1] = {
                        Position(0, 1), 
                        Position(1, 1), Position(1, 2),
                        Position(2, 1),
    };

    //  # # #
    //  . # .
    //  . . .
    _cells[2] = {
        Position(0, 0), Position(0, 1), Position(0, 2),
                        Position(1, 1)
        //              
    };

    // . # .
    // # # .
    // . # .
    _cells[3] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1),
                        Position(2, 1)
    };
    Move(0, 3);
}



SkewS::SkewS() {
    _colorId = 6;

    // . # #
    // # # .
    // . . .
    _cells[0] = {
                        Position(0, 1), Position(0, 2),
        Position(1, 0), Position(1, 1)
        //
    };

    // . # .
    // . # #
    // . . #
    _cells[1] = {
                        Position(0, 1),
                        Position(1, 1), Position(1, 2),
                                        Position(2, 2)
    };

    // . . .
    // . # #
    // # # .
    _cells[2] = {
        //
                        Position(1, 1), Position(1, 2),
        Position(2, 0), Position(2, 1)
    };

    // # . .
    // # # .
    // . # .
    _cells[3] = {
        Position(0, 0),
        Position(1, 0), Position(1, 1),
                        Position(2, 1)
    };
    Move(0, 3);
}


SkewZ::SkewZ() {
    _colorId = 7;
    // # # .
    // . # #
    // . . .
    _cells[0] = {
        Position(0, 0), Position(0, 1),
                        Position(1, 1), Position(1, 2)
        //
    };

    // . . #
    // . # #
    // . # .
    _cells[1] = {
                                        Position(0, 2),
                        Position(1, 1), Position(1, 2),
                        Position(2, 1)
    };

    // . . .
    // # # .
    // . # #
    _cells[2] = {
        //
        Position(1, 0), Position(1, 1),
                        Position(2, 1), Position(2, 2)
    };

    // . # .
    // # # .
    // # . .
    _cells[3] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1),
        Position(2, 0)
    };
    Move(0, 3);
}
