#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 
WORD FREQUENCY ANALYSIS VERSION 1.0 - David Gorski //
This is a simple program that analyzes a paragraph of text and displays a list of words used, ordered from most frequently to least frequently. 
It also displays the unique word count, and total word count. It parses for words by using spaces and punctuation as breaks (excluding apostraphes), 
and converts uppercase letters into lowercase. It checks whether the word was already seen by checking in a linked list, and if so simply interates the frequency variable. 
If not, then it creates a new node for the word. Finally, it sorts the linked list using a bubble sort algorithm.
*/

/* Introduce Data Struture */
typedef struct node {
int word[30];
int freq;
struct node * next;
} node;

/* Declare Function Prototypes */
void newnode(int phrase[30], node *current);
int check(int phrase[30], node *current);
int display(node *root);
void freenodes(node *root);
node* sort(node *root);

/* Initialize Main function */
void main(void)
{

/* Text Strings to hold User input and Integers to keep count words */
char text[10000];
int words[10000];
int word[30];
int counter = 0;
int uniq = 0;

/* Integer to keep track of location in main text string */
int loc = 0;

/* Integer to keep track of location in word file */
int lloc = 0;

/* Declare Root Node of Structure and make it Null */
node *root = NULL;


/* Declare current to track working position */
node *current = NULL;

/* Print Welcome Statement with instructions, fill text array with zeros and get user input from standard input */
printf("Welcome to Word Frequency Analysis by David Gorski. Ready to check word frequency. Words cannot be longer than 30 characters. Please enter your input (within 10000 characters):\n");
int x;
for(x = 0; x != 9999; x++) text[x] = 0;
fgets(text, 10000, stdin);

/* Declare integer then use loop to convert char array into integer array */ 
for(x = 0; x != 9999; x++) words[x] = text[x];

/* Loop that loads words into new nodes */
while(words[loc] != 10)
{

/* Fill word array with zeroes */
for(x = 0; x != 29; x++) word[x] = 0;

/* Make sure that loc is a letter (Special case for 39 which is an apostraphe) */
while((words[loc] >= 32 && words[loc] <= 38) || (words[loc] >= 40 && words[loc] <= 64) || (words[loc] >= 91 && words[loc] <= 96) || (words[loc] >= 123 && words[loc] <= 126) || (words[loc] <= 127 && words[loc] > 226) || (words[loc] > 226)) loc++;

/* Compatiblity with copying and pasting certain unicode standards */
while(words[loc] == 128 || words[loc] == 153) loc++;

/* If the location variable points to a 10, break the loop */
if(words[loc] == 10) break;

/* Zero lloc counter for word array */
lloc = 0;

/* Integer boolean to check  apostrophe was converted from unicode to asci */
int apo = 0; 

/* Load one word into the word array changing Uppercase characters into lowercase */
while((words[loc] >= 65 && words[loc] <= 90) || (words[loc] >= 97 && words[loc] <= 122)|| words[loc] == 39 || words[loc] == 226 && words[loc] != 10)
	{
	/* If unicode apostraphe is used, convert to asci and switch integer boolean to true */	
	if(words[loc] == 226)
	{
	apo = 1;  
	words[loc] = 39;
	}
	/* Conversion to lower case */	
	if((words[loc] >= 65) && (words[loc] <= 90)) word[lloc] = words[loc] + 32;
	else word[lloc] = words[loc]; 
	lloc++;
	/* Skip unicode artifacts if apostraphe was converted, normally iterate forward by one, also zero the interger boolean */	
	if(words[loc] == 39 && apo == 1) loc = loc + 2;
	loc++;
	apo = 0;
	}

/* Check if word is in linked list, If it is then simply increase the frequency in that node */
if(check(word, root) == 0)
	{
	counter++;
	}

/* If word is not in the linked list then creat a newnode by allocating necessary memory */ 
else
	{	
	/* If root is null then allocate the memory for the first node, and make it root */
	if(root == NULL) 
		{
		current = malloc(sizeof(node));
		root = current;
		}
	/* Otherwise allocate the memory necessary and and iterate current pointer to the next node */
	else
		{
		current -> next = malloc(sizeof(node));	
		current = current -> next;
		}	
	/* Pass current pointer and word array to the new node function */
	newnode(word, current);	
	/* Iterate the word counters */
	counter++;
	uniq++;
	}
}

/* Pass the root pointer to the sort function, return will be the new root pointer */
root = sort(root);

/* Print out a list of all the words in the linked list */
display(root);

/* Free all the memory in the heap consumed by the linked list */
freenodes(root);

/* Print Final Word Counts */
printf("\nUnique Word Count: %i\n", uniq);
printf("Total Word Count: %i \n\n", counter);
}

