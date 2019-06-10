#include <stdio.h>
#include <iostream>
#include <cstdlib> 
#include <math.h>

using namespace std;
float tolerance = 0;			// tolerance value for power iteration

int abs(int x)
{
/*
  This function returns absolute value of x.
  
  @param x Integer value
  @return Absolute value of x
*/
	if(x<0)
	{
		x=-x;
	}
	return x;
}

float abs(float x)
{
/*
  This function returns absolute value of x.
  
  @param x Float value
  @return Absolute value of x
*/
	if(x<0)
	{
		x=-x;
	}
	return x;
}

// takes nth power of x
float power (float x, int n)
{
	float sum=1.0;
	if (n<0){
		for(int i=0;i<abs(n);i++){
			sum*=1.0/x;
		}
	}
	else{	
		for(int i=0;i<n;i++){
			sum*=x;
		}
	}
	return sum;	
}

// returns sign of a float number
int sign (float x){
	if(x < 0){
		return -1;
	}
	else if (x>0) {
		return 1;
	}
	else{
		return 0;
	}	
}

class Polynomial{
		// degree of polynomial
		int degree;
		// coefficients of polynomial
		float *coeff;
		float root;
	public:
		// constructers
		Polynomial ();
   		Polynomial(char *argv[], int n);
   		// copy constructer and copy assignment
		Polynomial(const Polynomial& P); 
        Polynomial& operator= (const Polynomial& P);
        // destructer
    	~Polynomial();
		// prints coefficients of the polynomial        
		void print();
		// prints current root of polynomial
		void printRoot(int n);
		// function that evaluates polynomial for a given value
		float result(float x);
		// bisection method for finding a root of the polynomial
		int bisection(float ing1,float ing2);
		// secant method for finding a root of the polynomial
		int secant(float ing1,float ing2);
		// secant method for finding a root of the polynomial
		int hybrit(float ing1,float ing2);
};


int main( int argc, char *argv[] )  {
	//initial guesses
   	float ing1,ing2;
   	ing1 = atof(argv[1]);
   	ing2 = atof(argv[2]);

   	tolerance = atof(argv[3]);	     	// User defined tolerance value for algorithms	   
	
	// degree of polynomial
	int dim = argc-5;
	
	// construct polynomial with given coefficients
	Polynomial dene(argv,argc);
	
	// run bisection algorithm and print results
	int iter=dene.bisection(ing1,ing2);
	if (iter!= 0){
		dene.printRoot(0);
		cout<< "Number of iteration: "<<iter<<endl<<endl;
	}
	
	// run secant algorithm and print results
	iter=dene.secant(ing1,ing2);
	if (iter!= 0){
		dene.printRoot(1);
		cout<< "Number of iteration: "<<iter<<endl<<endl;
	}
	
	// run hybrit algorithm and print results
	iter=dene.hybrit(ing1,ing2);
	if (iter!= 0){
		dene.printRoot(2);
		cout<< "Number of iteration: "<<iter<<endl<<endl;
	}
}



/************* Class Polynomial Definitions **********************/
// Default constructer
Polynomial::Polynomial():degree(0),root(0){
	coeff= 0;
}

// Default constructer with command line arguments
Polynomial::Polynomial(char *argv[], int n):degree(n-5),root(0){
	this->coeff = new float[degree];
    for(int i=0;i<degree+1;i++){
    	coeff[i]=atof(argv[i+4]);
	}
}

// destructer
Polynomial::~Polynomial () {
	delete[] coeff;	
}

// copy constructer
Polynomial::Polynomial(const Polynomial& P){
	this->degree=P.degree;
	this->root=P.root;
    this->coeff = new float[degree];

    for (int i=0;i<degree+1;i++)
	{
		this->coeff[i]=P.coeff[i];
	}

}

//copy assignment
Polynomial& Polynomial:: operator= (const Polynomial& P){
	// delete allacoted memory
	delete[] coeff;
	
	// assign degree of P to the polynomial	
	this->degree=P.degree;
	// assign root
	this->root=P.root;
	// re-allocate memory that matches polynomial P
	this->coeff = new float[degree];
	for (int i=0;i<degree+1;i++)
	{
		this->coeff[i]=P.coeff[i];
	}
	return *this;
}


