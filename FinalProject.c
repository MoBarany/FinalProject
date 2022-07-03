#include <stdio.h>
#include <stdlib.h>
#include "Type_Def.h"

//creating Structure
typedef struct SimpleDb
{
    U16 ID;
	U16 year;

	U16 course1_ID;
	F32 course1_grade;

	U16 course2_ID;
	F32 course2_grade;

	U16 course3_ID;
	F32 course3_grade;

    struct SimpleDb *link; //address of next.

}node;

node* CreatSDB (U16 entries);

int main()
{
	U16 entries;
	
	node* start = NULL;

	//Taking in number of nodes in list.
	printf("Enter number of entries: ");
	scanf("%hu", &entries);

	//making sure user enters a length > 0.
	while(entries == 0)
    {
        printf("\nPLEASE ENTER A VALID NUMBER OF ENTRIES!");
        printf("Enter number of entries: ");
        scanf("%hu", &entries);
    }

	//creating list.
	CreatSDB (entries);
	return 0;
}


node* CreatSDB (U16 entries)
{
    U8 counter = 0;

    //Pointer of structure carries address of first node in LL.
    node* start = NULL;

    //temporary pointer to structure to make more nodes.
    node* temp;

    //creating first node.
    node* head = (node*)malloc(sizeof(node));


    //terminate if no memory was reserved
    if(head == NULL)
    {
        printf("\nUNABLE TO ALLOCATE MEMORY!\n");
        exit(0);
    }

    //input data from user.
    printf("\nStudent ID: ");
    scanf("%hu", &head->ID);

	printf("Student Year: ");
	scanf("%hu", &head->year);

	printf("Course 1 ID: ");
	scanf("%hu", &head->course1_ID);

	printf("Course 1 Grade: ");
	scanf("%f", &head->course1_grade);

	printf("Course 2 ID: ");
	scanf("%hu", &head->course2_ID);

	printf("Course 2 Grade: ");
	scanf("%f", &head->course2_grade);

	printf("Course 3 ID: ");
	scanf("%hu", &head->course3_ID);

	printf("Course 3 Grade: ");
	scanf("%f", &head->course3_grade);


    //making start pointer contain address of first node.
    start = head;

    //making pointer of first node points to NULL. i.e is the last node in the list.
    head->link = NULL;

    //creating n-1 numbers of nodes as read from user using temp.
    //for loop will start from 2nd node because we already made 1st one.
    for (counter = 2; counter <= entries; ++counter)
    {
        //creating new node
        temp = (node*)malloc(sizeof(node));

        //make sure new node is allocated in memory
        if (temp == NULL)
        {
            printf("\nUnable to allocate memory");
            break;
        }

       //input data from user.
        printf("\nStudent ID: ");
        scanf("%hu", &head->ID);

        printf("Student Year: ");
        scanf("%hu", &head->year);

        printf("Course 1 ID: ");
        scanf("%hu", &head->course1_ID);

        printf("Course 1 Grade: ");
        scanf("%f", &head->course1_grade);

        printf("Course 2 ID: ");
        scanf("%hu", &head->course2_ID);

        printf("Course 2 Grade: ");
        scanf("%f", &head->course2_grade);

        printf("Course 3 ID: ");
        scanf("%hu", &head->course3_ID);

        printf("Course 3 Grade: ");
        scanf("%f", &head->course3_grade);


        //making new node point to NULL.
        temp->link = NULL;

        //linking old node to new node.
        head->link = temp;

        //moving head naming from old node to current node.
        head = head->link;
        //head = temp;
    }
    //to prevent volatile action when scope ends and keep address saved in start.
    return start;
}

//input data from user.
void DataEntery(void)
{
 printf("\nStudent ID: ");
 scanf("%hu", &head->ID);

 printf("Student Year: ");	
 scanf("%hu", &head->year);

 printf("Course 1 ID: ");
 scanf("%hu", &head->course1_ID);

 printf("Course 1 Grade: ");
 scanf("%f", &head->course1_grade);

 printf("Course 2 ID: ");
 scanf("%hu", &head->course2_ID);

 printf("Course 2 Grade: ");
 scanf("%f", &head->course2_grade);

 printf("Course 3 ID: ");
 scanf("%hu", &head->course3_ID);

 printf("Course 3 Grade: ");
 scanf("%f", &head->course3_grade);
}