#include "tetromino.hpp"
#include "position.hpp"

el_c::el_c() 
{
    color_id = 1;
    //  . . #
    //  # # #
    //  . . .
    cells[0] = {
                                        position_s(0, 2),
        position_s(1, 0), position_s(1, 1), position_s(1, 2),
        //              
    };

    // . # .
    // . # .
    // . # #
    cells[1] = {
                        position_s(0, 1),
                        position_s(1, 1),
                        position_s(2, 1), position_s(2, 2)
    };

    // . . .
    // # # #
    // # . .
    cells[2] = {
        //              
        position_s(1, 0), position_s(1, 1), position_s(1, 2),
        position_s(2, 0),
    };

    // # # .
    // . # .
    // . # .
    cells[3] = {
        position_s(0, 0), position_s(0, 1),
                        position_s(1, 1),
                        position_s(2, 1)
    };

    move(0, 3);
}



jay_c::jay_c()
{
    color_id = 2;
    //  # . .
    //  # # #
    //  . . .
    cells[0] = {
        position_s(0, 0),
        position_s(1, 0), position_s(1, 1), position_s(1, 2),
        //              
    };

    // . # #
    // . # .
    // . # .
    cells[1] = {
                        position_s(0, 1), position_s(0, 2),
                        position_s(1, 1),
                        position_s(2, 1),
    };

    // . . .
    // # # #
    // . . #
    cells[2] = {
        //              
        position_s(1, 0), position_s(1, 1), position_s(1, 2),
                                        position_s(2, 2),
    };

    // . # .
    // . # .
    // # # .
    cells[3] = {
                        position_s(0, 1),
                        position_s(1, 1),
        position_s(2, 0), position_s(2, 1)
    };
    move(0, 3);
}



straight_c::straight_c() 
{
    color_id = 3;

    // . . . .
    // # # # #
    // . . . .
    // . . . .
    cells[0] = {
        //
        position_s(1, 0), position_s(1, 1), position_s(1, 2), position_s(1, 3)
        //
        //
    };

    // . . # .
    // . . # .
    // . . # .
    // . . # .
    cells[1] = {
                                        position_s(0, 2),
                                        position_s(1, 2),
                                        position_s(2, 2),
                                        position_s(3, 2)
    };

    // . . . .
    // . . . .
    // # # # #
    // . . . .
    cells[2] = {
        // 
        // 
        position_s(2, 0), position_s(2, 1), position_s(2, 2), position_s(2, 3)
        //
    };


    //  . # . .
    //  . # . .
    //  . # . .
    //  . # . .
    cells[3] = {
            position_s(0, 1),
            position_s(1, 1),
            position_s(2, 1),
            position_s(3, 1)
    };
    move(-1, 3);
}

square_c::square_c() {
    color_id = 4;

    // All rotation are the same.
    // # #
    // # #
    cells[0] = 
    cells[1] = 
    cells[2] = 
    cells[3] = {
        position_s(0, 0), position_s(0, 1),
        position_s(1, 0), position_s(1, 1)
    };
    move(0, 4);
}

tee_c::tee_c() {
    color_id = 5;

    // . # .
    // # # #
    // . . .
    cells[0] = {
                        position_s(0, 1),
        position_s(1, 0), position_s(1, 1), position_s(1, 2),
        //
    };

    // . # .
    // . # #
    // . # .
    cells[1] = {
                        position_s(0, 1), 
                        position_s(1, 1), position_s(1, 2),
                        position_s(2, 1),
    };

    //  # # #
    //  . # .
    //  . . .
    cells[2] = {
        position_s(0, 0), position_s(0, 1), position_s(0, 2),
                        position_s(1, 1)
        //              
    };

    // . # .
    // # # .
    // . # .
    cells[3] = {
                        position_s(0, 1),
        position_s(1, 0), position_s(1, 1),
                        position_s(2, 1)
    };
    move(0, 3);
}



skews_c::skews_c() {
    color_id = 6;

    // . # #
    // # # .
    // . . .
    cells[0] = {
                        position_s(0, 1), position_s(0, 2),
        position_s(1, 0), position_s(1, 1)
        //
    };

    // . # .
    // . # #
    // . . #
    cells[1] = {
                        position_s(0, 1),
                        position_s(1, 1), position_s(1, 2),
                                        position_s(2, 2)
    };

    // . . .
    // . # #
    // # # .
    cells[2] = {
        //
                        position_s(1, 1), position_s(1, 2),
        position_s(2, 0), position_s(2, 1)
    };

    // # . .
    // # # .
    // . # .
    cells[3] = {
        position_s(0, 0),
        position_s(1, 0), position_s(1, 1),
                        position_s(2, 1)
    };
    move(0, 3);
}


skewz_c::skewz_c() {
    color_id = 7;
    // # # .
    // . # #
    // . . .
    cells[0] = {
        position_s(0, 0), position_s(0, 1),
                        position_s(1, 1), position_s(1, 2)
        //
    };

    // . . #
    // . # #
    // . # .
    cells[1] = {
                                        position_s(0, 2),
                        position_s(1, 1), position_s(1, 2),
                        position_s(2, 1)
    };

    // . . .
    // # # .
    // . # #
    cells[2] = {
        //
        position_s(1, 0), position_s(1, 1),
                        position_s(2, 1), position_s(2, 2)
    };

    // . # .
    // # # .
    // # . .
    cells[3] = {
                        position_s(0, 1),
        position_s(1, 0), position_s(1, 1),
        position_s(2, 0)
    };
    move(0, 3);
}
