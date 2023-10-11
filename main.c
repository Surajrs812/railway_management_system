#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#define BLOCKSIZE 50
FILE *fp1,*fp2;

typedef struct train {
    int number;
    int blocks;
    char arrival[10];
    char departure[10];
    char source[50];
    char destination[50];
    struct train *lptr, *rptr;
}node1;

typedef struct passenger
{
    char pname[20];
    char gender;
    char board[20];
    char deboard[20];
    int dist;
    int trno;
    int pnrno;
    int type;
    struct passenger *rptr, *lptr;

}node2;
node1 *start1 = NULL;
node2 *start2 = NULL;

node1 *getnode1() {  //TRAIN DETAILS
    node1 *new1;
    new1 = (node1 *) malloc(sizeof(node1));
    printf("\n\tEnter the train number                 :");
    scanf("%d",&new1->number);
    printf("\n\tEnter the time of arrival              :");
    scanf("%s",new1->arrival);
    printf("\n\tEnter the time of departure            :");
    scanf("%s",new1->departure);
    printf("\n\tEnter the starting point of the train  :");
    scanf("%s",new1->source);
    printf("\n\tEnter the destination place            :");
    scanf("%s",new1->destination);
    printf("\n\tEnter the number of blocks in train    :");
    scanf("%d",&new1->blocks);
    new1->lptr = new1->rptr = NULL;
    return (new1);
}

void addTrain()
{
    node1 *new1;
    new1 = getnode1();
    node1 *temp = start1;
    if (start1 == NULL) {
        start1 = new1;
        return;
    }
    while (temp->rptr != NULL) {
        temp = temp->rptr;
    }
    temp->rptr = new1;
    new1->lptr = temp;
}

void addfile1()// To store train data into TRAININFO.txt file
{
    node1 *temp=start1;
    fp1=fopen("TRAININFO.txt","a");
    if (start1 == NULL) {
        printf("\n........   Currently there are no trains   ........\n");
        return;
    }
    while(temp!=NULL) {
        fprintf(fp1,"Train Number:%d\tArrival Time:%s\t\tDeparture Time:%s\t\tSource:%s\t\tDestination:%s\t\tBlocks In Train:%d\n",
                temp->number, temp->arrival, temp->departure, temp->source, temp->destination, temp->blocks);
        temp = temp->rptr;
    }
    fclose(fp1);
}

void displayTrain() {
    node1 *temp = start1;
    if (start1 == NULL) {
        printf("\n........   Currently there are no trains   ........\n");
        return;
    }
    printf("\n----------------------------    DETAILS OF THE TRAIN ARE    ------------------------------\n\n");
    while (temp != NULL) {
        printf("\n\ttrain number       = %d\n\tStarting point     = %s\n\tDestination point  = %s\n\tTime of Arrival    = %s\n\tDeparture Time     = %s\n\tNumber of seats    = %d\n\n",
               temp->number, temp->source, temp->destination, temp->arrival, temp->departure,(BLOCKSIZE) * temp->blocks);
        temp = temp->rptr;
    }
}

int searchTrain(int trainNum) { //Searches for existance of train accepting train num.Returns 1 if found else returns 0.
    int flag = 0;
    node1 *temp = start1;
    while (temp != NULL) {
        if (temp->number == trainNum) {
            flag = 1;
            break;
        }
        temp = temp->rptr;
    }
    return flag;
}

void deleteTrain() {
    node1 *temp = start1;
    int trainNum;
    printf("\nEnter the train number to be deleted : ");
    scanf("%d", &trainNum);
    if (start1 == NULL) {
        printf("\n........   No trains are present   ........ \n");
        return;
    }
    //1 node case
    if (start1->rptr == NULL) {
        if (start1->number == trainNum) {
            printf("\nDeleted train with train number  : %d\n", temp->number);
            free(start1);
            start1 = NULL;
            return;
        }
        else
            printf("\n**  Train not found  **");
        return;
    }
    //many nodes - 1st node is culprit
    if (temp->number == trainNum) {
        printf("\nDeleted train with train number  : %d\n", temp->number);
        temp = temp->rptr;
        free(start1);
        start1 = temp;
        return;
    }
    //culprit hides in-between
    while (temp->rptr != NULL) {
        if (temp->number == trainNum) {
            printf("\nDeleted train with train number  : %d\n", temp->number);
            (temp->rptr)->lptr = temp->lptr;
            (temp->lptr)->rptr = temp->rptr;
            free(temp);
            return;
        }
        temp = temp->rptr;
    }
    //culprit is last node - which in above code when included gives "seggy fault"
    if (temp->number == trainNum) {
        printf("\nDeleted train with train number  : %d\n", temp->number);
        (temp->lptr)->rptr = NULL;
        free(temp);
        return;
    }
    printf("\nNo such train with train number %d exists \n", temp->number);
}

