#include "SudokuGrid.hpp"
bool SudokuGrid::is_complete(){
    for(uint8 i = 0; i < 9; i++)
        for(uint8 j = 0; j < 9; j++)
            if(!grid[i][j].is_assigned()) 
                return false;
    return true;
}
bool SudokuGrid::exists(bool bar[], Var& var){
    if(!var.is_assigned()) return false;                            // No need to check value duplication if not assigned
    if(bar[var.val - 1]) return true;                               // Appeared before
    bar[var.val - 1] = true;                                        // If it's the first occurance record it
    return false;
}
bool SudokuGrid::isin_valid_state(){
    for(uint8 i = 0; i < 9; i++){
        bool rowsN[9]{}, colsN[9]{};
        for(uint8 j = 0; j < 9; j++)
            if(exists(rowsN, grid[i][j]) || exists(colsN, grid[j][i]))
                return false;                        
    }
    for(uint8 i = 0; i < 3; i++){
        for(uint8 j = 0; j < 3; j++){
            uint8 n = (i + 1) * 3, m = (j + 1) * 3;
            bool nums[9]{};
            for(uint8 r = i * 3; r < n; r++){
                for(uint8 c = j * 3; c < m; c++){
                    if(!grid[r][c].is_assigned()) continue;
                    if(nums[grid[r][c].val - 1]) return false;      // Appears twice for a 3 * 3 square
                    nums[grid[r][c].val - 1] = true;
                }
            }
        }
    }
    return true;
}
Var& SudokuGrid::select_unassigned_Var(){
    for(uint8 i = 0; i < 9; i++)
        for(uint8 j = 0; j < 9; j++)
            if(!grid[i][j].is_assigned())
                return grid[i][j];
}
