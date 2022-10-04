#include "SudokuSolver.hpp"
bool Solver::backtrack(){
    if(grid.is_complete()) return true;
    auto &var = grid.select_unassigned_Var();
    for(uint8 i = 1; i < 10; i++){
        if(!var.domain.has(i)) continue;
        var.val = i;
        if(grid.isin_valid_state())
            if(backtrack()) return true;
        var.val = 0;
    }
    return false;
}
void Solver::set_domains(){
    Domain rows[9], cols[9], subgrids[3][3];
    for(uint8 i = 0; i < 9; i++){
        for(uint8 j = 0; j < 9; j++){
            auto &value = grid.at(i, j).val;
            if(!value) continue;                        // unassigned
            rows[i].push(value);
            cols[j].push(value);
            subgrids[i / 3][j / 3].push(value);
        }
    }
    for(uint8 i = 0; i < 9; i++){
        for(uint8 j = 0; j < 9; j++){
            auto &var = grid.at(i, j);
            if(var.is_assigned()) continue;
            Domain takenDomain = rows[i] + cols[j] + subgrids[i / 3][j / 3];
            var.domain = (takenDomain).inverted();
        }
    }
}
bool Solver::solve(){
    set_domains();
    return backtrack();
}
