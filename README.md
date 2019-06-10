# PolyRootFinder
A program that implements secant and bisection algorithms in order to solve f(x)=0 for any given polynomial f.
Both algorithms need a tolerance value which is difference between calculated root and exact root. Also hybrit method that combines both secant and bisection algorithms is implemented, however this implementation can be improved.

### Compiling and Running
Program needs to be run from a command line with arguments in following order:
* Ininital guess number 1
* Initial guess number 2
* Tolerance value
* Rest of the arguments will be coefficients of polynomials with decreasing degree.

### Outputs:
* Root found by bisection method with number of iteration needed
* Root found by secant method with number of iteration needed
* Root found by hybrit method with number of iteration needed

### Exceptional Cases
* When power iteration does not converge into any value for 15 iteration
program prints out a warning
* When sign of the initial guesses are the same, bisection and hybrit methods does not work,
program prints out an error.

### Examples
**Example 1**  
Initial guesses x<sub>1</sub> = 1 , x<sub>2</sub> = 2, tolerance = 0.001 for f(x) = x<sup>2</sup> + 2x + 1
We need to give following arguments to program:
```
1 2 0.001 1 2 1
```
Result printed by program is:
```
WARNING: Bisection algorithm doesn't work if the signs of initial guesses are the same

The number of iterations exceeded the threshold
The root found by secant method is: -0.99856
Number of iteration: 15

WARNING: Hybrit algorithm doesn't work if the signs of initial guesses are the same
```
True result is -1.  
  
**Example 2**  
Initial guesses are x<sub>1</sub> = 1.5 , x<sub>2</sub> = 1.8, tolerance = 0.001 for f(x) = 2x<sup>4</sup> + 2x<sup>3</sup> - 7x<sup>2</sup> + x - 7   
We need to give following arguments to program:
```
1.5 1.8 0.001 2 2 -7 1 -7
```
Result printed by program is:
```
The root found by bisection method is: 1.66934
Number of iteration: 9

The root found by secant method is: 1.66941
Number of iteration: 4

The root found by hybrit method is: 1.66941
Number of iteration: 5
```
True result is 1.67.
