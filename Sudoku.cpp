#include "SudokuSolver.h"

using namespace std;

signed main(){
	Solver game;
	game.ask();
	
	if(!game.bmk){
		game.welcome();

		cout<<"Press enter to Continue.....";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout<<'\n';

		game.instructions();

		cout<<"Press enter to Continue.....";
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout<<'\n';
	}
	double mn=1.0*(1e9),mx=0;
	for(int i=0; i<game.n;i++){
		if(game.takeInput()){
			if(!game.bmk)cout<<"Validating Sudoku...\n\n";
			if(game.validate()){
				if(!game.bmk)cout<<"Validated Succesfully..\n\n";
				clock_t start_t = clock();
				game.solve();
				clock_t end_t = clock();
				cout<<'\n'<<"Hurray!!\nSolved in: "<<(double) (end_t - start_t) / CLOCKS_PER_SEC<<" sec\n";
				if(game.bmk){
					double ans=(double) (end_t - start_t) / CLOCKS_PER_SEC;
					mn=min(ans,mn);
					mx=max(ans,mx);
					game.time+=ans;
				}
			}else 
				cout<<"Invalid Sudoku...\n\n";
		}
		game.reset();
	}

	if(game.bmk){
		cout<<"Solved "<<game.n<<" sudoku's on average time of "<<game.time/game.n<<" sec."<<'\n';
		cout<<"Min. time: "<<mn<<" sec."<<'\n';
		cout<<"Max. time: "<<mx<<" sec."<<'\n';
	}

	cout<<"\nPress a number to exit..\n";
	game.intIp();

	return 0;
}
