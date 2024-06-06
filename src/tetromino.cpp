#include "tetromino.hpp"
#include "position.hpp"


El::El() 
{
    colorId = 1;
    //  . . #
    //  # # #
    //  . . .
    mCells[0] = {
                                        Position(0, 2),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //              
    };

    // . # .
    // . # .
    // . # #
    mCells[1] = {
                        Position(0, 1),
                        Position(1, 1),
                        Position(2, 1), Position(2, 2)
    };

    // . . .
    // # # #
    // # . .
    mCells[2] = {
        //              
        Position(1, 0), Position(1, 1), Position(1, 2),
        Position(2, 0),
    };

    // # # .
    // . # .
    // . # .
    mCells[3] = {
        Position(0, 0), Position(0, 1),
                        Position(1, 1),
                        Position(2, 1)
    };

    move(0, 3);
}



Jay::Jay()
{
    colorId = 2;
    //  # . .
    //  # # #
    //  . . .
    mCells[0] = {
        Position(0, 0),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //              
    };

    // . # #
    // . # .
    // . # .
    mCells[1] = {
                        Position(0, 1), Position(0, 2),
                        Position(1, 1),
                        Position(2, 1),
    };

    // . . .
    // # # #
    // . . #
    mCells[2] = {
        //              
        Position(1, 0), Position(1, 1), Position(1, 2),
                                        Position(2, 2),
    };

    // . # .
    // . # .
    // # # .
    mCells[3] = {
                        Position(0, 1),
                        Position(1, 1),
        Position(2, 0), Position(2, 1)
    };
    move(0, 3);
}



Straight::Straight() 
{
    colorId = 3;

    // . . . .
    // # # # #
    // . . . .
    // . . . .
    mCells[0] = {
        //
        Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)
        //
        //
    };

    // . . # .
    // . . # .
    // . . # .
    // . . # .
    mCells[1] = {
                                        Position(0, 2),
                                        Position(1, 2),
                                        Position(2, 2),
                                        Position(3, 2)
    };

    // . . . .
    // . . . .
    // # # # #
    // . . . .
    mCells[2] = {
        // 
        // 
        Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)
        //
    };


    //  . # . .
    //  . # . .
    //  . # . .
    //  . # . .
    mCells[3] = {
            Position(0, 1),
            Position(1, 1),
            Position(2, 1),
            Position(3, 1)
    };
    move(-1, 3);
}

Square::Square() {
    colorId = 4;

    // All rotation are the same.
    // # #
    // # #
    mCells[0] = 
    mCells[1] = 
    mCells[2] = 
    mCells[3] = {
        Position(0, 0), Position(0, 1),
        Position(1, 0), Position(1, 1)
    };
    move(0, 4);
}

Tee::Tee() {
    colorId = 5;

    // . # .
    // # # #
    // . . .
    mCells[0] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //
    };

    // . # .
    // . # #
    // . # .
    mCells[1] = {
                        Position(0, 1), 
                        Position(1, 1), Position(1, 2),
                        Position(2, 1),
    };

    //  # # #
    //  . # .
    //  . . .
    mCells[2] = {
        Position(0, 0), Position(0, 1), Position(0, 2),
                        Position(1, 1)
        //              
    };

    // . # .
    // # # .
    // . # .
    mCells[3] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1),
                        Position(2, 1)
    };
    move(0, 3);
}



SkewS::SkewS() {
    colorId = 6;

    // . # #
    // # # .
    // . . .
    mCells[0] = {
                        Position(0, 1), Position(0, 2),
        Position(1, 0), Position(1, 1)
        //
    };

    // . # .
    // . # #
    // . . #
    mCells[1] = {
                        Position(0, 1),
                        Position(1, 1), Position(1, 2),
                                        Position(2, 2)
    };

    // . . .
    // . # #
    // # # .
    mCells[2] = {
        //
                        Position(1, 1), Position(1, 2),
        Position(2, 0), Position(2, 1)
    };

    // # . .
    // # # .
    // . # .
    mCells[3] = {
        Position(0, 0),
        Position(1, 0), Position(1, 1),
                        Position(2, 1)
    };
    move(0, 3);
}


SkewZ::SkewZ() {
    colorId = 7;
    // # # .
    // . # #
    // . . .
    mCells[0] = {
        Position(0, 0), Position(0, 1),
                        Position(1, 1), Position(1, 2)
        //
    };

    // . . #
    // . # #
    // . # .
    mCells[1] = {
                                        Position(0, 2),
                        Position(1, 1), Position(1, 2),
                        Position(2, 1)
    };

    // . . .
    // # # .
    // . # #
    mCells[2] = {
        //
        Position(1, 0), Position(1, 1),
                        Position(2, 1), Position(2, 2)
    };

    // . # .
    // # # .
    // # . .
    mCells[3] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1),
        Position(2, 0)
    };
    move(0, 3);
}
