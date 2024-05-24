#include "tetromino.hpp"

El::El() 
{
    color_id = 1;
    //  . . #
    //  # # #
    //  . . .
    cells[0] = {
                                        Position(0, 2),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //              
    };

    // . # .
    // . # .
    // . # #
    cells[1] = {
                        Position(0, 1),
                        Position(1, 1),
                        Position(2, 1), Position(2, 2)
    };

    // . . .
    // # # #
    // # . .
    cells[2] = {
        //              
        Position(1, 0), Position(1, 1), Position(1, 2),
        Position(2, 0),
    };

    // # # .
    // . # .
    // . # .
    cells[3] = {
        Position(0, 0), Position(0, 1),
                        Position(1, 1),
                        Position(2, 1)
    };

    move(0, 3);
}



Jay::Jay()
{
    color_id = 2;
    //  # . .
    //  # # #
    //  . . .
    cells[0] = {
        Position(0, 0),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //              
    };

    // . # #
    // . # .
    // . # .
    cells[1] = {
                        Position(0, 1), Position(0, 2),
                        Position(1, 1),
                        Position(2, 1),
    };

    // . . .
    // # # #
    // . . #
    cells[2] = {
        //              
        Position(1, 0), Position(1, 1), Position(1, 2),
                                        Position(2, 2),
    };

    // . # .
    // . # .
    // # # .
    cells[3] = {
                        Position(0, 1),
                        Position(1, 1),
        Position(2, 0), Position(2, 1)
    };
    move(0, 3);
}



Straight::Straight() 
{
    color_id = 3;

    // . . . .
    // # # # #
    // . . . .
    // . . . .
    cells[0] = {
        //
        Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)
        //
        //
    };

    // . . # .
    // . . # .
    // . . # .
    // . . # .
    cells[1] = {
                                        Position(0, 2),
                                        Position(1, 2),
                                        Position(2, 2),
                                        Position(3, 2)
    };

    // . . . .
    // . . . .
    // # # # #
    // . . . .
    cells[2] = {
        // 
        // 
        Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)
        //
    };


    //  . # . .
    //  . # . .
    //  . # . .
    //  . # . .
    cells[3] = {
            Position(0, 1),
            Position(1, 1),
            Position(2, 1),
            Position(3, 1)
    };
    move(-1, 3);
}

Square::Square() {
    color_id = 4;

    // All rotation are the same.
    // # #
    // # #
    cells[0] = 
    cells[1] = 
    cells[2] = 
    cells[3] = {
        Position(0, 0), Position(0, 1),
        Position(1, 0), Position(1, 1)
    };
    move(0, 4);
}

Tee::Tee() {
    color_id = 5;

    // . # .
    // # # #
    // . . .
    cells[0] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //
    };

    // . # .
    // . # #
    // . # .
    cells[1] = {
                        Position(0, 1), 
                        Position(1, 1), Position(1, 2),
                        Position(2, 1),
    };

    //  # # #
    //  . # .
    //  . . .
    cells[2] = {
        Position(0, 0), Position(0, 1), Position(0, 2),
                        Position(1, 1)
        //              
    };

    // . # .
    // # # .
    // . # .
    cells[3] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1),
                        Position(2, 1)
    };
    move(0, 3);
}



SkewS::SkewS() {
    color_id = 6;

    // . # #
    // # # .
    // . . .
    cells[0] = {
                        Position(0, 1), Position(0, 2),
        Position(1, 0), Position(1, 1)
        //
    };

    // . # .
    // . # #
    // . . #
    cells[1] = {
                        Position(0, 1),
                        Position(1, 1), Position(1, 2),
                                        Position(2, 2)
    };

    // . . .
    // . # #
    // # # .
    cells[2] = {
        //
                        Position(1, 1), Position(1, 2),
        Position(2, 0), Position(2, 1)
    };

    // # . .
    // # # .
    // . # .
    cells[3] = {
        Position(0, 0),
        Position(1, 0), Position(1, 1),
                        Position(2, 1)
    };
    move(0, 3);
}


SkewZ::SkewZ() {
    color_id = 7;
    // # # .
    // . # #
    // . . .
    cells[0] = {
        Position(0, 0), Position(0, 1),
                        Position(1, 1), Position(1, 2)
        //
    };

    // . . #
    // . # #
    // . # .
    cells[1] = {
                                        Position(0, 2),
                        Position(1, 1), Position(1, 2),
                        Position(2, 1)
    };

    // . . .
    // # # .
    // . # #
    cells[2] = {
        //
        Position(1, 0), Position(1, 1),
                        Position(2, 1), Position(2, 2)
    };

    // . # .
    // # # .
    // # . .
    cells[3] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1),
        Position(2, 0)
    };
    move(0, 3);
}
