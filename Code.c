/*
Done By: Saif Al-Deen Shakoor Battah.
Sec#: 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//Define Passenger & Bus Linked Lists and Pointers

typedef struct Pass_Node *Pass_ptr;
typedef Pass_ptr Pass_List;
typedef struct Bus_Node *Bus_ptr;
typedef Bus_ptr Bus_List;

//Define Passenger node as initialization of the creation of passenger linked list

struct Pass_Node
{
    int Pass_ID;
    int Pass_Date;
    char Pass_Time[30];
    char Pass_From[30];
    char Pass_To[30];
    Bus_ptr AddedBus;
    Pass_ptr nextPass;
};

//Define Bus node as initialization of the creation of Buses linked list

struct Bus_Node
{
    int Bus_Number;
    int Bus_Date;
    char Bus_Time[30];
    char Bus_From[30];
    char Bus_To[30];
    int Price;
    int Capacity;
    Pass_ptr FirstPass; //first passenger in the bus
    Bus_ptr nextBus;
};

//Prototype of some functions
Pass_ptr FindPreviousPass(Pass_List PL, int ID);
Pass_ptr Delete_Pass(Pass_List PL, int ID, int x);
Bus_ptr Delete_Bus(Bus_List BL, int Bus_No);
Bus_ptr FindPreviousBus(Bus_List BL, int Bus_No);
Bus_ptr Scaning(Bus_List BL, int Number);

int main()
{
    // Creation of Bus List
    Bus_List BL;
    BL = (Bus_List)malloc(sizeof(struct Bus_Node));
    BL->nextBus = NULL;
    //---------------------
    // Creation of Passengers List
    Pass_List PL;
    PL = (Pass_List)malloc(sizeof(struct Pass_Node));
    PL->nextPass = NULL;
    //---------------------
    // Creation of a temp list to store matched passengers together for a while
    Pass_List MatchedList;
    MatchedList=(Pass_List)malloc(sizeof(struct Pass_Node));
    MatchedList->nextPass = NULL;
    //---------------------
    // Creation of list to store unmatched passengers.
    Pass_List UnmatchedList;
    UnmatchedList = (Pass_List)malloc(sizeof(struct Pass_Node));
    UnmatchedList->nextPass = NULL;
    //---------------------
    int Choice;
    int Firsty=0;
    int Secondy=0;
    // temp list's used to assign passengers to their correct buses
    Bus_ptr temp_bus_search;
    temp_bus_search = (Bus_ptr)malloc(sizeof(struct Bus_Node));

    Pass_ptr temp_pass_search;
    temp_pass_search = (Pass_ptr)malloc(sizeof(struct Pass_Node));

    Pass_ptr Update_Pass_List;
    Update_Pass_List = (Pass_ptr)malloc(sizeof(struct Pass_Node));

    Pass_ptr um_pass;
    um_pass = (Pass_ptr)malloc(sizeof(struct Pass_Node));

    Pass_ptr m_pass;
    m_pass = (Pass_ptr)malloc(sizeof(struct Pass_Node));

    Bus_ptr m_bus;
    m_bus = (Bus_ptr)malloc(sizeof(struct Bus_Node));

    // list used to store passengers in a deleted bus to append to the unmatched list
    Bus_ptr Temp_UM;
    Temp_UM = (Bus_ptr)malloc(sizeof(struct Bus_Node));

    char str1[30];
    char str2[30];
    int counts;
    int ID;
    int Date;
    char Time[30];
    char From[30];
    char To[30];
    int Update = 0;
    printf("Menu\n\n1. Load the bus information file.\n2. Load the passenger information file.\n3. Assign passengers and print assignment information of all busses.\n4. Print a specific bus information along with its passengers information (names and IDs).\n5. Print unmatched passengers.\n6. Add new passenger.\n7. Delete passenger.\n8. Delete bus number.\n9. Exit.\n");
    printf("\nEnter choice: ");
    scanf("%d",&Choice);

    while(Choice!= 9 )
        {
            if(Choice == 1)
                {
                    Load_Bus_List(BL); //Loading bus information from bus file and creating a bus list
                    Firsty++;
                }

            else if(Choice == 2)
                {
                    Load_Pass_List(PL); //Loading passenger information from passenger file and creating a passenger list
                    Secondy++;
                }

            else if(Choice == 3)
                {
                    if(Firsty == 0 && Secondy == 0)
                        {
                            printf("\nPlease Load Bus & Passengers List!\n\n"); //Error message if not bus list neither passenger list are loaded
                        }

                    else if(Firsty > 0 && Secondy == 0)
                        {
                            printf("\nPlease Load Passengers List!\n\n"); //Error message if passenger list only not loaded
                        }

                    else if(Firsty == 0 && Secondy >0)
                        {
                            printf("\nPlease Load Bus List\n\n"); //Error message if bus list only not loaded
                        }

                    else //If both lists are loaded then go to assign process
                        {

                            if(!isEmptyBus(BL) && !isEmptyPass(PL))
                                { // check if linked lists are empty or not !
                                    if(Update == 1) // if any deleting process occur get in here
                                        {
                                            Clear_List(BL); // clear bus list
                                            PL = Update_Pass_List; // clear passenger list
                                        }

                                    temp_pass_search = PL; // define Bus Linked list as temp LL for searching purpose

                                    while(temp_pass_search->nextPass != NULL)
                                        { // node by node until reaching last node
                                            temp_bus_search = BL; // define Passengers Linked list as temp LL for searching purpose
                                            counts = 0;

                                            while(temp_bus_search->nextBus != NULL)
                                                { // node by node until reaching last node
                                                    //Matching Search!
                                                        strcpy(str1,temp_bus_search->nextBus->Bus_Time);
                                                        strcpy(str2,temp_pass_search->nextPass->Pass_Time);

                                                    if(temp_bus_search->nextBus->Bus_Date == temp_pass_search->nextPass->Pass_Date && !strcmp(str1,str2))
                                                        {
                                                            ///printf("\nMatch Found!\n------------\n\nBus Date = %d  Passenger Date = %d |",temp_bus_search->nextBus->Bus_Date,temp_pass_search->nextPass->Pass_Date);
                                                            ///printf(" Bus Time = %s  Passenger Time = %s\n\n------------\n",temp_bus_search->nextBus->Bus_Time,temp_pass_search->nextPass->Pass_Time);

                                                            // initialize passenger information

                                                            ID = temp_pass_search->nextPass->Pass_ID;
                                                            Date = temp_pass_search->nextPass->Pass_Date;
                                                            strcpy(Time,temp_pass_search->nextPass->Pass_Time);
                                                            strcpy(From,temp_pass_search->nextPass->Pass_From);
                                                            strcpy(To,temp_pass_search->nextPass->Pass_To);
                                                            counts++;
                                                            break;
                                                        }

                                                    else
                                                        {
                                                            temp_bus_search = temp_bus_search->nextBus;
                                                        }
                                                    //End of Matching search!
                                                }

                                                if(counts>0) // Add passenger to matching bus
                                                    {
                                                        m_pass = temp_pass_search->nextPass;
                                                        m_bus = temp_bus_search->nextBus;
                                                        ///printf("\n=============================Start\n");
                                                        ///printf("\nMatched Passenger!\nPassenger Added to Bus %d\n",m_bus->Bus_Number);
                                                        ///printf("\nID=%d\nDate=%d\nTime=%s\nFrom=%s\nTo=%s\n",m_pass->Pass_ID,m_pass->Pass_Date,m_pass->Pass_Time,m_pass->Pass_From,m_pass->Pass_To);
                                                        MatchedList->nextPass = m_bus;
                                                        Add_Pass(&MatchedList,m_pass->Pass_ID,m_pass->Pass_Date,m_pass->Pass_Time,m_pass->Pass_From,m_pass->Pass_To);
                                                        ///printf("\n=============================End\n\n");
                                                    }

                                                else
                                                    { // add passenger to unmatching list
                                                        um_pass = temp_pass_search->nextPass;
                                                        ///printf("\n=============================Start\n");
                                                        ///printf("\nUnmatched Passenger!\nPassenger Added to Unmatched List!!\n");
                                                        ///printf("\nID=%d\nDate=%d\nTime=%s\nFrom=%s\nTo=%s\n",um_pass->Pass_ID,um_pass->Pass_Date,um_pass->Pass_Time,um_pass->Pass_From,um_pass->Pass_To);
                                                        Add_Pass(&UnmatchedList,um_pass->Pass_ID,um_pass->Pass_Date,um_pass->Pass_Time,um_pass->Pass_From,um_pass->Pass_To);
                                                        ///printf("\n=============================Start\n");
                                                    }

                                            temp_pass_search = temp_pass_search->nextPass; // go to next bus node to search within it
                                        }
                                }

                            else
                                {
                                    printf("Link List is Empty!!!");
                                }

                            Printing(BL); //Print each bus information with its passenger information
                            printf("Assigning Completed Successfully!\n\n");
                        }
                }

            else if(Choice == 4)
                {
                    int Bus_No;
                    printf("\nEnter Bus Number To Search For:\n");
                    scanf("%d",&Bus_No);
                    Searching(BL,Bus_No); // a function to search for the bus selected
                }

            else if(Choice == 5)
                {
                    if(UnmatchedList->nextPass != NULL)
                        {
                            printf("\nUnmatched Passenger List:\n-------------------------\n\n");
                            Print_Pass_List(UnmatchedList); //print unmatched passengers list
                            printf("\n");
                        }

                    else
                        {
                            printf("\nTheres No Unmatched Passengers!\n\n"); //if theres no passenger in the unmatched list
                        }
                }

            else if(Choice == 6)
            {
                //ask user to enter new passenger information
                printf("\nAdding New Passenger!\n---------------------\n\n");
                printf("ID = ");
                scanf("%d",&ID);
                printf("\nDate(In Form of DayMonthYear Ex: 15072022) = ");
                scanf("%d",&Date);
                printf("\nTime((In Form of Hour:Minute Ex: 16:30)) = ");
                scanf("%s",&Time);
                printf("\nFrom = ");
                scanf("%s",&From);
                printf("\nTo = ");
                scanf("%s",&To);
                printf("\n");
                //create passenger node and add it to the passenger list
                Add_Pass(&PL,ID,Date,Time,From,To);
                //print the passenger list after adding
                Print_Pass_List(PL);
            }

            else if(Choice == 7)
                {
                    if(PL->nextPass != NULL)
                        {
                            //ask user to enter passenger id to search if exist then delete it
                            printf("\n");
                            Print_Pass_List(PL);
                            int ID;
                            printf("\n\nEnter Passenger ID to Delete:\n");
                            scanf("%d",&ID);
                            PL = Delete_Pass(PL,ID,1); // 1 used to whole passenger list , so we get a error message if passenger doesn't exist or list is empty
                            printf("\n");
                            Print_Pass_List(PL);
                            UnmatchedList = Delete_Pass(UnmatchedList,ID,0); // delete passenger from unmatched list if exist, 0 is used to skip the not found or null list error message
                            Update = 1;
                            Update_Pass_List = PL; //load passenger list to temporary list for assign process
                            printf("\n");
                        }

                    else
                        {//if the list is null
                            printf("\nNo Passengers To remove!\n");
                        }
                }

            else if(Choice == 8)
                {
                    if(BL->nextBus != NULL)
                        {
                            //ask user to enter bus number to search for it and delete it
                            printf("\n");
                            Print_Bus_List(BL);
                            int Bus_No;
                            printf("\nEnter Bus Number To Delete\n");
                            scanf("%d",&Bus_No);
                            Temp_UM = Scaning(BL,Bus_No);

                            if(Temp_UM != NULL && Temp_UM->FirstPass != NULL)
                                {//if bus already deleted , append its passenger to unmatched list
                                    Add_To_Unmatch(UnmatchedList,Temp_UM);
                                }

                            BL = Delete_Bus(BL,Bus_No);
                            printf("\n");
                            Print_Bus_List(BL);
                            printf("\n");

                        }

                    else//if bus list is empty
                        {
                            printf("\nNo Buses To Remove!\n");
                        }
                }

            else
                {//Error message if user enter a wrong input
                    printf("\nPlease Enter a number from 1 to 9!\n");
                }

            printf("\n\nMenu\n\n1. Load the bus information file.\n2. Load the passenger information file.\n3. Assign passengers and print assignment information of all busses.\n4. Print a specific bus information along with its passengers information (names and IDs).\n5. Print unmatched passengers.\n6. Add new passenger.\n7. Delete passenger.\n8. Delete bus number.\n9. Exit.\n");
            printf("\nEnter choice: ");
            scanf("%d",&Choice);
        }

    if(Choice == 9)
        {//Exit statement
            printf("\nBye\n");
        }

    return 0;
}

void Load_Bus_List(Bus_List BL)
{
    FILE *Bus_File;
    char str[100];
    char line[100];
    char *split;
    //Bus inputs
    int Bus_Number;
    int Bus_Date;
    char Bus_Time[30];
    char Bus_From[30];
    char Bus_To[30];
    int Price;
    int Capacity;
    Bus_File = fopen("busses.txt","r");
    //statement to check if file exist or not
    if(Bus_File == NULL)
        {
            printf("\nFile Doesn't Exists\n\n");
        }

    else
        {
            printf("\nFile Successfully Opened!\n\n");
            //read line by line from file
            while(fgets(str,sizeof(str),Bus_File) != NULL)
                {
                    strcpy(line,str);
                    split = strtok(line,"#");
                    Bus_Number = atoi(split);
                    split = strtok(NULL,"#");
                    Bus_Date = atoi(split);
                    split = strtok(NULL,"#");
                    strcpy(Bus_Time, split);
                    split = strtok(NULL,"#");
                    strcpy(Bus_From,split);
                    split = strtok(NULL,"#");
                    strcpy(Bus_To,split);
                    split = strtok(NULL,"#");
                    Price = atoi(split);
                    split = strtok(NULL,"#");
                    Capacity = atoi(split);
                    //create new node of the information read form file and add node to list
                    Add_Bus(&BL,Bus_Number,Bus_Date,Bus_Time,Bus_From,Bus_To,Price,Capacity);
                }
        //end of reading
        }

    fclose(Bus_File);
    Print_Bus_List(BL);
    printf("\n====================================\nBus Information Loaded Successfully!\n====================================\n\n");
}

void Add_Bus(Bus_List *head_bus, int Number, int Date, char  Time[], char From[], char To[], int price, int capacity)
{
    //statement to check if bus already exist or not in the list
    if(Search_Bus(*head_bus,Number) == 0)
        {//if new bus
            Bus_ptr newBusNode = (Bus_ptr)malloc(sizeof(struct Bus_Node));
            newBusNode->FirstPass = NULL;
            Bus_ptr last = *head_bus;
            newBusNode->Bus_Number = Number;
            newBusNode->Bus_Date = Date;
            strcpy(newBusNode->Bus_Time, Time);
            strcpy(newBusNode->Bus_From,From);
            strcpy(newBusNode->Bus_To,To);
            newBusNode->Price = price;
            newBusNode->Capacity = capacity;
            newBusNode->nextBus = NULL;

            if(*head_bus == NULL)
                {
                    *head_bus = newBusNode;
                    return;
                }

            while(last->nextBus != NULL)
                {
                    last = last->nextBus;
                }

            last->nextBus=newBusNode;
            return;
        }

    else
        {//if bus already exist
            printf("\nBus Already Exist!\n\n");
        }
}

void Print_Bus_List(Bus_List BL)
{
    //statement to check if bus list empty or not
    if(!isEmptyBus(BL))
        {//if list not NULL
            Bus_ptr temp_bus = BL->nextBus;

            while(temp_bus != NULL)
                {//while loop to print bus by bus
                    printf("| %d | %d | %s | %s | %s | %d | %d\n",temp_bus->Bus_Number,temp_bus->Bus_Date,temp_bus->Bus_Time,temp_bus->Bus_From,temp_bus->Bus_To,temp_bus->Price,temp_bus->Capacity);
                    temp_bus = temp_bus->nextBus;

                    if(temp_bus != NULL)
                        {
                            printf("------>");
                        }
                }
        }

    else
        {//if list is null
            printf("\nEmpty Linked List!\n");
        }
}

int isEmptyBus(Bus_List BL)
{//function to check if bus list is empty or not
    if(BL == NULL)
        {
            return 1; // null bus
        }

    else
        {
            return BL->nextBus == NULL; // return next node position
        }
}

void Load_Pass_List(Pass_List PL)
{
    FILE *Pass_File;
    char str[100];
    char line[100];
    char *split;
    //Passenger inputs
    int Pass_ID;
    int Pass_Date;
    char Pass_Time[30];
    char Pass_From[30];
    char Pass_To[30];
    Pass_File = fopen("passengers.txt","r");
    //statement to check if passenger file exist or not
    if(Pass_File == NULL)
        {
            printf("\nFile Doesn't Exists\n\n");
        }

    else
        {
            printf("\nFile Successfully Opened!\n\n");
            //read line by line from file
            while(fgets(str,sizeof(str),Pass_File) != NULL)
                {
                    strcpy(line,str);
                    split = strtok(line,"#");
                    Pass_ID = atoi(split);
                    split = strtok(NULL,"#");
                    Pass_Date = atoi(split);
                    split = strtok(NULL,"#");
                    strcpy(Pass_Time, split);
                    split = strtok(NULL,"#");
                    strcpy(Pass_From,split);
                    split = strtok(NULL,"#");
                    strcpy(Pass_To,split);
                    //create node of read information from passenger file and add node to passenger list
                    Add_Pass(&PL,Pass_ID,Pass_Date,Pass_Time,Pass_From,Pass_To);
                }
        //end of reading
        }

    fclose(Pass_File);
    Print_Pass_List(PL);
    printf("\n\n===========================================\nPassengers Information Loaded Successfully!\n===========================================\n\n");
}


void Add_Pass(Pass_List *head_pass, int ID, int Date, char  Time[], char From[], char To[])
{//statement to check if passenger is unique or not
    if(Search_Pass(*head_pass,ID) == 0)
        {
            Pass_ptr newPassNode = (Pass_ptr)malloc(sizeof(struct Pass_Node));
            Pass_ptr last = *head_pass;
            newPassNode->Pass_ID = ID;
            newPassNode->Pass_Date = Date;
            strcpy(newPassNode->Pass_Time, Time);
            strcpy(newPassNode->Pass_From,From);
            strcpy(newPassNode->Pass_To,To);
            newPassNode->nextPass = NULL;

            if(*head_pass == NULL)
                {
                    *head_pass = newPassNode;
                    return;
                }

            while(last->nextPass != NULL)
                {
                    last = last->nextPass;
                }

            last->nextPass=newPassNode;
            return;
    }

    else
        {
            printf("\nPassenger Already Exists!\n\n");
        }
}

void Print_Pass_List(Pass_List PL)
{//print passenger by passenger from passenger list
    if(!isEmptyPass(PL))
        {
            Pass_ptr temp_pass = PL->nextPass;

            while(temp_pass != NULL)
                {
                    printf("| %d | %d | %s | %s | %s ",temp_pass->Pass_ID,temp_pass->Pass_Date,temp_pass->Pass_Time,temp_pass->Pass_From,temp_pass->Pass_To);
                    temp_pass = temp_pass->nextPass;

                    if(temp_pass != NULL)
                        {
                            printf("------->");
                        }
                }
        }

    else
        {
            printf("Empty Passengers List!!\n\n");
        }
}

int isEmptyPass(Pass_List PL)
{//check if passenger list is empty or not
    if(PL == NULL)
        {
            return 1;
        }

    else
        {
            return PL->nextPass == NULL;
        }
}

void Printing(Bus_List BL)
{// function to read bus by bus and then print each bus with its own passenger information
    printf("\n");
    printf("\n=====================================================\n");
    Pass_ptr temp;

    if(!isEmptyBus(BL))//check if bus list is empty or not
        {
            Bus_ptr temp_bus = BL->nextBus;

            while(temp_bus != NULL)
                {//while bus list not finished, read its own passenger list and print node by node
                    printf("| %d | %d | %s | %s | %s | %d | %d",temp_bus->Bus_Number,temp_bus->Bus_Date,temp_bus->Bus_Time,temp_bus->Bus_From,temp_bus->Bus_To,temp_bus->Price,temp_bus->Capacity);
                    temp = temp_bus->FirstPass;

                    if(temp != NULL)
                        {
                            printf(" :\n");
                            printf("->");
                            Printing_Pass_List(temp);
                        }

                    temp_bus = temp_bus->nextBus;

                    if(temp_bus != NULL)
                        {
                            printf("\n=====================================================\n");
                        }

                }
            printf("\n=====================================================\n");
        }

    else
        {//Error message if bus list is empty
            printf("\nEmpty Bus List!\n");
        }

    printf("\n");
}



void Printing_Pass_List(Pass_List PL)
{//read passenger list node by node and print each node by itself
    while(PL != NULL)
        {
            printf("| %d | %d | %s | %s | %s",PL->Pass_ID,PL->Pass_Date,PL->Pass_Time,PL->Pass_From,PL->Pass_To);

            if(PL->nextPass != NULL)
                {
                    printf("-->");
                }

            PL = PL->nextPass;
        }

}

void Searching(Bus_List BL, int Number)
{//function to search for a specific bus based on its number, and print this bus details with its passenger details
    BL = BL->nextBus;

    while(BL != NULL)
        {
            if(BL->Bus_Number == Number)
                {
                    printf("\n--------------------\nBus %d Found Already!\n--------------------\n\n",BL->Bus_Number);
                    printf("Bus Information:\n| %d | %d | %s | %s | %s | %d | %d |\n",BL->Bus_Number,BL->Bus_Date,BL->Bus_Time,BL->Bus_From,BL->Bus_To,BL->Price,BL->Capacity);

                    if(BL->FirstPass != NULL)
                        {
                            printf("\n\nPassengers Information:\n",BL->Bus_Number);
                        }

                    Printing_Pass_List(BL->FirstPass);
                    printf("\n");

                    break;
                }

            BL=BL->nextBus;
        }

    if(BL == NULL)
        {
            printf("\n-------------------\nBus Doesn't Exist!!\n-------------------\n");
        }
}

Pass_ptr Delete_Pass(Pass_List PL, int ID, int x)
{//delete passenger and return the new passenger list
    if(!isEmptyPass(PL))
        {
            if(Search_Pass(PL,ID) == 1)
                {
                    Pass_ptr ptr = FindPreviousPass(PL,ID);

                    if(ptr != NULL)
                        {
                            Pass_ptr deleted_pass = ptr->nextPass;
                            ptr->nextPass = deleted_pass->nextPass;
                            free(deleted_pass);
                            printf("\n----------------------------------------\nPassenger Has Been Deleted Successfully!\n----------------------------------------\n");
                        }
                }

            else
                {
                    if(x == 1)
                        {
                            printf("\n------------------------\nPassenger Doesn'n Exist!\n------------------------\n");
                        }
                }
        }

    else
        {
            if(x == 1)
                {
                    printf("\nYou Can't Delete From an Empty List!\n");
                }
        }

    return PL;
}

Pass_ptr FindPreviousPass(Pass_List PL, int ID)
{//used to redirect the pointer of previous node and let it point to the next after deleting process
    Pass_ptr a = PL->nextPass;
    Pass_ptr b = PL;

    while(a != NULL && b->nextPass->Pass_ID != ID)
        {
            b = b->nextPass;
            a = a->nextPass;
        }

    if(a == NULL)
        {
            return a;
        }

    else
        {
            return b;
        }
}

int Search_Pass(Pass_List PL, int ID)
{//function to search for a specific passenger using his id number
    PL = PL->nextPass;

    while(PL != NULL)
        {
            if(PL->Pass_ID == ID)
                {
                    return 1;

                    break;
                }

            PL = PL->nextPass;
        }

    if(PL == NULL)
        {
            return 0;
        }
}

void Deleteing(Pass_List PL, int ID)
{
    if(!isEmptyPass(PL))
        {
            if(Search_Pass(PL,ID) == 1)
                {

                    Pass_ptr ptr = FindPreviousPass(PL,ID);

                    if(ptr != NULL)
                        {
                            Pass_ptr deleted_pass = ptr->nextPass;
                            ptr->nextPass = deleted_pass->nextPass;
                            free(deleted_pass);
                        }
                }
        }
}

void Clear_List(Bus_List BL)
{//clear list after deleting bus or passenger so no misleading occur
    Bus_ptr TBL = BL->nextBus;

    while(TBL != NULL)
        {
            if(TBL->FirstPass != NULL)
                {
                    while(TBL->FirstPass != NULL)
                        {
                            Deleteing(TBL->FirstPass,TBL->FirstPass->Pass_ID);
                            TBL->FirstPass = TBL->FirstPass->nextPass;
                        }
                }

            TBL = TBL->nextBus;
        }

}


Bus_ptr Delete_Bus(Bus_List BL, int Bus_No)
{//function to delete bus using his number
    if(!isEmptyBus(BL))
        {
            if(Search_Bus(BL,Bus_No) == 1)
                {
                    Bus_ptr flag = FindPreviousBus(BL,Bus_No);
                    if(flag != NULL)
                        {
                            Bus_ptr d = flag->nextBus;
                            flag->nextBus = d->nextBus;
                            free(d);
                        }
                        printf("\n-----------------------------\nBus Has Deleted Successfully!\n-----------------------------\n");
                }

            else
                {
                    printf("\n------------------\nBus Doesn't Exist!\n------------------\n");

                }
        }

    else
        {
            printf("\nYou Can't Delete From an Empty List!\n");
        }

    return BL;
}


Bus_ptr FindPreviousBus(Bus_List BL, int Bus_No)
{//redirect pointer from previous to next and excepting the deleted node
    Bus_ptr a = BL->nextBus;
    Bus_ptr b = BL;

    while(a != NULL && b->nextBus->Bus_Number != Bus_No)
        {
            b = b->nextBus;
            a = a->nextBus;
        }

    if(a == NULL)
        {
            return a;
        }
    else
        {
            return b;
        }
}

int Search_Bus(Bus_List BL, int Number)
{//search in bus list for a specific bus using his number
    BL = BL->nextBus;

    while(BL != NULL)
        {
            if(BL->Bus_Number == Number)
                {
                    return 1;

                    break;
                }

            BL = BL->nextBus;
        }

    if(BL == NULL)
        {
            return 0;
        }
}

void Add_To_Unmatch(Pass_List UnmatchedList, Bus_ptr BL)
{//add passengers from a deleted bus to unmatched list
    Pass_ptr TempPass = BL->FirstPass;

    while(TempPass != NULL)
        {
            Add_Pass(&UnmatchedList,TempPass->Pass_ID,TempPass->Pass_Date,TempPass->Pass_Time,TempPass->Pass_From,TempPass->Pass_To);
            TempPass = TempPass->nextPass;
        }
}

Bus_ptr Scaning(Bus_List BL, int Number)
{//function that search for a specific bus using his number and return a pointer to that bus, so we can use this pointer to add this bus passengers to unmatched list before deleting it!
    BL = BL->nextBus;

    while(BL != NULL)
        {
            if(BL->Bus_Number == Number)
                {
                    return BL;

                    break;
                }

            BL = BL->nextBus;
        }
}