void modifyTrain() {
    node1 *temp=start1;
    int ch,trainnum,flag;
    printf("\nEnter the Train Number that you want to modify :");
    scanf("%d",&trainnum);
    flag=searchTrain(trainnum);;
    if(flag == 1)
    {
        while(temp->rptr!=NULL)
        {
            if(temp->number==trainnum)
                break;
            else
                temp=temp->rptr;
        }
        while(true) {
            printf("\nWhat do you want to modify?\n\n\t1.Starting point\n\t2.Destination point\n\t3.Time of Arrival\n\t4.Departure time\n\t5.Number of blocks in Train\n\t6.No further modification\n\nEnter Your Choice: ");
            scanf("%d", &ch);
            switch (ch) {
                case 1:
                    printf("\nEnter the new starting point of the train  :");
                    scanf("%s", temp->source);
                    printf(".........   Modification Successful   ........\n");
                    break;
                case 2:
                    printf("\nEnter the new destination place            :");
                    scanf("%s", temp->destination);
                    printf(".........   Modification Successful   ........\n");
                    break;
                case 3:
                    printf("\nEnter the updated time of arrival           :");
                    scanf("%s", temp->arrival);
                    printf(".........   Modification Successful   ........\n");
                    break;
                case 4 :
                    printf("\nEnter the updated time of departure         :");
                    scanf("%s", temp->departure);
                    printf(".........   Modification Successful   ........\n");
                    break;
                case 5:
                    printf("\nEnter the updated number of blocks in train  :");
                    scanf("%d", &temp->blocks);
                    printf(".........   Modification Successful   ........\n");
                    break;
                case 6:
                    return;
                default:
                    printf("\nInvalid choice for Updation.Please check you input and try again ");
                    return;
            }
        }
    }
    else
        printf("\n**  Train not found  **");
}


node2 *getnode2()
{
    node2 *new2;
    node2 *temp = start2;
    int tno;
    char YN;
    new2 = (node2 *)malloc(sizeof(node2));
    printf("\n\tEnter the train number                :\t");
    scanf("%d",&tno);
    if(searchTrain(tno) == 0)
    {
        printf("\nTrain doesn't exist, try again");
        free(new2);
        getnode2();
    }
    new2->trno = tno;
    printf("\n\tEnter the 5 digit PNR number      :\t");
    scanf("%d",&new2->pnrno);
    printf("\n\tEnter Name of passenger           :\t");
    scanf("%s",new2->pname);
    printf("\n\tEnter the gender (M/F/T)          :\t");
    scanf("\n%c",&new2->gender);
    printf("\n\tEnter the boarding station        :\t");
    scanf("%s",new2->board);
    printf("\n\tEnter the de-boarding Station     :\t");
    scanf("%s",new2->deboard);
    printf("\n\tEnter the distance                :\t");
    scanf("%d",&new2->dist);
    printf("\n\tEnter the Seat type:\n\t1 for A/C class\n\t2 for Sleeper class\n\t3 for General class\t:");
    scanf("%d",&new2->type);
    new2->rptr=new2->lptr=NULL;
    return(new2);
}


void deletePAssenger(int pnr) //invisible to main
{
    node2 *temp = start2;
    if (start2 == NULL) {
        printf("\n........   No passengers are present   ........ \n");
        return;
    }
    //1 node case
    if (start2->rptr == NULL) {
        if (start2->pnrno == pnr) {
            printf("\nDetails of passenger %s is deleted\n", temp->pname);
            free(start2);
            start2 = NULL;
            return;
        }
        else
            printf("\n**  Passenger not found  **");
        return;
    }
    //many nodes - 1st node is culprit
    if (temp->pnrno == pnr) {
        printf("\nDetails of passenger %s is deleted\n", temp->pname);
        temp = temp->rptr;
        free(start2);
        start2 = temp;
        return;
    }
    //culprit hides in-between
    while (temp->rptr != NULL) {
        if (temp->pnrno == pnr) {
            printf("\nDetails of passenger %s is deleted\n", temp->pname);
            (temp->rptr)->lptr = temp->lptr;
            (temp->lptr)->rptr = temp->rptr;
            free(temp);
            return;
        }
        temp = temp->rptr;
    }
    //culprit is last node - which in above code when included gives "seggy fault"
    if (temp->pnrno == pnr) {
        printf("\nDetails of passenger %s is deleted\n", temp->pname);
        (temp->lptr)->rptr = NULL;
        free(temp);
        return;
    }
    printf("\nNo such train with train number %d exists \n", temp->pnrno);
}

