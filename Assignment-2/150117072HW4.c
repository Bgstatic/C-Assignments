#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Math.h>
#include <limits.h>
#define SIZE 10
// Bilgehan Geçici 150117072

// This program shows path of the metro stations based on given input values. The program tells the appropriate path  and smallest distance metro stations have
struct MetroStation{  // MetroStation Struct.
	char name[20];
	double x,y;
};typedef struct MetroStation MetroStation; // Typedef it to MetroStation.

struct MetroLine{ // MetroLine Struct
	char color[20];
	MetroStation MetroStations[SIZE];
	double x,y;
};typedef struct MetroLine MetroLine; // Typedef it to MetroLine.

struct MetroSystem{ // MetroSystem Struct.
	char name[20];
	MetroLine MetroLines[SIZE];
};typedef struct MetroSystem MetroSystem; // Typedef it to MetroSystem.

MetroSystem istanbul = {"istanbul", '\0'}; // Declare a MetroSystem named istanbul.

int equals(MetroStation s1, MetroStation s2){ //Equals method checks the given metrostation's name properties. 
	
	if(strcmp(s1.name, s2.name) == 0)
	  return 1; 
	  
	else
	  return 0; 
}

void addStation(MetroLine* l1, MetroStation s1){ // addStation adds the given MetroStation to the given MetroLine.
	int i=0;
	
	while(i<SIZE){
		if(l1->MetroStations[i].name[0] == '\0'){
			l1->MetroStations[i] = s1;
			break;
		}
		i++;
	}

}

int hasStation(MetroLine l1, MetroStation s1){ /*hasStation checks the given MetroLine if it has a MetroStation returns non-zero value 
                                                 if it is not returns zero value.*/
	
	int i; 
	
	for(i = 0; i<sizeof(l1)/sizeof(MetroStation); i++){
		
		if(strcmp(l1.MetroStations[i].name, s1.name) == 0){
		
		  return 1;
		  }
		  else
		  return 0; 
	}
}

MetroStation getFirstStop(MetroLine l1){  // getFirstStop returns a empty MetroStation if it is null at the beginning otherwise it returns the first stop.
	
	if(l1.MetroStations[0].name[0] == '\0'){
		
		MetroStation *new_metroStation = malloc(sizeof(MetroStation));
		return *new_metroStation;
	}
		
	else
		return l1.MetroStations[0]; 
	
}

MetroStation getPriorStop(MetroLine l1, MetroStation s1){ //getPriorStop checks properties of the given Metroline and MetroStation and 
                                                        //if it is at first stop then it returns empty MetroStation otherwise it returns previous stop.

	int i;
	
  if((strcmp(l1.MetroStations[0].name, s1.name) == 0) && (l1.MetroStations[0].x == s1.x) && (l1.MetroStations[0].y == s1.y)){
  	MetroStation *new_metroStation = malloc(sizeof(MetroStation));
	return *new_metroStation;
  }
  
  else{
  	for(i=1; i<SIZE+1; i++){
  		if((strcmp(l1.MetroStations[i].name, s1.name) == 0) && (l1.MetroStations[i].x == s1.x) && (l1.MetroStations[i].y == s1.y)){
  			return l1.MetroStations[i-1];
		}
	  }
  }
}

MetroStation getNextStop(MetroLine l1, MetroStation s1){ //getNextStop checks properties of the given Metroline and MetroStation and 
                                                        //if it is at end of the stop then it returns empty MetroStation otherwise it returns the next stop.
	
	int i;
	
  if((strcmp(l1.MetroStations[9].name, s1.name) == 0) && (l1.MetroStations[9].x == s1.x) && (l1.MetroStations[9].y == s1.y)){
  	MetroStation *new_metroStation = malloc(sizeof(MetroStation));
	return *new_metroStation;
  }
  
  else{
  	for(i=0; i<SIZE-1; i++){
  		if((strcmp(l1.MetroStations[i].name, s1.name) == 0) && (l1.MetroStations[i].x == s1.x) && (l1.MetroStations[i].y == s1.y)){
  			return l1.MetroStations[i+1];
		}
	  }
  }	
	
}

void addLine(MetroSystem* sys1, MetroLine l1){ //addLine adds the given MetroLine to the given MetroSystem. 
	int i=0;
	
	while(i<SIZE){
		if(sys1->MetroLines[i].color[0] == '\0'){
			sys1->MetroLines[i] = l1;
			break;
		}
		i++;
	}
}

void printLine(MetroLine l1){ //printLine prints the given MetroLine's MetroStations. 
	
	int i; 
	printf("Metroline %s:  ", l1.color ); 
	for(i = 0; i<SIZE; i++){
		
	    	printf("%s ", l1.MetroStations[i].name);
	    	
		
	}
	printf("\n");
}

void printPath(MetroStation metro[SIZE]){ // printPath prints the given MetroStation's array.
	
	int i;
	
	for(i = 0; i< SIZE; i++){
		
		printf("%s \n", metro[i].name);
	}
}

double getDistanceTravelled(MetroStation metro[]){ //getDistanceTravelled gets the distance between MetroStations.
	
	int i, arraySize = sizeof(metro) / sizeof(MetroStation);
	double dist;
	
	if(arraySize < 2)
		return 0.0;
		
	else{
		
		for(i=0; i<arraySize-1; i++)
		 dist += sqrt(((metro[i+1].x - metro[i].x), 2) + pow((metro[i+1].y - metro[i].y), 2));
	}
	
	return dist;
	
}

