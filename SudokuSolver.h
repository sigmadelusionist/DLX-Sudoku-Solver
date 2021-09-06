#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include <iomanip>
#include <string>
#include "DancingLinks.h"

class Solver{
	public:
		Solver();
		int size;
		bool bmk;//for benchmarking
		int n;
		double time;
		int **sudoku;
		DancingLinks dlx;	

		void welcome();
		void instructions();
		void reset();
		void ask();
		int intIp();
		int intIpSudoku();
		bool checkSize(int);
		bool takeInput();
		bool validate();
		void solve();
		void BuildMatrix();
		void BuildCover();
		void TransformToCurrentGrid();
		void print();
};
