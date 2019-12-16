// Bilgehan GEÇÝCÝ 150117072

// This program adds the given number by checking to the given line. Then it adds the number to the given line.  

#include <stdio.h>

int count = 0, t=0;

void bunnyEars2(int t, int n){
	if(t > n){ // base case for the function
		return;
	}
	else if(t == 0){ // if the value is zero return the value
		printf("\nbunnyEars2(%d) -> %d", t, count);
	}
	//if n is odd
	else if(t%2 != 0){ // if the the value is odd number than add 2 to the that line 
		//add 2
		count += 2;
		printf("\nbunnyEars2(%d) -> %d", t, count);
	}
	//if n is even
	else if(t%2 == 0){ // if the value is even number that add 3 to the that line
		//add 3
		count += 3;
		printf("\nbunnyEars2(%d) -> %d", t, count);
	}
	t++;
	bunnyEars2(t, n); // Calling recursively to the bunnyEars2 function for the next iteration
}

int main(int argc, char** argv) { // Main function
	int n;
    printf("Please enter the number of lines (n=) : "); // Get the number of lines from the user.
    scanf("%d", &n);

    bunnyEars2(t, n); // Calling bunnyEars2 function
	
	return 0;
}
