#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include "DancingLinks.h"

class Solver{
	public:
		Solver();
		int size;
		int **sudoku;
		DancingLinks dlx;	

		void welcome();
		void instructions();
		int intIp();
		bool checkSize(int);
		bool takeInput();
		bool validate();
		void solve();
		void BuildMatrix();
		void BuildCover();
		void TransformToCurrentGrid();
		void print();
};