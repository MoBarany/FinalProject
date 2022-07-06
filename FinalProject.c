#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Type_Def.h"

#define ZERO 0
#define ONE  1
#define TWO  2
#define MAX  10

/* creating Structure */
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

    struct SimpleDb *link; /*address of next*/
} node;

//prototypes
node* CreatSDB (node* start);
void SDB_TakeData(node* head);
bool SDB_IsFull (node* start);
U8 SDB_GetUsedSize (node* start);
bool SDB_AddEntry (node* start, U8 counter);
node* SDB_DeleteEntry (node* start);
bool SDB_ReadEntry (node* start);
void SDB_GetIdList (node* start);
bool SDB_IsIdExist (U16 data, node* start);

int main()
{
    node* start = NULL;
    U8 counter =  ZERO;

    /* creating list & saving pointer of first item in start */
    start = CreatSDB (start);

    /* list is full or not */
    SDB_IsFull (start);

    /* Number of entries in the database */
    counter = SDB_GetUsedSize (start);

    /* Inserting nodes */
    SDB_AddEntry (start, counter);

    /* Deleting entry */
    start = SDB_DeleteEntry (start);

    /* Searching for entry */
    SDB_ReadEntry (start);

    /* Prints IDs in the list */
    SDB_GetIdList (start);
    return false;
}

//* Creat list *//
node* CreatSDB (node* start)
{
    U16 entries;
    U8 counter = ZERO;
    node* temp;

    printf("Enter number of entries: ");
    scanf("%hu", &entries);

    /* making sure user enters a number > zero */
    while(entries == ZERO)
    {
        printf("\nPLEASE ENTER A VALID NUMBER OF ENTRIES!\n");
        printf("Enter number of entries: ");
        scanf("%hu", &entries);
    }

    /* first node */
    node* head = (node*)malloc(sizeof(node));

    /* if no memory was reserved */
    if(head == NULL)
    {
        printf("\nUNABLE TO ALLOCATE MEMORY!\n");
        exit(false);
    }

    /* taking in data */
    SDB_TakeData(head);

    start = head;
    head->link = NULL;

    /* creating n-1 numbers of nodes as read from user using temp.
    for loop will start from 2nd node because we already made 1st ONE.*/
    for (counter = TWO; counter <= entries; ++counter)
    {
        /* new node */
        temp = (node*)malloc(sizeof(node));

        /* list is empty */
        if (temp == NULL)
        {
            printf("\nUnable to allocate memory");
            break;
        }
        /* Take Data */
        SDB_TakeData(temp);

        temp->link = NULL;
        head->link = temp;
        head = head->link;
    }
    return start;
}

/** there's a problem in float %f**/
//* Taking Data from user *//
void SDB_TakeData (node* head)
{
    printf("\nStudent ID: ");
    scanf("%hu", &head->ID);
    printf("Student Year: ");
    scanf("%hu", &head->year);

    /* Subjects */
    printf("Course 1 ID: ");
    scanf("%hu", &head->course1_ID);
    printf("Course 2 ID: ");
    scanf("%hu", &head->course2_ID);
    printf("Course 3 ID: ");
    scanf("%hu", &head->course3_ID);

    /* Grades */
    printf("Course 1 Grade: ");
    scanf("%f", &head->course1_grade);
    while (head->course1_grade < 0 ||
            head->course1_grade > 100)
    {
        printf("\nENTER A VALID GRADE!");
        printf("\nCourse 1 Grade: ");
        scanf("%f", &head->course1_grade);
    }

    printf("Course 2 Grade: ");
    scanf("%f", &head->course2_grade);
    while (head->course2_grade < 0 ||
            head->course2_grade > 100)
    {
        printf("\nENTER A VALID GRADE!");
        printf("\nCourse 2 Grade: ");
        scanf("%f", &head->course2_grade);
    }

    printf("Course 3 Grade: ");
    scanf("%f", &head->course3_grade);
    while (head->course3_grade < 0 ||
            head->course2_grade > 100)
    {
        printf("\nENTER A VALID GRADE!");
        printf("\nCourse 3 Grade: ");
        scanf("%f", &head->course3_grade);
    }
}

//* Printing Data *//
void SDB_PrintData (node* head)
{
    printf("\nStudent Year: %hu", head->year);
    printf("\nSubject 1 ID: %hu", head->course1_ID);
    printf("\nSubject 2 ID: %hu", head->course2_ID);
    printf("\nSubject 3 ID: %hu", head->course3_ID);
    printf("\nSubject 1 grade: %f", head->course1_grade);
    printf("\nSubject 2 grade: %f", head->course2_grade);
    printf("\nSubject 3 grade: %f\n", head->course3_grade);
}

//* checking if full list *//
bool SDB_IsFull (node* start)
{
    node* mover = start;
    U8 counter = ONE;

    /* returning false in case empty list */
    if (mover == NULL)
    {
        printf("\n\nLIST IS EMPTY!\n");
        return false;
    }

    /* counting number of entries */
    while (mover->link != NULL)
    {
        mover = mover->link;
        counter ++;
    }

    /* if list is full */
    if (counter == MAX)
    {
        printf("\n\nLIST IS FULL!\n");
        return true;
    }

    /* if list not full */
    else
    {
        printf("\n\nLIST IS NOT FULL!");
        return false;
    }
}