// Prints values of vector
void Polynomial::print(){
    
{
	for(int i=0;i<degree+1;i++)
		{
			cout<<coeff[i]<<endl;
		}
	cout<<endl;
}

}

void Polynomial::printRoot(int n){
	if(n==0){
		cout<<"The root found by bisection method is: "<<root<<endl;
	}
	if(n==1){
		cout<<"The root found by secant method is: "<<root<<endl;
	}
	if(n==2){
		cout<<"The root found by hybrit method is: "<<root<<endl;
	}

}

// Evaluate function for a given value
float Polynomial:: result(float x){
	float sum=0;
	for(int i=0;i<degree+1;i++){
		sum+= coeff[i]*power(x,degree-i);
	}
	return sum;
}



// Bisection method for finding roots

int Polynomial::bisection(float ing1, float ing2){
	// First check whether bisection method is valid or not
	if(sign(result(ing1))== sign(result(ing2)) && sign(result(ing1))!=0 ) {
		cout<<"WARNING: Bisection algorithm doesn't work if the signs of initial guesses are the same"<<endl<<endl;
		return 0;		
	}
	int count = 0;
	float m = 0;
	while (abs(ing1-ing2)>tolerance){
		m=ing1+((ing2-ing1)/2);
		
		// Checks sign to find proper interval
		if(sign(result(ing1))== sign(result(m))){
			ing1=m;
		}
		else {
			ing2=m;
		}
		count++;

		
		// Checks threshold condition for iterations
		if(count==15){
			cout<<"The number of iterations exceeded the threshold"<< endl;
			break;
		}
	}
	root=m;
	return count;
}

// Secant method for finding roots

int Polynomial::secant(float ing1, float ing2){
	
	int count = 0;
	float m = 0;
	while (abs(ing1-ing2)>tolerance){
		
		// Checks result to find interval closest to root
		if(abs(result(ing1)) >= abs(result(ing2))){
			//find next value for secant 
			m=ing2-(result(ing2)*(ing2-ing1))/(result(ing2)-result(ing1));
			ing1=m;
		}
		else {
			//find next value for secant 
			m=ing1-(result(ing1)*(ing1-ing2))/(result(ing1)-result(ing2));			
			ing2=m;
		}
		count++;
		
		// Checks threshold condition for iterations
		if(count==15){
			cout<<"The number of iterations exceeded the threshold"<< endl;
			break;
		}
	}
	root=m;
	return count;
}

// Secant method for finding roots

int Polynomial::hybrit(float ing1, float ing2){
	// First check whether bisection method is valid or not
	if(sign(result(ing1))== sign(result(ing2)) && sign(result(ing1))!=0 ) {
		cout<<"WARNING: Hybrit algorithm doesn't work if the signs of initial guesses are the same"<<endl<<endl;
		return 0;		
	}
	int count = 0;
	float m = 0;
	
	while (abs(ing1-ing2)>tolerance && count<2){
		m=ing1+((ing2-ing1)/2);
		// Checks sign to find proper interval
		if(sign(result(ing1))== sign(result(m))){
			ing1=m;
		}
		else {
			ing2=m;
		}
		count++;
		}
				
	while (abs(ing1-ing2)>tolerance){
		
		// Checks result to find interval closest to root
		if(abs(result(ing1)) >= abs(result(ing2))){
			//find next value for secant 
			m=ing2-(result(ing2)*(ing2-ing1))/(result(ing2)-result(ing1));
			ing1=m;
		}
		else {
			//find next value for secant 
			m=ing1-(result(ing1)*(ing1-ing2))/(result(ing1)-result(ing2));			
			ing2=m;
		}
		count++;
				
		// Checks threshold condition for iterations
		if(count==15){
			cout<<"The number of iterations exceeded the threshold"<< endl;
			break;
		}
	}
	root=m;
	return count;
}

/************* Class Polynomial Definitions END *******************/




