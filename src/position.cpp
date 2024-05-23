#include "position.hpp"

Position::Position(int t_row, int t_col)
    : row {t_row}
    , col {t_col}
{
    //assert(col >= 0 && row >= 0);
}

//void
//Position::set_col(int t_col) {
//    assert(t_col >= 0);
//    m_col = t_col;
//}

//void
//Position::set_row(int t_row) {
//    assert(t_row >= 0);
//    m_row = t_row;
//}

//int
//Position::get_col() const {
//    return m_col;
//}

//int
//Position::get_row() const {
//    return m_row;
//}
