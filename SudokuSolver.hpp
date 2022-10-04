#ifndef __SUDOKU_SOLVER__
#define __SUDOKU_SOLVER__
#include "SudokuGrid.hpp"
class Solver{
    SudokuGrid &grid;
    bool backtrack();
    void set_domains();
public:
    Solver(SudokuGrid& sg) : grid(sg) {}
    inline void set(SudokuGrid& sg){ grid = sg; }
    bool solve();
};
#endif