float totalFare(int dist, int type)
{
    float fare;
    if (dist <= 50)
        fare = dist * 2.0;
    else if (dist >51 && dist <= 100)
        fare = (dist-50.0)*5.0+ 50.0*3.0;
    else if (dist > 100 && dist <= 500)
        fare =  (dist-100.0)*7.0 + 100.0*5.0;
    else
        fare =  (dist-500.0)*10.0+500.0*5.0;

    switch (type)
    {
        case 1: fare+=200.0; break;
        case 2: fare+=150.0; break;
        case 3: fare+=100.0; break;
        default: printf("\n**  The type doesnt exist  **");

    }
    return fare;
}

void passengerlist()
{
    node2 *temp=start2;
    if(start2==NULL)
    {
        printf("\n.........   Passenger list is empty   ..........\n");
        return;
    }
    printf("\n----------  Passenger list for the day  -----------\n");
    printf("\nPNR Number\tPassengerName\t\tTrainNumber\tGender\t\t\tBoard\t\tDeboard\tSeatType\n");
    while(temp != NULL)
    {
        printf("%d\t\t%10s\t\t\t%d\t\t%c\t\t%10s\t%10s\t%d\n",temp->pnrno,temp->pname,temp->trno,temp->gender,temp->board,temp->deboard,temp->type);
        temp=temp->rptr;
    }
}

void addPassenger()
{
    node2 *new2;
    new2 = getnode2();
    node2 *temp = start2;
    if (start2 == NULL) {
        start2 = new2;
        return;
    }
    while (temp->rptr != NULL) {
        temp = temp->rptr;
    }
    temp->rptr = new2;
    new2->lptr = temp;
}

void cancelTicket() {
    node2 *temp = NULL;
    int pnr;
    printf("\n-------  Cancelling ticket  -------\n\n");
    printf("\nEnter the PNR number\t:\t ");
    scanf("%d", &pnr);
    node2 *pass= start2;
    while(pass != NULL)
    {
        if(pnr== pass->pnrno) {
            temp = pass;
            break;
        }
        else
            pass = pass->rptr;
    }
    if(temp == NULL) {
        printf("\n**  Passenger does not exist  **\n");
        return;
    }

    printf("\n\t|   Total Fare\t=\t%.2f   |",0.6*totalFare(temp->dist,temp->type));
    deletePAssenger(pnr);
}
void showTicket(int pnr)
{
    node2 *pass= start2;
    node2 *temp = NULL;
    while(pass != NULL)
    {
        if(pnr== pass->pnrno) {
            temp = pass;
            break;
        }
        else
            pass = pass->rptr;
    }
    if(temp == NULL) {
        printf("\n**  Passenger doesnt exist  **\n");
        return;
    }
    printf("\n----------------------------------------------------------------------\n");
    printf("\n|\tTrain number   = %d",temp->trno);
    printf("\n|\tPassenger name = %s",temp->pname);
    printf("\n|\tPNR number    = %d",temp->pnrno);
    printf("\n|\tGender      = %c",temp->gender);
    printf("\n|\tBoard from    = %s",temp->board);
    printf("\n|\tDeboard to    = %s",temp->board);
    printf("\n|\tSeat type     = %d",temp->type);
    printf("\n|\tTotal Fare   = %.2f",totalFare(temp->dist,temp->type));
    printf("\n-------------------------------------------------------------------------\n");
}

void addfile2()
{
    node2 *temp=start2;
    fp2=fopen("PASSENGERINFO.txt","a");
    if (start2 == NULL) {
        printf("\n........   Currently there are no passengers   ........\n");
        return;
    }
    while(temp!=NULL){
        fprintf(fp2,"PNR Number:%d\tPassenger Name:%s\t\tGender:%c\t\tBoarding Staion:%s\t\tDe-boarding Station:%s\t\tDistance:%d\t\tSeat Type:%d\n",temp->pnrno,temp->pname,temp->gender,temp->board,temp->deboard,temp->dist,temp->type);
        temp=temp->rptr;

    }
    fclose(fp2);


}

