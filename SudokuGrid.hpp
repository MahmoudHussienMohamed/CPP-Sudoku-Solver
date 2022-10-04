#ifndef __SUDOKU_GRID__
#define __SUDOKU_GRID__
#define twoPower(n) (1 << (n))
#include <iostream>
#include <string>
using uint8 = unsigned char;
using uint16 = unsigned short;
using std::string;
using std::istream;
using std::ostream;
class Domain{
    uint16 domain;
    Domain(uint16 newDomain): domain(newDomain){}
public:
    Domain(): domain(0) { }
    inline bool is_empty()     { return !domain; }
    inline void push(uint8 val){         domain |=  twoPower(val); }
    inline void pop(uint8 val) {         domain &= ~twoPower(val); }
    inline bool has(uint8 val) { return  domain &   twoPower(val); }
    inline Domain inverted()   { return  Domain(~domain); }
    inline Domain operator+(const Domain& other) {                                  // union of two Domains  
        return Domain(this->domain | other.domain); 
    }
    uint8 size(){ 
        uint8 cnt{};
        for(uint8 i = 1 ; i < 10; i++) cnt += has(i); 
        return cnt;
    }
};
struct Var{
    uint8 val;
    Domain domain;
    Var():val(0) {}
    inline bool is_assigned(){ return val; }
};
class SudokuGrid{
    Var grid[9][9]{};
    bool exists(bool[], Var&);
    static string format(char fill, char first, char internal_sep, char external_sep, char last){
        string formated(37, fill);
        formated.front() = first;
        formated.back() = last;
        for(size_t i = 4; i < formated.size() - 4; i += 4)
            formated[i] = i % 12 ? internal_sep : external_sep;
        return formated;
    }
public:
    bool is_complete();
    bool isin_valid_state();
    inline Var& at(uint8 row, uint8 col){ return grid[row][col]; }
    Var& select_unassigned_Var();
    friend istream& operator>>(istream &in, SudokuGrid& sg){
        for(uint8 i = 0, tmp; i < 9; i++)
            for(uint8 j = 0; j < 9; j++){
                in >> tmp;
                if(tmp >= '1' && tmp <= '9'){
                    tmp -= '0';
                    sg.grid[i][j].val = tmp;
                    sg.grid[i][j].domain.push(tmp);
                }
            }
        return in;
    }
    friend ostream& operator<<(ostream &out, const SudokuGrid& sg){
        //                     ═    ╔    ╤    ╦    ╗
        out << '\n' << format(-51, -55, -47, -53, -69) << '\n'; 
        //                          ─    ╟    ┼    ╫    ╢
        string internal_sep{format(-60, -57, -59, -41, -74)};
        //                          ═    ╠    ╪    ╬    ╣
        string external_sep{format(-51, -52, -40, -50, -71)};
        for(uint8 i = 0; i < 9; i++){
            out << char(-70);                                                       // = (║)
            for(uint8 j = 0; j < 9; j++){
                out << ' ' << int(sg.grid[i][j].val) << ' ';
                if(j != 8) out << char(j == 2 || j == 5 ? -70 : -77);               // (║) : (│)
            }
            out << char(-70) << '\n';                                               // = (║)
            if(i != 8) 
                out << (i == 2 || i == 5 ? external_sep : internal_sep) << '\n';
        }
        //             ═    ╚    ╧    ╩    ╝
        out << format(-51, -56, -49, -54, -68) << '\n';
        return out;
    }
};
#endif
