#ifdef _WIN32
	#include <Windows.h>
#endif
#include "SudokuBoard.hpp"
#include "Timer.hpp"

using namespace std::literals::string_literals;

bool solveWithRecursion{false};
std::string inFileName{"data/sample1.txt"};

void HandleInputArguments(const int argc, char* argv[]);

int main(int argc, char* argv[])
{
	try{
		Timer t{};
		Logger logFile{"log/sudoku_solver_" + t.YYYYMMDD_HHMMSS() + ".log"};
		HandleInputArguments(argc, argv);

		#ifdef _WIN32
			SetConsoleOutputCP(CP_UTF8);
		#endif

		logFile.writeWithTC("File to be loaded: " + inFileName);
		SudokuBoard sudoku{inFileName, logFile};
		sudoku.Print(std::cout);
		std::cout << "\n";

		t.Start();
		if(solveWithRecursion == true){
			logFile.writeWithTC("Solving Sudoku with recursive solve function..."s);
			sudoku.SolveWithRecursion();
		} else {
			logFile.writeWithTC("Solving Sudoku..."s);
			sudoku.Solve();
		}
		auto time = t.Stop();

		sudoku.Print(std::cout);
		std::cout << "Solve time: " << time << " s";
		sudoku.Print(logFile);
		logFile << "Solve time: " << time << " s";
		std::cin.get();
	}
	catch(const std::string & message){
		std::cout << message << std::endl;
	}
	catch(const std::exception & e){
		std::cout << e.what() << std::endl;
	}
	catch(...){
		std::cout << "Unexpected error." << std::endl;
	}
	return 0;
}

void HandleInputArguments(const int argc, char* argv[])
{
	switch(argc){
		case 1:
			break;
		case 2:
			if(std::string{argv[1]} == "-r"){
				solveWithRecursion = true;
			} else {
				inFileName = std::string{argv[1]};
			}
			break;
		case 3:
			if(std::string{argv[1]} == "-r"){
				solveWithRecursion = true;
				inFileName = std::string{argv[2]};
			} else if(std::string{argv[2]} == "-r"){
				solveWithRecursion = true;
				inFileName = std::string{argv[1]};
			} else {
				auto message = "Incorrect input parameters: " + std::string{argv[1]} + ", " + std::string{argv[2]};
				throw(message);
			}
			break;
		default:
			throw("Incorrect number of input parameters."s);
	}
	return;
}