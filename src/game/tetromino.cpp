#include "tetromino.hpp"
#include "position.hpp"


el::el() 
{
    color_id_ = 1;
    //  . . #
    //  # # #
    //  . . .
    cells_[0] = {
                                        ::position(0, 2),
        ::position(1, 0), ::position(1, 1), ::position(1, 2),
        //              
    };

    // . # .
    // . # .
    // . # #
    cells_[1] = {
                        ::position(0, 1),
                        ::position(1, 1),
                        ::position(2, 1), ::position(2, 2)
    };

    // . . .
    // # # #
    // # . .
    cells_[2] = {
        //              
        ::position(1, 0), ::position(1, 1), ::position(1, 2),
        ::position(2, 0),
    };

    // # # .
    // . # .
    // . # .
    cells_[3] = {
        ::position(0, 0), ::position(0, 1),
                        ::position(1, 1),
                        ::position(2, 1)
    };

}



jay::jay()
{
    color_id_ = 2;
    //  # . .
    //  # # #
    //  . . .
    cells_[0] = {
        ::position(0, 0),
        ::position(1, 0), ::position(1, 1), ::position(1, 2),
        //              
    };

    // . # #
    // . # .
    // . # .
    cells_[1] = {
                        ::position(0, 1), ::position(0, 2),
                        ::position(1, 1),
                        ::position(2, 1),
    };

    // . . .
    // # # #
    // . . #
    cells_[2] = {
        //              
        ::position(1, 0), ::position(1, 1), ::position(1, 2),
                                        ::position(2, 2),
    };

    // . # .
    // . # .
    // # # .
    cells_[3] = {
                        ::position(0, 1),
                        ::position(1, 1),
        ::position(2, 0), ::position(2, 1)
    };
}



straight::straight() 
{
    color_id_ = 3;

    // . . . .
    // # # # #
    // . . . .
    // . . . .
    cells_[0] = {
        //
        ::position(1, 0), ::position(1, 1), ::position(1, 2), ::position(1, 3)
        //
        //
    };

    // . . # .
    // . . # .
    // . . # .
    // . . # .
    cells_[1] = {
                                        ::position(0, 2),
                                        ::position(1, 2),
                                        ::position(2, 2),
                                        ::position(3, 2)
    };

    // . . . .
    // . . . .
    // # # # #
    // . . . .
    cells_[2] = {
        // 
        // 
        ::position(2, 0), ::position(2, 1), ::position(2, 2), ::position(2, 3)
        //
    };


    //  . # . .
    //  . # . .
    //  . # . .
    //  . # . .
    cells_[3] = {
            ::position(0, 1),
            ::position(1, 1),
            ::position(2, 1),
            ::position(3, 1)
    };
    move(-1, 3);
}

square::square() {
    color_id_ = 4;

    // All rotation are the same.
    // # #
    // # #
    cells_[0] = 
    cells_[1] = 
    cells_[2] = 
    cells_[3] = {
        ::position(0, 0), ::position(0, 1),
        ::position(1, 0), ::position(1, 1)
    };
}

tee::tee() {
    color_id_ = 5;

    // . # .
    // # # #
    // . . .
    cells_[0] = {
                        ::position(0, 1),
        ::position(1, 0), ::position(1, 1), ::position(1, 2),
        //
    };

    // . # .
    // . # #
    // . # .
    cells_[1] = {
                        ::position(0, 1), 
                        ::position(1, 1), ::position(1, 2),
                        ::position(2, 1),
    };

    //  # # #
    //  . # .
    //  . . .
    cells_[2] = {
        ::position(0, 0), ::position(0, 1), ::position(0, 2),
                        ::position(1, 1)
        //              
    };

    // . # .
    // # # .
    // . # .
    cells_[3] = {
                        ::position(0, 1),
        ::position(1, 0), ::position(1, 1),
                        ::position(2, 1)
    };
}



skew_s::skew_s() {
    color_id_ = 6;

    // . # #
    // # # .
    // . . .
    cells_[0] = {
                        ::position(0, 1), ::position(0, 2),
        ::position(1, 0), ::position(1, 1)
        //
    };

    // . # .
    // . # #
    // . . #
    cells_[1] = {
                        ::position(0, 1),
                        ::position(1, 1), ::position(1, 2),
                                        ::position(2, 2)
    };

    // . . .
    // . # #
    // # # .
    cells_[2] = {
        //
                        ::position(1, 1), ::position(1, 2),
        ::position(2, 0), ::position(2, 1)
    };

    // # . .
    // # # .
    // . # .
    cells_[3] = {
        ::position(0, 0),
        ::position(1, 0), ::position(1, 1),
                        ::position(2, 1)
    };
}


skew_z::skew_z() {
    color_id_ = 7;
    // # # .
    // . # #
    // . . .
    cells_[0] = {
        ::position(0, 0), ::position(0, 1),
                        ::position(1, 1), ::position(1, 2)
        //
    };

    // . . #
    // . # #
    // . # .
    cells_[1] = {
                                        ::position(0, 2),
                        ::position(1, 1), ::position(1, 2),
                        ::position(2, 1)
    };

    // . . .
    // # # .
    // . # #
    cells_[2] = {
        //
        ::position(1, 0), ::position(1, 1),
                        ::position(2, 1), ::position(2, 2)
    };

    // . # .
    // # # .
    // # . .
    cells_[3] = {
                        ::position(0, 1),
        ::position(1, 0), ::position(1, 1),
        ::position(2, 0)
    };
    move(0, 3);
}