void main() {
    printf("\n\n\n");
    printf("\n\n\t\t\t\t***      WELCOME TO TRAIN MANAGEMENT SYSTEM       **\n\n\n");
    printf(""
           "                             /\\                    /\\\n"
           "                         _\\/_============_\\/__    ___=======================\n"
           "                        /_|     OOOOOOOOOOOOO    []     |    |  |[]|  []    []    [_]\n"
           "                       /             T R A I N            |    |  |  |\n"
           "                       \\___________|ii|_||_______\n"
           "                        ()==()    === ++++ ===   ()==()       ()==()     +++   ++++++++\n"
           "                     ===================================================================\n");
    int ch1=0, trainNum;
    do{
        printf("\n\n");
        printf("\n============================================================================================================");
        printf("\n\n\t\t\t\t\t\t|   Main menu   |\n\n1.Train Module\n2.Ticket booking and Passenger Module\n3.Fare Module\n4.Exit\n\nEnter your choice\t:");
        scanf("%d",&ch1);
        if(ch1==4)
        {
            printf("\n\n\t\t~ ~ ~ ~  Thank You For Using Our Version Of Train Management System  ~ ~ ~ ~\n\n");
            exit(0);
        }
        printf("======================================================\n\n");
        switch (ch1)
        {
            case 1: {
                printf("\n\n\t\t\t\t|**   WELCOME TO TRAIN MODULE   **|\n\n");
                int ch2 = 0;
                do {
                    printf("\n=======================================================");
                    printf("\n1.Add New Train Details\n2.Delete Train Details\n3.Display Train List\n4.Search train\n5.Modify Train Details\n6.Back to main menu\n\nPlease Enter Your Choice\t:");
                    scanf("%d", &ch2);
                    printf("=========================================================\n");
                    switch (ch2) {
                        case 1:
                            addTrain();
                            break;
                        case 2:
                            deleteTrain();
                            break;
                        case 3:
                            displayTrain();
                            break;
                        case 4:
                            printf("\nEnter the train number to search for\t:\t ");
                            scanf("%d", &trainNum);
                            int flag = searchTrain(trainNum);
                            if (flag == 1)
                                printf("\n**     Train found     **\n");
                            else
                                printf("\n**     Train not found     **\n");
                            break;
                        case 5:
                            modifyTrain();
                            break;
                    }
                } while (ch2 != 6);
                printf("\n\t\tThe contents are successfully updated in the train module file\n");
                addfile1();
                ch2 = 0;
            }
                break;

            case 2: {
                int ch3 = 0;
                printf("\n\n\t\t\t\t|**   WELCOME TO TICKET AND PASSENGER MODULE   **|\n\n");
                do{
                    printf("\n======================================================");
                    printf("\n1.Book a ticket\n2.Cancel the ticket\n3.Display the ticket\n4.Passenger list for the day\n5.Back to main menu\n\nPlease Enter your choice\t:");
                    scanf("%d", &ch3);
                    printf("========================================================\n");
                    int pnr;
                    switch (ch3) {
                        case 1:
                            addPassenger();
                            break;
                        case 2:
                            cancelTicket();
                            break;
                        case 3:
                            printf("\nEnter the pnr number\t:\t ");
                            scanf("%d", &pnr);
                            showTicket(pnr);
                            break;
                        case 4:
                            passengerlist();
                            break;
                    }
                }while(ch3 != 5);
                printf("\n\t\tThe contents are successfully updated in the file\n\n");
                addfile2();
                ch3=0;
            }
                break;

            case 3:{
                int dist,type,ch4=0;
                float fare=0,ref=0;
                printf("\n====================================================================\n");
                printf("\n\n\t\t\t\t|**   WELCOME TO FARE MANAGEMENT MODULE   **|");
                do{
                    printf("\n=============================================================\n\n");
                    printf("\n1.Fare for travelling\n2.Refund for cancelling ticket\nEnter your choice\t:");
                    scanf("%d",&ch4);
                    printf("-----------------------------------------------------\n");
                    switch(ch4)
                    {
                        case 1:printf("\nEnter distance\t: ");
                            scanf("%d",&dist);
                            printf("\nChart of seat type:\n\t1.AC class\n\t2.Sleeper class\n\t3.General class\n\t4.Main Menu\n\tEnter the choice\t:\t");
                            scanf("%d",&type);
                            fare = totalFare(dist,type);
                            printf("\nFare\t=\t%.2f",fare);
                            break;
                        case 2:printf("\nEnter distance: ");
                            scanf("%d",&dist);
                            printf("\nChart of seat type:\n\t1.AC class\n\t2.Sleeper class\n\t3.General class\n\tEnter the choice\t:\t");
                            scanf("%d",&type);
                            printf("\n60 percent of your money will be refunded");
                            ref = 0.6*totalFare(dist,type);
                            printf("\nRefunded Fare\t=\t%.2f",ref);
                            break;
                    }
                }while(ch4 !=3);
                ch4=0;
            }

        }
    }while(ch1 != 4);
    exit(0);
}