/* Funtion that creates a new node, loads word into the new node, increases word frequency by one, and sets current pointer to next */
void newnode(int phrase[30], node *current)
{

/* Location tracking integer */
int loc = 0;

/* Insert the word from word array into Node array */
while(phrase[loc] != 0)
	{
	current -> word[loc] = phrase[loc];
	loc++;
	}

/* Set frequency to one */
current -> freq = 1;

}

/* Function that check if the current word is in the linked list */
int check(int phrase[30], node *root)
{
/* Create current node pointer that originally points at the root node */
node *current = root;


/* Check if the root pointer is Null. If so, end the function and return 1 */
if(current == NULL)
{
	return 1;
}

/* While the current pointer is not Null, iterate between the nodes in the linked list */
while(current != NULL)
	{
	int loc = 0;
	/* Repeat a maximum of 30 times. Check if each letter is the same. Every time it is increase loc. If it is not, break the loop */
	while(loc != 30)
		{
		if(current -> word[loc] == phrase[loc]) 
			{
			loc++;
			}	
		else 
			{	
			break;
			}

		}	

/* Check if the current location is 30, if it is then the words match. Increase frequency and return 0 */
	if(loc == 30)
		{
		current -> freq = current -> freq + 1;
		return 0;
		}
	/* Check if there is a next node. If yes, switch the current pointer to it and the loop will repeat */
	else if(current -> next != NULL)
		{
		current = current -> next;		
		}	
	/* Otherwise return 1, signifying that the word is not in the list */
	else
		{
		return 1;
		}
	}	


}

/* Function that prints out on display every word in the linked list and the frequency of use of each */
int display(node *root)
{

/* Make current pointer equal to root */
node *current = root;

/* Display header */
printf("\nFREQUENCY OF WORDS USED //\n\n");

/* If current is equal to Null, root is equal ot null, so there is nothing in the list */
if(current == NULL)
{
	printf("Write something, you doofus!\n");
	return 1;
}


/*Iterate over each node of the data structure as long as the current pointer is not equal to NULL */
while(current != NULL)
	{
	printf("%i : ", current -> freq);	
	int loc = 0;
	while(current -> word[loc] != 0)
		{
		printf("%c", current -> word[loc]);
		loc++; 
		}	
	printf("\n");

	/* Check if there is a next node. If yes, switch the current pointer to it and the loop will repeat */
	if(current -> next != NULL)
		{
		current = current -> next;		
		}	
	/* Otherwise return 1, signifying that the word is not in the list */
	else
		{
		return 1;
		}
	}	

}

/* Function to release all the memory used by the linked list */
void freenodes(node *root)
{

/* Make current pointer equal to root */
node *current = root;

/* while the current function is not equal to null, free the crreut */
while(current != NULL)
	{
	free(current);
	current = current -> next;	
	}

}

/* Function that sorts the linked list in order of frequency using a bubble sort algorithm */
node* sort(node *root)
{

/* Declare pointers that will keep track of nodes*/
node *current = root;
node *temp = NULL;
node *prev = NULL;
node *cons = NULL;

/* If there is only one item in the list, return root pointer */
if(current -> next == NULL) return root;

/* Integer boolean that tracks if a word was swapped */
int swap = 1;

/* Loop that sets the current node to root, and other pointers accordingly. Ends when no words have been swapped */
while(swap != 0)
{
/* Set the boolean to zero swaps */
swap = 0;

/* Set pointers */
current = root;
prev = current;
current = current -> next;
cons = current -> next;
temp = NULL;

/* Loop that continues it is broken by final swap */
while( current != NULL)
{

/* If consective is NULL (meaning last swap) */
if(cons == NULL)
{
	
	/* If previous frequency is greater than current frequency, swap them */		
	if(prev -> freq < current -> freq)
		{
		/* switch swap boolean */
		swap = 1;	
		
		if(temp != NULL) temp -> next = current;				
		current -> next = prev;
		prev -> next = cons;
		/* If prevous is equal to root, don't lose the root node, by making current root */		
		if(prev == root) root = current;
		}
	/* break the loop */
	break;

}


/* If consective is not NULL */
if(cons != NULL)
{
	/* If previous frequency is greater than current frequency, swap them */
	if(prev -> freq < current -> freq)
		{
		/* swtich swap boolean */	
		swap = 1;				
		
		if(temp != NULL) temp -> next = current;				
		current -> next = prev;
		prev -> next = cons;			
		/* If prevous is equal to root, don't lose the root node, by making current root */		
		if(prev == root) root = current;
		
		prev = current;
		current = current -> next;
		}
		
		temp = prev;
		prev = prev -> next;
		current = current -> next;
		cons = cons -> next;
}
}
}
return root; 
}

