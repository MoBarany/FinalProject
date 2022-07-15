#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

/* creating Structure */
typedef struct SimpleDb
{
    U8 ID;
    U8 year;

    U8 course1_ID;
    F32 course1_grade;

    U8 course2_ID;
    F32 course2_grade;

    U8 course3_ID;
    F32 course3_grade;


    struct SimpleDb *link; /*address of next*/
} node;



//prototypes

void SDB_TakeData     (node* head);

bool SDB_IsFull       (void);

U8 SDB_GetUsedSize    (void);

bool SDB_AddEntry     (void);

void SDB_DeleteEntry  (void);

bool SDB_ReadEntry    (void);

void SDB_GetIdList    (void);

bool SDB_IsIdExist    (U8 data);


#endif // INTERFACE_H_INCLUDED
