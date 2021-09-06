# DLX-Sudoku-Solver
 * This is a C++ implementation of Donald Knuth's Algorithm X using the Dancing Links technique(DLX Algorithm).
 
 * Benchmarked the solver for 9x9 sudoku against 4 difficulty standards by 1000 boards of each to solve on average under 1 ms (max 7ms for any std of difficulty)

 * Benchmarking is done on 2 parameters(in a specific difficulty standard):
   *  Max time to solve any sudoku (in ms)
   *  Average time of 1000 sudoku (in ms)
 * <a/>
  Std | Simple | Easy | Intermediate |	Expert 
 :---:|:------:|:----:|:------------:|:------:
  Max	|  4.00	 | 4.00	|    7.00	     |  4.00  
  Avg	|  0.85	 | 1.19 |    1.11	     |  0.87  

## Acknowledgements
  * Dr Knuth's Dancing Links Paper: http://www.ocf.berkeley.edu/~jchu/publicportal/sudoku/0011047.pdf
