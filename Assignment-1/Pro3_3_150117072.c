//Bilgehan GEÇÝCÝ  150117072
 
 //This program prints some fractals based on the user's input.
 
#include <stdio.h>

char triangle[32][63]; // Empty Triangle 
void init(); // A function fills the array with underscore
void tri0(int row, int col); // 0-input prototype
void tri1(int row, int col); // 1-input prototype
void tri2(int row, int col); // 2-input prototype
void tri3(int row, int col); // 3-input prototype
void tri4(int row, int col); // 4-input prototype
void printTriangle();


int main(){ // Main function 
	
	int n=0;
	
	do{ // User menu 
	
		printf("Enter '99' to exit the program...\n\n");
		printf("Enter the number of iterations: ");
		scanf("%d", &n);
		
		
		if(n == 0){ // 0 input iteration
			init();
			tri0(0,31);
			printTriangle();
		}
		
		else if(n == 1){ // 1 input iteration
			init();
			tri0(0,31);
			tri1(32,31);
			printTriangle();
		}
		else if(n == 2){ // 2 input iteration
			init();
			tri0(0,31);
			tri1(32,31);
			tri2(32,15);
			printTriangle();
		}
		else if(n == 3){ // 3 input iteration
			init();
			tri0(0,31);
			tri1(32,31);
			tri2(32,15);
			tri3(32,7);
			printTriangle();
		}
		else if(n == 4){ // 4 input iteration
			init();
			tri0(0,31);
			tri1(32,31);
			tri2(32,15);
			tri3(32,7);
			tri4(32,3);
			printTriangle();
		}
		else if(n == 99)printf("\nGood Bye!"); // if input is 99 the program terminates
		else printf("Iteration range: 0 < n < 5\n\n");	
	}while(n != 99);
	
	return;
}

void printTriangle(){ // PrintTriangle function prints the triangle array when it invokes.
	
	int i,j = 0;
	
	for(i=0; i<32; i++){
		
		for(j=0; j<63; j++){
			//triangle[i][j] = '_';
			printf("%c", triangle[i][j]);
		}
		printf("\n");
	}
}

void init(){ // Init function fills the trianngle with underscore. 
	
	int i,j = 0;
	
	for(i=0; i<32; i++){
		
		for(j=0; j<63; j++){
			triangle[i][j] = '_';
			//printf("%c", triangle[i][j]);
		}
		//printf("\n");
	}
}

void tri0(int row, int col){ // 0-input triangle 
	
	int i=0;
	if(row > 31){return;}
	
	triangle[row][col] = '1';
	
	for(i=0; i<=row; i++){
		triangle[row][col+i] = '1';
		triangle[row][col-i] = '1';
	}
		
	tri0(row+1, 31); // Calling recursively the tri0 function for next iteration
}

void tri1(int row, int col){ // 1-input triangle 
	
	int i=0;
	if(row < 16){return;}
	
	triangle[row][col] = '_';
	
	for(i=0; i<32-row; i++){
		triangle[row][col+i] = '_';
		triangle[row][col-i] = '_';
	}
	
	tri1(row-1, 31); // Calling recursively the tri1 function for next iteration
}

//15 31 47
void tri2(int row, int col){ // 2-input triangle 
	
	int i=0;
	if(row < 24){return;}
	
	triangle[row][col] = '_';
	triangle[row][col+16] = '_';
	triangle[row][col+32] = '_';
	
	for(i=0; i<32-row; i++){
		//col 15
		triangle[row][col+i] = '_';
		triangle[row][col-i] = '_';
		//col 31
		triangle[row-16][col+16+i] = '_';
		triangle[row-16][col+16-i] = '_';
		//col 47
		triangle[row][col+32+i] = '_';
		triangle[row][col+32-i] = '_';
	}
	
	tri2(row-1, 15); // Calling recursively the tri2 function for next iteration
}

