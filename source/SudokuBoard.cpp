#include "SudokuBoard.hpp"

using namespace std::string_literals;

SudokuBoard::SudokuBoard(std::string file, Logger & logfile):  sudokuData{}, logFile{logfile}
{
	int num = 0, row = 0, column = 0, block = 0;
	bool protect = true;
	std::string line, ch;
	std::ifstream inFile(file);
	if(!inFile.is_open()){
		throw("Unable to open file."s);
	} else {
		while(std::getline(inFile, line)){
			column = 0;
			++row;
        	for(auto c : line){
				if(isdigit(c)){
                	num = static_cast<int>(c) - 48;
					++column;
					if(row <= 3){
						if(column <= 3){
							block = 1;
						} else if (column >= 3 && column <= 6){
							block = 2;
						} else {
							block = 3;
						}
					} else if (row >=3 && row <= 6){
						if(column <= 3){
							block = 4;
						} else if (column >= 3 && column <= 6){
							block = 5;
						} else {
							block = 6;
						}
					} else {
						if(column <= 3){
							block = 7;
						} else if (column >= 3 && column <= 6){
							block = 8;
						} else {
							block = 9;
						}
					}
					if(num == 0){
						protect = false;
					} else {
						protect = true;
					}
					sudokuData.emplace_back(SudokuNum{num, row, column, block, protect});
				}
			}
        }
    }
	inFile.close();
	if(sudokuData.size() != 81 || Test() != true){
		throw("Loaded Sudoku board is invalid."s);
	} else {
		logFile.writeWithTC("File successfully loaded."s);
	}
}

bool SudokuBoard::TestBlock() const
{
	bool result = true;
	for(auto x = sudokuData.begin(); x != sudokuData.end(); ++x){
		for(auto i = sudokuData.begin(); i != sudokuData.end(); ++i){
			if( (x != i) && ((*i).GetValue() != 0) &&
				((*x).GetBlock() == (*i).GetBlock()) &&
				((*x).GetValue() == (*i).GetValue()) ){
				result = false;
				break;
			}
		}
	}
	return result;
}

bool SudokuBoard::TestRow() const
{
	bool result = true;
	for(auto x = sudokuData.begin(); x != sudokuData.end(); ++x){
		for(auto i = sudokuData.begin(); i != sudokuData.end(); ++i){
			if( (x != i) && ((*i).GetValue() != 0) &&
				((*x).GetRow() == (*i).GetRow()) &&
				((*x).GetValue() == (*i).GetValue()) ){
				result = false;
				break;
			}
		}
	}
	return result;
}

bool SudokuBoard::TestColumn() const
{
	bool result = true;
	for(auto x = sudokuData.begin(); x != sudokuData.end(); ++x){
		for(auto i = sudokuData.begin(); i != sudokuData.end(); ++i){
			if( (x != i) && ((*i).GetValue() != 0) &&
				((*x).GetColumn() == (*i).GetColumn()) &&
				((*x).GetValue() == (*i).GetValue()) ){
				result = false;
				break;
			}
		}
	}
	return result;
}

bool SudokuBoard::Test() const
{
	bool result = false;
	if(TestBlock() && TestRow() && TestColumn()){
		result = true;
	}
	return result;
}

bool SudokuBoard::isPossible(size_t const index, int const value)
{
	sudokuData.at(index).SetValue(value);
	bool result = Test();
	sudokuData.at(index).SetValue(0);
	return result;
}

void SudokuBoard::Solve()
{
	enum Steps {go_back, stay_and_increase, go_to_next};
	Steps next_step;
	size_t current_index = 0;
	if(sudokuData.at(0).IsProtected() == false){
		next_step = stay_and_increase;
	} else {
		next_step = go_to_next;
	}
	while(current_index < sudokuData.size()){
		std::ostringstream logMessage;
		logMessage << "Index = " << current_index << ", Value = " << (sudokuData.at(current_index)).GetValue() <<  ", Next step: ";
		switch(next_step){
			case 0: logMessage << "go_back"; break;
			case 1: logMessage << "stay_and_increase"; break;
			case 2: logMessage << "go_to_next"; break;
		}
		logFile.writeWithTC(logMessage.str());
		switch(next_step){
			case go_back:
				(sudokuData.at(current_index)).SetValue(0);
				--current_index;
				while(current_index > 0){
					if((sudokuData.at(current_index)).IsProtected() == true){
						--current_index;
					} else if((sudokuData.at(current_index)).IsProtected() == false && (sudokuData.at(current_index)).GetValue() == 9){
						(sudokuData.at(current_index)).SetValue(0);
						--current_index;
					} else {
						break;
					}
				}
				(sudokuData.at(current_index)).SetValue((sudokuData.at(current_index)).GetValue() + 1);
				break;
			case stay_and_increase:
				(sudokuData.at(current_index)).SetValue((sudokuData.at(current_index)).GetValue() + 1);
				break;
			case go_to_next:
				++current_index;
				if(current_index == sudokuData.size()){
					break;
				}
				while(current_index < sudokuData.size() && (sudokuData.at(current_index)).IsProtected() == true){
					++current_index;
				}
				if(current_index < sudokuData.size() && (sudokuData.at(current_index)).IsProtected() == false){
					(sudokuData.at(current_index)).SetValue((sudokuData.at(current_index)).GetValue() + 1);
				}
				break;
		}
		if(current_index < sudokuData.size()){
			if(Test() == false){
				if((sudokuData.at(current_index)).GetValue() < 9){
					next_step = stay_and_increase;
				} else {
					next_step = go_back;
				}
			} else {
				next_step = go_to_next;
			}
		}
	}
}

bool SudokuBoard::SolveWithRecursion()
{
	for(auto index = 0; index < 81; ++index){
		std::ostringstream logMessage;
		logMessage << "Index = " << index << ", Value = " << (sudokuData.at(index)).GetValue();
		logFile.writeWithTC(logMessage.str());
		if(sudokuData.at(index).GetValue() == 0){
			for(int value = 1; value < 10; ++value){
				if(isPossible(index, value) == true){
					sudokuData.at(index).SetValue(value);
					if(this->SolveWithRecursion()){
						return true;
					}
					sudokuData.at(index).SetValue(0);
				}
			}
			return false;
		}
	}
	return true;
}