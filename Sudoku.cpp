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
	double mn=1.0*(1<<30)-1.0,mx=0.0,ans=0.0;
	for(int i=0; i<game.n;i++){
		if(game.takeInput()){
			if(!game.bmk)cout<<"Validating Sudoku...\n\n";
			if(game.validate()){
				if(!game.bmk)cout<<"Validated Succesfully..\n\n";
				
				game.solve();

				if(game.dlx.isSolved){
					cout<<'\n'<<"Hurray!!\nSolved in: "<<(double)game.time<<" sec\n";
				}
				if(game.bmk){;
					mn=min(game.time,mn);
					mx=max(game.time,mx);
					ans+=game.time;
				}
			}else 
				cout<<"Invalid Sudoku...\n\n";
		}
		game.reset();
	}

	if(game.bmk){
		cout<<"Solved "<<game.n<<" sudoku's on average time of "<<(double)ans/game.n<<" sec."<<'\n';
		cout<<"Min. time: "<<mn<<" sec."<<'\n';
		cout<<"Max. time: "<<mx<<" sec."<<'\n';
	}

	cout<<"\nPress a number to exit..\n";
	game.intIp();

	return 0;
}
