// Bilgehan GEÇİCİ 150117072

/*This program calculates the super digit of the given number. First it generates a number repeater for the given number than it computes the
 super digit of that number.*/


# include <stdio.h>
#include <math.h>

int super_digit(int n){ 
	
	int sum = 0;
	int remaining = 0; 
	
		if(n == 0){  // if the given number is zero than the sum of the digit is zero 
		
		return 0; 
        } 	
		else{	
		
		remaining =  n % 10;
		sum = remaining + super_digit(n/10); // Calling super_digit recursively to get the sum of the digits.
		
		}
	
	if(sum > 9){ // if the sum is more than 9 than it should be do the same executions in super_digit function 
		
	n = sum;
	sum = super_digit(n);	
		
	}
	return sum;
}

int numberRepeater(int n, int k, int digit){   // NumberRepeater function for the which number repeats 
	int add=0, oldN = n;
	
	while(k-1 > 0){       // Get the given values in types of 
		add = pow(10,digit);
		n = n * add;
		n = n + oldN;
		k--;
	}
	
	return n;
}

void main(){ // Main function
	int n, k, temp, digit=0;
	int result = 0; 
	int Current_Number;
	printf("Please enter a number (n=) : "); // Get the value of the result from the user. 
	scanf("%d", &n);
	printf("\nPlease enter repetition factor (k=): "); // Get the number of repetition time for the given number.
	scanf("%d", &k);
	
	temp = n;
	
    while(temp != 0) 
    {
        
        digit++;
        temp /= 10;
    }
	
	Current_Number = numberRepeater(n, k, digit); // Get the number from numberRepeater function
	result = super_digit(Current_Number); // Get the result
	printf("\nSuper digit of number %d is %d.", Current_Number, result); // Printing result
}