MetroStation findNearestStation(MetroSystem sys1, double x , double y){ // findNearestStation finds the given MetroSystem's nearest MetroStation. 
	
	int i,j, dist=0, closest=INT_MAX;
	int temp1, temp2;
	
	MetroStation *metroStation = malloc(sizeof(MetroStation));
	
	for(i=0; i<SIZE; i++){
		*metroStation = getFirstStop(sys1.MetroLines[i]);
		for(j=0; j<SIZE; j++){
			dist = sqrt(pow((metroStation->x - x), 2) + pow((metroStation->y - y), 2));
			if((dist < closest)){ //&& (metroStation->name[0] != '\0')){
				closest = dist;
				temp1=i; temp2=j;
			}
			*metroStation = getNextStop(sys1.MetroLines[i], sys1.MetroLines[i].MetroStations[j]);
		}
	}
	
	return sys1.MetroLines[temp1].MetroStations[temp2];
}

void getNeighboringStations(MetroSystem sys1, MetroStation s1, MetroStation neighboringStations[]){ // getNeighboringStations gets the neighbour stations 
                                                                                                   //in the given MetroSystem and MetroStation and adds the MetroStation to the given neighboringStations array.
	
	int i,j, neighbour_index=0;
	
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if(strcmp(sys1.MetroLines[i].MetroStations[j].name, s1.name) == 0){
				if(j == 0){neighboringStations[neighbour_index] = sys1.MetroLines[i].MetroStations[j+1]; neighbour_index++;}
				else if(j == SIZE-1){neighboringStations[neighbour_index] = sys1.MetroLines[i].MetroStations[j-1]; neighbour_index++;}
				else{
				neighboringStations[neighbour_index] = sys1.MetroLines[i].MetroStations[j+1];
				neighbour_index++;
				neighboringStations[neighbour_index] = sys1.MetroLines[i].MetroStations[j-1];
				neighbour_index++;
				}
			}
		}
	}
		
}

void recursiveFindPath(MetroStation start, MetroStation finish, MetroStation partialPath[], MetroStation bestPath[]){ // recursiveFindPath finds the paths of the given MetroStation
	
	int i;
	MetroStation neighbours[SIZE];
	MetroStation duplicatePath[sizeof(partialPath)/sizeof(MetroStation)];
	
	
	for(i=0; i<sizeof(partialPath)/sizeof(MetroStation); i++){
		if(equals(start, partialPath[i])){
			return;
		}
	}
	
	if(equals(start, finish)){
		for(i=0; i<sizeof(partialPath)/sizeof(MetroStation); i++){
			partialPath[i] = bestPath[i];
			}
	}
	
	else{
		getNeighboringStations(istanbul, start, neighbours);
		for(i=0; i<sizeof(partialPath)/sizeof(MetroStation); i++){
			duplicatePath[i] = partialPath[i];
		}
		duplicatePath[sizeof(partialPath)/sizeof(MetroStation)-1] = start;
		
		for(i=0; i<sizeof(neighbours)/sizeof(MetroStation); i++){
			
		}
	}
}

void findPath(MetroStation start, MetroStation finish, MetroStation path[]){ // findPath finds the paths with recursiveFindPath
	
	MetroStation partialPath[SIZE];
	
	recursiveFindPath(start, finish, path, partialPath);
}

int main()
{
	int i;
	double myX=1, myY=2; 
	double goalX=62, goalY=45; 
	
	// define 3 metro lines, 9 metro stations, and an empty myPath
	MetroLine red={'\0'}, blue={'\0'}, green={'\0'};
	MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
	MetroStation myPath[SIZE]={'\0'};
	
	strcpy(red.color, "red"); 
	strcpy(blue.color, "blue");
	strcpy(green.color, "green");

	
	strcpy(s1.name, "Haydarpasa"); 		s1.x=0; 	s1.y=0;
	strcpy(s2.name, "Sogutlucesme"); 	s2.x=10; 	s2.y=5;
	strcpy(s3.name, "Goztepe"); 		s3.x=20; 	s3.y=10;
	strcpy(s4.name, "Kozyatagi"); 		s4.x=30; 	s4.y=35;
	strcpy(s5.name, "Bostanci"); 		s5.x=45; 	s5.y=20;
	strcpy(s6.name, "Kartal"); 			s6.x=55; 	s6.y=20;
	strcpy(s7.name, "Samandira"); 		s7.x=60; 	s7.y=40;
	strcpy(s8.name, "Icmeler"); 		s8.x=70; 	s8.y=15;
	
	//Add several metro stations to the given metro lines.
	addStation(&red, s1); 
	addStation(&red, s2); 
	addStation(&red, s3); 
	addStation(&red, s4); 
	addStation(&red, s5); 
	addStation(&red, s8);
	
	addStation(&blue, s2); addStation(&blue, s3); addStation(&blue, s4); addStation(&blue, s6); addStation(&blue, s7);
	
	addStation(&green, s2); addStation(&green, s3); addStation(&green, s5); addStation(&green, s6); addStation(&green, s8);
	
	// Add red, blue, green metro lines to the Istanbul metro system.
	addLine(&istanbul, red);
	addLine(&istanbul, blue);
	addLine(&istanbul, green);
	
	// print the content of the red, blue, green metro lines
	printLine(red);
	printLine(blue);
	printLine(green);
		
		
	// find the nearest stations to the current and target locations
	MetroStation nearMe = findNearestStation(istanbul, myX, myY);
	MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);
	
	printf("\n");
	
	printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);
	
	// if the nearest current and target stations are the same, then print a message and exit.
	if(equals(nearMe, nearGoal)){
		printf("It is better to walk!\n");
		return 0;
	}
	
	// Calculate and print the myPath with the minimum distance travelled from start to target stations.
	findPath(nearMe, nearGoal, myPath);
	
	if(strlen(myPath[0].name) == 0)
		printf("There is no path on the metro!\n");
	else{
		printPath(myPath);
	}
	
	return;

}

