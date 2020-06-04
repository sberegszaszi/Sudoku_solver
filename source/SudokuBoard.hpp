#ifndef SUDOKUBOARD_HPP
#define SUDOKUBOARD_HPP

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include "SudokuNum.hpp"
#include "Logger.hpp"

class SudokuBoard
{
private:
	std::vector<SudokuNum> sudokuData;
	Logger & logFile;

	bool TestBlock() const;
	bool TestRow() const;
	bool TestColumn() const;
	bool Test() const;
	bool isPossible(size_t const index, int const value);
public:
	SudokuBoard() = delete;
	explicit SudokuBoard(std::string file, Logger & logfile);
	SudokuBoard(SudokuBoard const &) = delete;
    SudokuBoard & operator=(SudokuBoard const &) = delete;
	SudokuBoard(SudokuBoard &&) = delete;
	SudokuBoard & operator=(SudokuBoard &&) = delete;
	~SudokuBoard() = default;

	template <typename oStream> void Print(oStream & os) const;
	void Solve();
	bool SolveWithRecursion();
};


template <typename oStream>
void SudokuBoard::Print(oStream & os) const
{
	const std::string borderType1 = u8"╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗";
	const std::string borderType2 = u8"╟───┼───┼───╫───┼───┼───╫───┼───┼───╢";
	const std::string borderType3 = u8"╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣";
	const std::string borderType5 = u8"╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝";
	const std::string vLine1 = u8"║";
	const std::string vLine2 = u8"│";
	os << borderType1 << "\n";
	for(auto it = sudokuData.begin(); it != sudokuData.end(); ++it){
		if((*it).GetColumn() % 3 == 1){
			os << vLine1;
		} else {
			os << vLine2;
		}

		if((*it).GetValue() != 0){
			os << " " << (*it).GetValue() << " ";
		} else {
			os << "   ";
		}

		if ((*it).GetColumn() == 9 && (*it).GetRow() !=9){
			os << vLine1 << "\n";
			if ((*it).GetRow() % 3 == 0){
				os << borderType3 << "\n";
			} else {
				os << borderType2 << "\n";
			}
		}
	}
	os << vLine1 << "\n" << borderType5 << "\n";
}

#endif // SUDOKUBOARD__HPP