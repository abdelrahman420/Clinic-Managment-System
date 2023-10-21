#ifndef CLINICMANAGMENTSYSTEM_H
#define CLINICMANAGMENTSYSTEM_H

#define MAX_LENGTH 50
#define maxAttempts 3


typedef enum
{
    USER,
    ADMIN 
}MODE_enum;

typedef enum 
{
    FEMALE,
    MALE 
}Gender_enum;

typedef enum 
{
    SLOT_2PM_230PM,
    SLOT_230PM_3PM,
    SLOT_3PM_330PM,
    SLOT_4PM_430PM,
    SLOT_430PM_5PM,
    NUM_SLOTS
} AvailableSlot;

typedef struct Node
{
    char Name[MAX_LENGTH];
    int Age;
    Gender_enum Gender;
    int ID;
    int slot;
    struct Node *Next;
}Patient;

typedef struct 
{
    Patient *Head;
}List;

int EnterPassword(int Password); 
int ID_intCheck(List *Patient_Ptr,int ID_Check);
void List_voidInit(List *Patient_Ptr);
void Patient_voidAddRecord(MODE_enum Mode,List *Patient_Ptr,char *name,int age,Gender_enum gender,int ID_Enter);
void Patient_voidEditRecord(MODE_enum Mode,List *Patient_Ptr,int ID_Enter);
void Patient_DisplayAvailableSlots(void);
void Patient_voidAddReservation(MODE_enum Mode,List *Patient_Ptr,int ID_Enter,AvailableSlot Time_Slot);
void Patient_voidCancelReservation(MODE_enum Mode,List *Patient_Ptr,int ID_Enter);
void Patient_voidViewRecord(List *Patient_Ptr,int ID_Enter);
void Patient_voidViewTodaysReservations(List *Patient_Ptr);



#endif