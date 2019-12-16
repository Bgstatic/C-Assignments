#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//Bilgehan Geçici 150117072 

//This program reads the given input and it crates a list about songs and it's durations. 
//It sorts the list in chronological, alphabetical order. Also it sorts the list based on duration and random order.
// It can also insert the given song to the end of list , also it can delete the given song if it is exist then also it can print the all type of list.

struct song{ // Default struct type for songs. 
	
	char songName[25];
	int duration;
	struct song *chrono_next;
	struct song *alpha_next;
	struct song *duration_next;
	struct song *random_next;
	
};
 typedef struct song Song; // Typedef it to 'Song'.
 
//Prototypes of various functions.
void instructions(void);
int *shuffle(int[], int);
void insertChrono(Song **, Song *);
void insertAlpha(Song **, Song *);
void insertDuration(Song **, Song *);
int deleteSong(Song **, char[], int);
int isInPlayList(Song *, char[]);
void printChrono(Song *);
void printChrono_out_file(Song *, FILE *);
void printAlpha(Song *);
void printAlpha_out_file(Song *, FILE *);
void printDuration(Song *);
void printDuration_out_file(Song *, FILE *);
void printRandom(Song *, int);
void printRandom_out_file(Song *, FILE *, int);
 


int main(){
	
	// Initialy there are no nodes.
	Song *headChrono=NULL, *headAlpha=NULL, *headDuration=NULL;
	
	FILE *fp = fopen("songs.txt", "r");
	char line[100]; // Char array for scan the given line.
	char *name, *duration, *min_s, *sec_s = NULL;
	int min, sec, size=0;
	
	//	first, read the text file and insert it
	if(fp != NULL){
		
		while(fgets(line,sizeof line,fp)!= NULL){
			
			Song *new_song = malloc(sizeof(Song)); // Create new node.
			
			//strtok modifies the original string.
			//It puts NULL characters ('\0') at the delimiter position after every call to strtok.
			
			//	split the line into parts
            name=strtok(line,"\t"); // Get the name from input file.
            duration=strtok(NULL,"\t"); // Get the duration from input file.
            
            min_s=strtok(duration,":");sec_s=strtok(NULL,":"); // Get the minutes and seconds from input file.
            min=atoi(min_s);sec=atoi(sec_s); // Converting string values to the int value.
            
            sec = min*60 + sec;  //Get duration in seconds.
            strcpy(new_song->songName, name); // Assign the input file's  name to the new node's name.
            new_song->duration = sec; // Assign the seconds value to the new song's duration value.
            
            size++; // increment the list size by one. 
            
            //	fill the playlist
            insertChrono(&headChrono, new_song);
            insertAlpha(&headAlpha, new_song);
            insertDuration(&headDuration, new_song);
            
		}
		
	}
	
	char buffer[100]; // Char array entered song name and duration by user. 
	FILE *f;
	
	instructions();
	
	printf("Enter your choice:\n");
	unsigned int choice; // user's choice
	scanf("%u", &choice);
   
	// loop while user does not choose 5
	while (choice != 5) {

		switch (choice) {
			
        	case 1:
			{
				name, duration, min_s, sec_s = NULL;
			 	Song *new_song = malloc(sizeof(Song));
	            puts("Enter a song name with duration: ");
	            scanf(" %[^\n]", &buffer);
	            
	            //	split the line into parts
	            name=strtok(buffer,"\t");
	            duration=strtok(NULL,"\t");
	            min_s=strtok(duration,":");sec_s=strtok(NULL,":");
	            min=atoi(min_s);sec=atoi(sec_s);
	            sec = min*60 + sec;
	            strcpy(new_song->songName, name);
	            new_song->duration = sec;
	            size++;
	            
	            //	fill the playlist
	            insertChrono(&headChrono, new_song);
	            insertAlpha(&headAlpha, new_song);
	            insertDuration(&headDuration, new_song);
	            
	            break;
		 
			}
         	
         	case 2: // delete an element
         	{
         		int t1,t2,t3;
	         	
	            if(size!=0){ // Check if list is not empty.
	            
	            	puts("Enter a song name:");
	            	scanf(" %[^\n]", &buffer);
	            	
	            	if(!isInPlayList(headChrono, buffer)){ //	check if song exists in the list or not
	            	
	            		puts("\nThe song you entered is not in the playlist!");
	            		break;	
					}
	            		
	            	t1=deleteSong(&headChrono, buffer, 0);
	            	t2=deleteSong(&headAlpha, buffer, 1);
	            	t3=deleteSong(&headDuration, buffer, 2);
	            	
	            	if(t1&t2&t3)
	            		size--; // Decrement the size of list by one.
				}
	            else{
	               puts("List is empty.\n");
	            }	
			}
            

            break;
            
            case 3: // Print part.
				
				//Print the playlist based on given format.
			            	
            	printChrono(headChrono);
				printf("\n");
				printAlpha(headAlpha);
				printf("\n");
				printDuration(headDuration);
				printf("\n");
				printRandom(headChrono, size);
				
				break;
				
			case 4: //Print the songs to the output file part.
				
				puts("Enter a file name(file name should contains .txt extension):");
				scanf(" %[^\n]", &buffer);
				
				f = fopen(buffer, "w");
				
				if (f == NULL){
				    printf("Error opening file!\n");
				    break;
				}
					
            	printChrono_out_file(headChrono, f);
				fprintf(f, "\n");
				printAlpha_out_file(headAlpha, f);
				fprintf(f, "\n");
				printDuration_out_file(headDuration, f);
				fprintf(f, "\n");
				printRandom_out_file(headChrono, f, size);
				
				printf("\n>>>Output is printed to the file %s\n", buffer);
				fclose(f);
				break;
				
         default:
            puts("Invalid choice.\n");
            //instructions();
            break;
      } // end switch
      puts("\n########################\n");
	  instructions();
	  printf("%s", "? ");
	  scanf("%u", &choice);
   }

   puts("End of run.");
   
   return 0;
}

