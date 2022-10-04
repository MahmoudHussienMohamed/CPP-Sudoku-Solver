#include "SudokuGrid.hpp"
#include "SudokuSolver.hpp"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    SudokuGrid sudoku_grid;
    if(argc == 2){
        ifstream grid_file(argv[1]);
        grid_file >> sudoku_grid;
        grid_file.close();
    } 
    else cin >> sudoku_grid;
    Solver solver(sudoku_grid);
    bool solvable = solver.solve();
    if(solvable) cout << sudoku_grid;
    else cout << "Sudoku grid couldn't be solved!\n";
    return 0;
}