//7 15 23 31 39 47 55
void tri3(int row, int col){ // 3-input triangle
	
	int i=0;
	if(row < 28){return;}
	
	triangle[row][col] = '_';
	triangle[row][col+8] = '_';
	triangle[row][col+16] = '_';
	triangle[row][col+24] = '_';
	triangle[row][col+32] = '_';
	triangle[row][col+40] = '_';
	triangle[row][col+48] = '_';
	
	for(i=0; i<32-row; i++){
		//col 7
		triangle[row][col+i] = '_';
		triangle[row][col-i] = '_';
		//col 15
		triangle[row-8][col+8+i] = '_';
		triangle[row-8][col+8-i] = '_';
		//col 23
		triangle[row][col+16+i] = '_';
		triangle[row][col+16-i] = '_';
		triangle[row-16][col+16+i] = '_';
		triangle[row-16][col+16-i] = '_';
		//col 31
		triangle[row-24][col+24+i] = '_';
		triangle[row-24][col+24-i] = '_';
		//col 39
		triangle[row][col+32+i] = '_';
		triangle[row][col+32-i] = '_';
		triangle[row-16][col+32+i] = '_';
		triangle[row-16][col+32-i] = '_';
		//col 47
		triangle[row-8][col+40+i] = '_';
		triangle[row-8][col+40-i] = '_';
		//col 55
		triangle[row][col+48+i] = '_';
		triangle[row][col+48-i] = '_';
	}
	
	tri3(row-1, 7); // Calling recursively the tri3 function for next iteration
}

//3 7 11 15 19 23 27 31 35 39 43 47 51 55 59 
void tri4(int row, int col){  // 4-input triangle
	
	int i=0;
	if(row < 30){return;}
	
	triangle[row][col] = '_';
	triangle[row][col+4] = '_';
	triangle[row][col+8] = '_';
	triangle[row][col+12] = '_';
	triangle[row][col+16] = '_';
	triangle[row][col+20] = '_';
	triangle[row][col+24] = '_';
	triangle[row][col+28] = '_';
	triangle[row][col+32] = '_';
	triangle[row][col+36] = '_';
	triangle[row][col+40] = '_';
	triangle[row][col+44] = '_';
	triangle[row][col+48] = '_';
	triangle[row][col+52] = '_';
	triangle[row][col+56] = '_';	
	
	for(i=0; i<32-row; i++){
		//col 3
		triangle[row][col+i] = '_';
		triangle[row][col-i] = '_';
		//col 7
		triangle[row-4][col+4+i] = '_';
		triangle[row-4][col+4-i] = '_';
		//col 11
		triangle[row][col+8+i] = '_';
		triangle[row][col+8-i] = '_';
		triangle[row-8][col+8+i] = '_';
		triangle[row-8][col+8-i] = '_';
		//col 15
		triangle[row-12][col+12+i] = '_';
		triangle[row-12][col+12-i] = '_';
		//col 19
		triangle[row][col+16+i] = '_';
		triangle[row][col+16-i] = '_';
		triangle[row-8][col+16+i] = '_';
		triangle[row-8][col+16-i] = '_';
		triangle[row-16][col+16+i] = '_';
		triangle[row-16][col+16-i] = '_';
		//col 23
		triangle[row-4][col+20+i] = '_';
		triangle[row-4][col+20-i] = '_';
		triangle[row-20][col+20+i] = '_';
		triangle[row-20][col+20-i] = '_';
		//col 27
		triangle[row][col+24+i] = '_';
		triangle[row][col+24-i] = '_';
		triangle[row-16][col+24+i] = '_';
		triangle[row-16][col+24-i] = '_';
		triangle[row-24][col+24+i] = '_';
		triangle[row-24][col+24-i] = '_';
		//col 31
		triangle[row-28][col+28+i] = '_';
		triangle[row-28][col+28-i] = '_';
		//col 35
		triangle[row][col+32+i] = '_';
		triangle[row][col+32-i] = '_';
		triangle[row-16][col+32+i] = '_';
		triangle[row-16][col+32-i] = '_';
		triangle[row-24][col+32+i] = '_';
		triangle[row-24][col+32-i] = '_';
		//col 39
		triangle[row-4][col+36+i] = '_';
		triangle[row-4][col+36-i] = '_';
		triangle[row-20][col+36+i] = '_';
		triangle[row-20][col+36-i] = '_';
		//col 43
		triangle[row][col+40+i] = '_';
		triangle[row][col+40-i] = '_';
		triangle[row-8][col+40+i] = '_';
		triangle[row-8][col+40-i] = '_';
		triangle[row-16][col+40+i] = '_';
		triangle[row-16][col+40-i] = '_';
		//col 47
		triangle[row-12][col+44+i] = '_';
		triangle[row-12][col+44-i] = '_';
		//col 51
		triangle[row][col+48+i] = '_';
		triangle[row][col+48-i] = '_';
		triangle[row-8][col+48+i] = '_';
		triangle[row-8][col+48-i] = '_';
		//col 55
		triangle[row][col+52+i] = '_';
		triangle[row][col+52-i] = '_';
		//col 59
		triangle[row][col+56+i] = '_';
		triangle[row][col+56-i] = '_';
	}
	
	tri4(row-1, 3); // Calling recursively the tri4 function for next iteration
}
