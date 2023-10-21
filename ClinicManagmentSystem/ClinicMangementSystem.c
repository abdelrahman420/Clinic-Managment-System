#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClinicMangementSystem.h"

int main(void) 
{
    List L;
    int password;
    printf("Clinic Management System\n");
    printf("PLEASE ENTER PASSWORD : ");
    scanf("%d",&password);
    if (EnterPassword(password) == 1)
    {
        Patient_voidAddRecord(ADMIN,&L,"ABDO",23,MALE,1809267);
        Patient_voidAddRecord(ADMIN,&L,"MARK",27,MALE,190367);
        Patient_voidAddRecord(ADMIN,&L,"MAGY",25,FEMALE,209267);
        Patient_voidAddRecord(USER,&L,"TOQA",32,FEMALE,12267);
        Patient_voidEditRecord(ADMIN,&L,190367);
        Patient_voidEditRecord(USER,&L,190367);
        Patient_voidAddReservation( ADMIN,&L, 1809267, SLOT_3PM_330PM);
        Patient_voidCancelReservation(USER,&L, 190367);
        Patient_voidAddReservation(ADMIN,&L,190367,SLOT_2PM_230PM);
        Patient_voidCancelReservation(ADMIN,&L, 190367);
    }
    Patient_voidViewRecord(&L,190367);
    Patient_voidViewTodaysReservations(&L);

    return 0;
}

int EnterPassword(int Password) 
{
    int Returned_intPassword = 0;  // Initialize to 0
    
    if (Password == 1234)
    {
        Returned_intPassword = 1;  // Allow with correct password
    } else {
        int i = 1;
        while (i < maxAttempts) 
        {
            // Ask for password again
            printf("Password is incorrect. Please try again: ");
            scanf("%d", &Password);
            if (Password == 1234) 
            {
                Returned_intPassword = 1;  // Allow with correct password
                break;
            }
            i++;
        }
    }
  
    
    return Returned_intPassword;
}

int ID_intCheck(List *Patient_Ptr, int ID_Check)
{
    Patient *current = Patient_Ptr->Head;
    
    while (current != NULL)
    {
        if (ID_Check == current->ID)
        {
            return 1;  
        }
        current = current->Next;
    }
    
    return 0;  
}