void insertChrono(Song **head, Song *new_song){ // Insert the new songs based on chronological order.
	
	Song *temp = *head;
		// Initially there are no next nodes.
	new_song->alpha_next=NULL;
	new_song->chrono_next=NULL;
	new_song->duration_next=NULL;
	new_song->random_next=NULL;
	
	if(*head == NULL){ // If given list is empty then add the given song to the beginning of the list.
		*head = new_song;
		temp = new_song;
	}
	else{
		while(temp->chrono_next != NULL) // If list is not empty then add the given song to the end of the list.
			temp = temp->chrono_next;
		
		temp->chrono_next = new_song;
	}
}

void insertAlpha(Song **head, Song *new_song){ // Insert new songs in alphabetical order.
	
	Song *current = *head, *prev=NULL;
	int res;
	
	if(*head==NULL)
		*head = new_song;
	
	else{
		while(current!=NULL){
			
			res=strcmp(current->songName, new_song->songName); //Compare and sort their names in alphabetical order. 
			// New song is latter.
			if(res==-1){
				//	If current is head.
				if(current->alpha_next==NULL){
					current->alpha_next=new_song;
					return;
				}
				//	Go further.
				else{
					prev=current;
					current=current->alpha_next;
				}
			}
			//	New song is prior or equal.
			else{
				//	If current is head.
				if(current==*head){
					new_song->alpha_next=current;
					*head=new_song;
					return;
				}
				else{
					
					prev->alpha_next=new_song;
					new_song->alpha_next=current;
					return;
				}
			}
		}
	}
}

void insertDuration(Song **head, Song *new_song){ // Compare and sort their durations in ascending order.
	
	Song *current = *head, *prev=NULL;
	int res;
	
	if(*head==NULL)
		*head = new_song;
	
	else{
		while(current!=NULL){
			
			
			if(new_song->duration > current->duration){ // Compare durations.
			
				if(current->duration_next==NULL){
					current->duration_next=new_song;
					return;
				}
				
				else{
					prev=current;
					current=current->duration_next;
				}
			}
			
			else{
				//	If urrent is head.
				if(current==*head){
					new_song->duration_next=current;
					*head=new_song;
					return;
				}
				else{
					
					prev->duration_next=new_song;
					new_song->duration_next=current;
					return;
				}
			}
		}
	}
}

