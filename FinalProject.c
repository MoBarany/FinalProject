#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Type_Def.h"
#include "interface.h"

#define ZERO   0
#define ONE    1
#define TWO    2
#define MAX    10


/* assigning global pointer to first element in list */
node* start = NULL;


void main()
{
    static U8 checker = ONE;
    U8 choice  = ONE;

    while (checker == ONE)
    {
        printf("Choose operation:\n");
        printf("1) Add new ID.\n2) Delete specific ID.\n3) Search for ID.\n4) View current IDs list.\n5) Exit program.\n");
        printf("\nChoice: ");
        scanf("%d", &choice);
        printf("=========================\n");

        /* Choice validation */
        while  (choice != 1
                && choice != 2
                && choice != 3
                && choice != 4
                && choice != 5)
        {
            printf("ENTER A VALID CHOICE!\n");
            printf("\nChoice: ");
            scanf("%d", &choice);
            printf("=====================\n");
        }

        switch (choice)
        {

        case 1:
            /* inserting entry */
            SDB_AddEntry();

            printf("\n=============================================");
            printf(" Press any button to continue ");
            printf("=============================================");
            getch();
            break;

        case 2:
            /* Deleting entry */
            SDB_DeleteEntry ();

            printf("\n=============================================");
            printf(" Press any button to continue ");
            printf("=============================================");
            getch();
            break;

        case 3:
            /* Searching for entry */
            SDB_ReadEntry ();

            printf("\n=============================================");
            printf(" Press any button to continue ");
            printf("=============================================");
            getch();
            break;

        case 4:
            /* Prints IDs in list */
            SDB_GetIdList();

            printf("\n=============================================");
            printf(" Press any button to continue ");
            printf("=============================================");
            getch();
            break;

        case 5:
            /* exiting program */
            checker = ZERO;
            break;

        }
    }
    printf("TERMINATED SUCCESSFULLY!");

    getch();
}

//* Taking Data from user *//
void SDB_TakeData (node* head)
{
    printf("Student ID: ");
    scanf("%d", &head->ID);
    printf("Student Year: ");
    scanf("%d", &head->year);

    /* Subjects */
    printf("Course 1 ID: ");
    scanf("%d", &head->course1_ID);
    printf("Course 2 ID: ");
    scanf("%d", &head->course2_ID);
    printf("Course 3 ID: ");
    scanf("%d", &head->course3_ID);

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
            head->course3_grade > 100)
    {
        printf("\nENTER A VALID GRADE!");
        printf("\nCourse 3 Grade: ");
        scanf("%f", &head->course3_grade);
    }
}

//* Printing Data *//
void SDB_PrintData (node* head)
{
    printf("\nStudent Year: %d", head->year);
    printf("\nSubject 1 ID: %d", head->course1_ID);
    printf("\nSubject 2 ID: %d", head->course2_ID);
    printf("\nSubject 3 ID: %d", head->course3_ID);
    printf("\nSubject 1 grade: %f", head->course1_grade);
    printf("\nSubject 2 grade: %f", head->course2_grade);
    printf("\nSubject 3 grade: %f\n", head->course3_grade);
}

//* checking if full list *//
bool SDB_IsFull (void)
{
    node* mover = start;
    U8 counter = ONE;

    /* if list empty */
    if (start == NULL)
    {
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
        return true;
    }

    /* if list not full */
    else
    {
        return false;
    }
}


//* Size of current list *//
U8 SDB_GetUsedSize (void)
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

    printf("\nNumber of entries is: %d\n", counter);
    printf("Number of entries left is: %d\n", MAX-counter);
    return counter;
}


//* Inserting new entry *//
bool SDB_AddEntry (void)
{
    printf("Enter the following data.\n");

    /* inserting beginning */
    if (start == NULL)
    {
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
        printf("\nSUCCESSFULLY ADDED ENTRY!\n");

        /* Number of entries in the database */
        SDB_GetUsedSize();
        return true;
    }

    /*inserting end */
    else
    {
        /* If list is not full */
        if (SDB_IsFull() == false)
        {
            node* temp_2 = (node*)malloc(sizeof(node));
            node* mover = start;

            if (temp_2 == NULL)
            {
                printf("\nUNABLE TO ALLOCATE MEMORY!");
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

            /* Number of entries in the database */
            SDB_GetUsedSize();
            return true;
        }

    }
    /* If there list is full */
    printf("\nCAN NOT ADD MORE ENTRIES, LIST IS FULL!\n");
    return false;
}


//* deleting by key *//
void SDB_DeleteEntry (void)
{
    node* temp;
    node* ptr;
    U8 data;

    /* List is empty */
    if(start == NULL)
    {
        printf("NOTHING TO DELETE, LIST IS EMPTY!\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%d", &data);

    /* Case delete the first Node at the List */
    if(start->ID == data)
    {
        temp  = start;
        start = start->link;
        free(temp);
        temp = NULL;

        printf("\nDELETED SUCCESSFULLY!\n");

        /* Prints IDs in list */
        SDB_GetIdList();
        return;
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

    /*if ID is not found */
    if(ptr->link == NULL)
    {
        printf("\nID (%d) IS NOT FOUND!", data);
    }

    else
    {
        ptr->link = temp->link;
        free(temp);
        ptr = NULL;

        printf("DELETED SUCCESSFULLY!\n");

        /* Prints IDs in list */
        SDB_GetIdList();
    }
    return;
}


//* Finds an ID *//
bool SDB_ReadEntry(void)
{
    static node* mover = NULL;
    mover = start;
    U8 data;

    /* if list empty */
    if(start == NULL)
    {
        printf("ADD SOMETHING, LIST IS EMPTY!\n");
        return false;
    }

    printf("Enter ID to search: ");
    scanf("%d", &data);

    /* checking existence of ID */
    if (SDB_IsIdExist (data))
    {
        /* if found */
        printf("\nID WAS FOUND!\n");
        printf("\nID details:");

        /*print contents of id */
        SDB_PrintData (mover);
        return true;
    }

    /* If not found */
    printf("\nID WAS NOT FOUND!\n");
    return false;
}


//* Prints IDs in the list *//
void SDB_GetIdList (void)
{
    node* mover = start;
    U8 counter  = ONE;

    /* if list empty */
    if(start == NULL)
    {
        printf("\nLIST IS EMPTY!\n");
        return;
    }

    printf("\nCurrent IDs List is:\n");

    while (mover != NULL)
    {
        printf("%d) %d\n", counter, mover->ID);
        counter++;
        mover = mover->link;
    }
}


//* checks if ID exists *//
bool SDB_IsIdExist (U8 data)
{
    node* mover = start;

    while (mover != NULL)
    {
        if(mover->ID == data)
        {
            return true; /* exists */
        }
        mover = mover->link;
    }

    return false; /* not exist */
}