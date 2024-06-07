#include "tetromino.hpp"
#include "position.hpp"


El::El() 
{
    color_id_ = 1;
    //  . . #
    //  # # #
    //  . . .
    cells_[0] = {
                                        Position(0, 2),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //              
    };

    // . # .
    // . # .
    // . # #
    cells_[1] = {
                        Position(0, 1),
                        Position(1, 1),
                        Position(2, 1), Position(2, 2)
    };

    // . . .
    // # # #
    // # . .
    cells_[2] = {
        //              
        Position(1, 0), Position(1, 1), Position(1, 2),
        Position(2, 0),
    };

    // # # .
    // . # .
    // . # .
    cells_[3] = {
        Position(0, 0), Position(0, 1),
                        Position(1, 1),
                        Position(2, 1)
    };

    Move(0, 3);
}



Jay::Jay()
{
    color_id_ = 2;
    //  # . .
    //  # # #
    //  . . .
    cells_[0] = {
        Position(0, 0),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //              
    };

    // . # #
    // . # .
    // . # .
    cells_[1] = {
                        Position(0, 1), Position(0, 2),
                        Position(1, 1),
                        Position(2, 1),
    };

    // . . .
    // # # #
    // . . #
    cells_[2] = {
        //              
        Position(1, 0), Position(1, 1), Position(1, 2),
                                        Position(2, 2),
    };

    // . # .
    // . # .
    // # # .
    cells_[3] = {
                        Position(0, 1),
                        Position(1, 1),
        Position(2, 0), Position(2, 1)
    };
    Move(0, 3);
}



Straight::Straight() 
{
    color_id_ = 3;

    // . . . .
    // # # # #
    // . . . .
    // . . . .
    cells_[0] = {
        //
        Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)
        //
        //
    };

    // . . # .
    // . . # .
    // . . # .
    // . . # .
    cells_[1] = {
                                        Position(0, 2),
                                        Position(1, 2),
                                        Position(2, 2),
                                        Position(3, 2)
    };

    // . . . .
    // . . . .
    // # # # #
    // . . . .
    cells_[2] = {
        // 
        // 
        Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)
        //
    };


    //  . # . .
    //  . # . .
    //  . # . .
    //  . # . .
    cells_[3] = {
            Position(0, 1),
            Position(1, 1),
            Position(2, 1),
            Position(3, 1)
    };
    Move(-1, 3);
}

Square::Square() {
    color_id_ = 4;

    // All rotation are the same.
    // # #
    // # #
    cells_[0] = 
    cells_[1] = 
    cells_[2] = 
    cells_[3] = {
        Position(0, 0), Position(0, 1),
        Position(1, 0), Position(1, 1)
    };
    Move(0, 4);
}

Tee::Tee() {
    color_id_ = 5;

    // . # .
    // # # #
    // . . .
    cells_[0] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1), Position(1, 2),
        //
    };

    // . # .
    // . # #
    // . # .
    cells_[1] = {
                        Position(0, 1), 
                        Position(1, 1), Position(1, 2),
                        Position(2, 1),
    };

    //  # # #
    //  . # .
    //  . . .
    cells_[2] = {
        Position(0, 0), Position(0, 1), Position(0, 2),
                        Position(1, 1)
        //              
    };

    // . # .
    // # # .
    // . # .
    cells_[3] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1),
                        Position(2, 1)
    };
    Move(0, 3);
}



SkewS::SkewS() {
    color_id_ = 6;

    // . # #
    // # # .
    // . . .
    cells_[0] = {
                        Position(0, 1), Position(0, 2),
        Position(1, 0), Position(1, 1)
        //
    };

    // . # .
    // . # #
    // . . #
    cells_[1] = {
                        Position(0, 1),
                        Position(1, 1), Position(1, 2),
                                        Position(2, 2)
    };

    // . . .
    // . # #
    // # # .
    cells_[2] = {
        //
                        Position(1, 1), Position(1, 2),
        Position(2, 0), Position(2, 1)
    };

    // # . .
    // # # .
    // . # .
    cells_[3] = {
        Position(0, 0),
        Position(1, 0), Position(1, 1),
                        Position(2, 1)
    };
    Move(0, 3);
}


SkewZ::SkewZ() {
    color_id_ = 7;
    // # # .
    // . # #
    // . . .
    cells_[0] = {
        Position(0, 0), Position(0, 1),
                        Position(1, 1), Position(1, 2)
        //
    };

    // . . #
    // . # #
    // . # .
    cells_[1] = {
                                        Position(0, 2),
                        Position(1, 1), Position(1, 2),
                        Position(2, 1)
    };

    // . . .
    // # # .
    // . # #
    cells_[2] = {
        //
        Position(1, 0), Position(1, 1),
                        Position(2, 1), Position(2, 2)
    };

    // . # .
    // # # .
    // # . .
    cells_[3] = {
                        Position(0, 1),
        Position(1, 0), Position(1, 1),
        Position(2, 0)
    };
    Move(0, 3);
}