void printChrono(Song *head){ // Print the song in chronological order.
	
	Song *temp = head;
	int i=1;
	puts("The list in chronological order:\n");
	while(temp != NULL){
		printf("%d.%s\t%d:%d\n", i, temp->songName, (temp->duration)/60, (temp->duration)%60);
		temp = temp->chrono_next;
		i++;
	}
		
}

void printChrono_out_file(Song *head, FILE *file){ // Print the song in chronological order to the output file.
	
	Song *temp = head;
	int i=1;
	fprintf(file, "The list in chronological order:\n");
	while(temp != NULL){
		fprintf(file, "%d.%s\t%d:%d\n", i, temp->songName, (temp->duration)/60, (temp->duration)%60);
		temp = temp->chrono_next;
		i++;
	}
	
}

void printAlpha(Song *head){ // Print the song in alphabetical order.
	
	Song *temp = head;
	int i=1;
	puts("The list in alphabetical order:\n");
	while(temp != NULL){
		printf("%d.%s\t%d:%d\n", i, temp->songName, (temp->duration)/60, (temp->duration)%60);
		temp = temp->alpha_next;
		i++;
	}
}

void printAlpha_out_file(Song *head, FILE *file){ // Print the song in alphabetical order to the output file..
		
	Song *temp = head;
	int i=1;
	fprintf(file, "The list in alphabetical order:\n");
	while(temp != NULL){
		fprintf(file, "%d.%s\t%d:%d\n", i, temp->songName, (temp->duration)/60, (temp->duration)%60);
		temp = temp->alpha_next;
		i++;
	}
}

void printDuration(Song *head){ // Print the song based on durations. The durations sorted ascending order.
	
	Song *temp = head;
	int i=1;
	puts("The list in duration-time order:\n");
	while(temp != NULL){
		printf("%d.%s\t%d:%d\n", i, temp->songName, (temp->duration)/60, (temp->duration)%60);
		temp = temp->duration_next;
		i++;
	}
}

void printDuration_out_file(Song *head, FILE *file){ // Print the song based on durations to the output file.
	
	Song *temp = head;
	int i=1;
	fprintf(file, "The list in duration-time order:\n");
	while(temp != NULL){
		fprintf(file, "%d.%s\t%d:%d\n", i, temp->songName, (temp->duration)/60, (temp->duration)%60);
		temp = temp->duration_next;
		i++;
	}
	
}

void printRandom(Song *head, int size){ // Insert the songs in random order and print the new songs based on random order.
	
	Song *temp=head;
	Song *randomArray=calloc(size, sizeof(Song));
	int i=0;
	
	
	int *array=(int *)malloc(size*sizeof(Song));
	//	get array of indeces
	for(i = 0; i<size; i++)
  		array[i] = i;
	
	array = shuffle(array, size);
	
	i=0;
	while(temp!=NULL){
		strcpy(randomArray[i].songName,temp->songName);
		randomArray[i].duration=temp->duration;
		temp=temp->chrono_next;
		i++;
	}
	puts("The list in random order:\n");
	for(i=0; i<size; i++){
		printf("%d.%s\t%d:%d\n", i+1, randomArray[array[i]].songName, (randomArray[array[i]].duration)/60, (randomArray[array[i]].duration)%60);
	}
	
	//free(temp);
	free(array);
	free(randomArray);
}

