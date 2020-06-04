#ifndef SUDOKUNUM_HPP
#define SUDOKUNUM_HPP

class SudokuNum
{
private:
	int value{0};
	int row{0};
	int column{0};
	int block{0};
	bool original{false};
public:
	SudokuNum() = delete;
	SudokuNum(int v, int r, int c, int b, bool o): value{v}, row{r}, column{c}, block{b}, original{o} {}
	SudokuNum(SudokuNum const &) = default;
    SudokuNum & operator=(SudokuNum const &) = delete;
	SudokuNum(SudokuNum &&) = default;
	SudokuNum & operator=(SudokuNum &&) = delete;
	~SudokuNum() = default;

	int GetValue() const { return value; }
	int GetRow() const { return row; }
	int GetColumn() const { return column; }
	int GetBlock() const { return block; }
	int IsProtected() const { return original; }
	void SetValue(int value){ this->value = value; }
};

#endif //SUDOKUNUM_HPP