void List_voidInit(List *Patient_Ptr)
{
    Patient_Ptr->Head = NULL;
}
void Patient_voidAddRecord(MODE_enum Mode,List *Patient_Ptr,char *name,int age,Gender_enum gender,int ID_Enter)
{
    if(Mode == ADMIN)
    {
        if(!ID_intCheck(Patient_Ptr,ID_Enter))
        {
        
            Patient *New_Record = (Patient *)malloc(sizeof(Patient));
            if(New_Record == NULL)
            {
                printf("FAILED TO ADD NODE\n");
            }
            strcpy(New_Record->Name,name);
            New_Record->Age = age;
            New_Record->Gender = gender;   
            New_Record->ID = ID_Enter;
            New_Record->slot = -1;
            New_Record->Next = NULL;

            if(Patient_Ptr->Head == NULL)
            {
                Patient_Ptr->Head = New_Record;
            }
            else
            {
                Patient *current = Patient_Ptr->Head;
                while(current->Next != NULL)
                {
                    current = current->Next;
                }
                current->Next = New_Record;
            }
        }
        else
        {
            printf("ENTRY REJECTED : ID ALREADY EXISTS\n");
        }
    }
    else {printf("YOU CANNOT ADD PATIENT RECORD : YOU ARE IN USER MODE\n");}
}
void Patient_voidEditRecord(MODE_enum Mode,List *Patient_Ptr,int ID_Enter)
{
    if(Mode == ADMIN)
    {
        if(ID_intCheck(Patient_Ptr,ID_Enter))
        {
            Patient *currnt =  Patient_Ptr->Head;
            while(currnt != NULL)
            {
                if(currnt->ID == ID_Enter)
                {
                    printf("**********Editing Patient Information**********\n");
                    printf("Please Enter Desired Name : ");
                    scanf("%s",currnt->Name);
                    printf("Please Enter Desired Age : ");
                    scanf("%d",&(currnt->Age));
                    printf("Please Enter Desired Gender enter 1 for male and 0 for female: ");
                    scanf("%d",&(currnt->Gender));
                    printf("**********Patient Information Updated**********\n");
                    break;
                }
                currnt = currnt->Next;
            }
        }
        else
        {
            printf("ID DOESNOT EXIST !!!\n");
        }
    }
    else {printf("YOU CANNOT EDIT PATIENT RECORD : YOU ARE IN USER MODE\n");}
}
void Patient_DisplayAvailableSlots(void)
{
    printf("Available slots:\n");
    for (int i = 0; i < NUM_SLOTS; i++) 
    {
  
        switch(i)
        {
            case 0:printf("2:00 - 2:30\n");
            break;
            case 1:printf("2:30 - 3:00\n");
            break;
            case 2:printf("3:00 - 3:30\n");
            break;
            case 3:printf("4:00 - 4:30\n");
            break;
            case 4:printf("4:30 - 5:00\n");
            break;
            default:
            break;
        }

    }
}
void Patient_voidAddReservation(MODE_enum Mode,List *Patient_Ptr,int ID_Enter,AvailableSlot Time_Slot)
{
    if(Mode== ADMIN)
    {
        if(ID_intCheck(Patient_Ptr,ID_Enter))
        {
            Patient *current = Patient_Ptr->Head;
            while (current != NULL) 
            {
                if (current->ID == ID_Enter) 
                {
                    if(current->slot != -1)
                    {
                        printf("PATIENT HAVE A RESERVED SLOT\n");
                    }
                    else
                    {
                        current->slot = Time_Slot;
                        printf("RESERVATION ADDED\n");

                    }
                    break;
                }
                current = current->Next;
            }
        }else{printf("Patient Not found");}
    }
    else {printf("YOU CANNOT ADD RESERVATION : YOU ARE IN USER MODE\n");}

}
void Patient_voidCancelReservation(MODE_enum Mode,List *Patient_Ptr,int ID_Enter)
{
    if (Mode == ADMIN)
    {
        if(ID_intCheck(Patient_Ptr,ID_Enter))
        {
            Patient *current = Patient_Ptr->Head;
            while (current != NULL) 
            {
                if (current->ID == ID_Enter) 
                {
                    if(current->slot == -1)
                    {
                        printf("PATIENT DOESNOT HAVE A RESERVED SLOT\n");
                    }
                    else
                    {
                        current->slot = -1;
                        printf("RESERVATION CANCELED\n");
                    }
                    break;
                }
                current = current->Next;
            }
        }else{printf("Patient Not found");}
    }
    else {printf("YOU CANNOT CANCEL RESERVATION : YOU ARE IN USER MODE\n");}
}
void Patient_voidViewRecord(List *Patient_Ptr,int ID_Enter)
{
    Patient *currnt =  Patient_Ptr->Head;
    while(currnt != NULL)
    {
        if(currnt->ID == ID_Enter)
        {
            printf("**********Viewing Patient Information**********\n");
            printf("Patient NAME is : %s\n",currnt->Name);
            printf("Patient ID is : %d\n",currnt->ID);
            printf("Patient AGE is : %d\n",currnt->Age);
            printf("Printing patient GENDER 1 stands for MALE 0 stands for FEMALE : %d\n",currnt->Gender);
            printf("**********Patient Information Viewed**********\n");
            break;
        }
        currnt = currnt->Next;
    }
}
void Patient_voidViewTodaysReservations(List *Patient_Ptr)
{
    printf("Today's Reserved Slots:\n");
    for (int i = 0; i < NUM_SLOTS; i++) 
    {
        Patient *current = Patient_Ptr->Head;
        while (current != NULL) 
        {
            if (current->slot == i) 
            {
                switch(i)
                {
                    case 0:printf("2:00 - 2:30 >>> Patient ID :%d\n",current->ID);
                    break;
                    case 1:printf("2:30 - 3:00 >>> Patient ID :%d\n",current->ID);
                    break;
                    case 2:printf("3:00 - 3:30 >>> Patient ID :%d\n",current->ID);
                    break;
                    case 3:printf("4:00 - 4:30 >>> Patient ID :%d\n",current->ID);
                    break;
                    case 4:printf("4:30 - 5:00 >>> Patient ID :%d\n",current->ID);
                    break;
                    default:
                    break;
                }
            }
            current = current->Next;
        }
    }
}