void printRandom_out_file(Song *head, FILE *file, int size){ // Insert the songs in random order and print the new songs to the output file based on random order.
	
	Song *temp=head;
	Song *randomArray=calloc(size, sizeof(Song));
	int i=0;
	
	
	int *array=(int *)malloc(size*sizeof(Song));
	//	get array of indeces
	for(i = 0; i<size; i++)
  		array[i] = i;
	
	array = shuffle(array, size);
	
	i=0;
	while(temp!=NULL){
		strcpy(randomArray[i].songName,temp->songName);
		randomArray[i].duration=temp->duration;
		temp=temp->chrono_next;
		i++;
	}
	fprintf(file, "The list in random order:\n");
	for(i=0; i<size; i++){
		fprintf(file, "%d.%s\t%d:%d\n", i+1, randomArray[array[i]].songName, (randomArray[array[i]].duration)/60, (randomArray[array[i]].duration)%60);
	}
	
	free(array);
	free(randomArray);
}

int deleteSong(Song **head, char song[], int del_case){ // Delete the song from the list if it is exist
	
	Song *temp=*head;
	
	switch(del_case){
		
		case 0:
			//	if song to be deleted is head of the list
			if(!strcmp((*head)->songName, song)){
				temp=*head;
				(*head)=(*head)->chrono_next;
				
			}
			else{
				Song *prev = (*head);
		      	Song *current = (*head)->chrono_next;
		
		      	// loop to find the correct location in the list
		      	while (current != NULL && strcmp(current->songName, song)!=0) {
		         	prev = current; // walk to ...
		         	current = current->chrono_next; // ... next node
		      	}
		
		      	// delete node at currentPtr
		      	if (current != NULL) {
		         	temp = current;
		         	prev->chrono_next = current->chrono_next;
		         	
		      	}
			}
		
			break;
		
		case 1:
			//	if song to be deleted is head of the list
			if(!strcmp((*head)->songName, song)){
				temp=(*head);
				(*head)=(*head)->alpha_next;
				
			}
			else{
				Song *prev = (*head);
		      	Song *current = (*head)->alpha_next;
		
		      	// loop to find the correct location in the list
		      	while (current != NULL && strcmp(current->songName, song)!=0) {
		         	prev = current; // walk to ...
		         	current = current->alpha_next; // ... next node
		      	}
		
		      	// delete node at currentPtr
		      	if (current != NULL) {
		         	temp = current;
		         	prev->alpha_next = current->alpha_next;
		         	
		      	}
			}
			
			break;
			
		case 2:
			//	if song to be deleted is head of the list
			if(!strcmp((*head)->songName, song)){
				temp=(*head);
				(*head)=(*head)->duration_next;
				free(temp);
			}
			else{
				Song *prev = (*head);
		      	Song *current = (*head)->duration_next;
		
		      	// loop to find the correct location in the list
		      	while (current != NULL && strcmp(current->songName, song)!=0) {
		         	prev = current; // walk to ...
		         	current = current->duration_next; // ... next node
		      	}
		
		      	// delete node at currentPtr
		      	if (current != NULL) {
		         	temp = current;
		         	prev->duration_next = current->duration_next;
		         	free(temp);
		      	}
			}
			
			break;
			
		default:
			return 0;
		
	}
		
	return 1;	
}

int isInPlayList(Song *head, char songName[]){ // Check whether the song is in the playlist.
	
	Song *temp=head;
	while(temp!=NULL){
		if(!strcmp(temp->songName, songName))
			return 1;
		temp=temp->chrono_next;
	}
	return 0;
}

int *shuffle(int array[], int size){  // Shuffle the array randomly.
	
	int i,j,t;
	
	
	srand(time(NULL));
	
	if (size > 1) {
    	for (i = 0; i < size; i++){
	    	j = i + rand() / (RAND_MAX / (size - i) + 1);	//get arbitrary index of the random array
			t = array[j];	//swap op
			array[j] = array[i];	
			array[i] = t;
        }
    }
    
    return array;
}

void instructions(void){ //Instructions.
   puts("Enter your choice:\n"
      "   1 to insert a song into the list.\n"
      "   2 to delete a song from the list.\n"
      "   3 to print the songs in the list.\n"
	  "   4 to print the songs to an output file.\n"
	  "   5 to end...\n");
}