//* Size of current list *//
U8 SDB_GetUsedSize (node* start)
{
    U8 counter = ONE;
    node* mover = start;

    if (mover == NULL)
    {
        printf("\nLIST IS EMPTY!");
        return false;
    }

    while (mover->link != NULL)
    {
        mover = mover->link;
        counter ++;
    }

    printf("\nCurrent number of entries in the data base is: %d\n", counter);
    printf("Number of entries left is: %d\n", MAX-counter);
    return counter;
}


//* Inserting new entry *//
bool SDB_AddEntry (node* start, U8 counter)
{
    U8 choice = ZERO;

    /* checking if there's a free space */
    if (counter != MAX)
    {
        printf("\nDo you want to add a new entry (1/0) ?: ");
        scanf("%d", &choice);

        /* user enters valid choice */
        while (choice != ONE && choice != ZERO)
        {
            printf("\nPLEASE ENTER A VALID CHOICE!");
            printf("\nDo you want to add a new entry (1/0) ?: ");
            scanf("%d", &choice);
        }

        if (choice == ONE)
        {
            node* temp_2 = (node*)malloc(sizeof(node));
            node* mover = start;

            if (temp_2 == NULL)
            {
                printf("\nUnable to allocate memory.");
                return false;
            }

            /* last node */
            temp_2->link = NULL;

            /* taking in Data from user */
            SDB_TakeData(temp_2);

            /* will loop until finding last node whose link points to NULL value */
            while (mover->link != NULL)
            {
                /* jump to next node */
                mover = mover->link;
            }

            /* reassigning link of last node the new last node inserted */
            mover->link = temp_2;
            printf("\nSUCCESSFULLY ADDED ENTRY!\n");

            /* Prints new list */
            SDB_GetIdList(start);
        }
    }
    return true;
}


//* deleting by key *//
node* SDB_DeleteEntry (node* start)
{
    node* temp;
    node* ptr;
    U16 data;
    U8 choice = ZERO;

    printf("\nDelete specific ID (1/0) ?: ");
    scanf("%d", &choice);

    while (choice != ONE && choice != ZERO)
    {
        printf("\nPLEASE ENTER A VALID CHOICE!");
        printf("\nDelete specific ID (1/0) ?: ");
        scanf("%d", &choice);
    }

    if (choice == ONE)
    {
        printf("\nEnter ID to delete: ");
        scanf("%d", &data);

        /* List is empty */
        if(start == NULL)
        {
            printf("List is empty \n");
            return start;
        }

        /* Case delete the first Node at the List */
        if(start->ID == data)
        {
            temp  = start;
            start = start->link;
            free(temp);
            temp = NULL;
            printf("DELETED SUCCESSFULLY!\n");
            /* print new ID list */
            SDB_GetIdList(start);
            return start;
        }

        /* Case delete in between the Nodes or at the end */
        ptr = start;
        while(ptr->link != NULL)
        {
            if(ptr->link->ID == data)
            {
                temp = ptr->link;
                break;
            }

            ptr = ptr->link;
        }

        if(ptr->link == NULL)
        {
            printf("\nID (%d) is not in the found", data);
        }

        else
        {
            ptr->link = temp->link;
            free(temp);
            ptr = NULL;
            printf("DELETED SUCCESSFULLY!\n");
            /* print new ID list */
            SDB_GetIdList(start);
        }
    }
    return start;
}


//* Finds an ID *//
bool SDB_ReadEntry(node* start)
{
    static node* mover = NULL;
    mover = start;
    U8 choice = ZERO;
    U8 data;

    printf("\nSearch for a specific ID (1/0) ?: ");
    scanf("%d", &choice);

    while (choice != ONE && choice != ZERO)
    {
        printf("\nPLEASE ENTER A VALID CHOICE!");
        printf("\nSearch for a specific ID (1/0) ?: ");
        scanf("%d", &choice);
    }

    if (choice == ONE)
    {
        printf("Enter ID to search: ");
        scanf("%d", &data);

        while (mover != NULL)
        {
            /* checking existence of ID */
            if (SDB_IsIdExist (data, mover))
            {
                /* if found */
                printf("\nID WAS FOUND!\n");
                printf("\nID details:");
                SDB_PrintData (mover);
                return true;
            }
            mover = mover->link;
        }
        /* If not found */
        printf("\nID WAS NOT FOUND!\n");
        return false;
    }
    return false;
}


//* Prints IDs in the list *//
void SDB_GetIdList (node* start)
{
    node* mover = NULL;
    mover = start;
    U8 counter = ONE;

    printf("\nCurrent IDs List is:\n");

    while (mover != NULL)
    {
        printf("%d) %hu\n", counter, mover->ID);
        counter++;
        mover = mover->link;
    }
}


//* checks if ID exists *//
bool SDB_IsIdExist (U16 data, node* mover)
{

    if(mover->ID == data)
    {
        return true; /* exists */
    }
    return false;
}