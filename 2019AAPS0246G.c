/**********************************************PREPROCESSORS**********************************************************/
//Railway Reservation System for Migrant Labourers
//Working on basic structure
//including all libraries for now
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
/*******************************************GLOBAL VARIABLES**********************************************************/
// All the globle variables and the composite data types will be declared here
// Structure-based implementation of trains and tickets

typedef struct{
char name[50];
int train_num;
int number_of_seats;
}tickets;

static int PNR;

typedef struct{
    char pnr[50];
    char name[50];
    char noofseats[50];
    char trainno[50];
    char train[50];
    char destination[50];
    char departure[50];
    char charges[50];
}ticketdetails;

typedef struct{
    int train_num;
    char train_name[40];
    char source[40];
    char destination[40];
    int price;
    char time[10];
    unsigned int seats;
}trains;
trains t[10];


/*******************************************FUNCTION PROTOTYPE**********************************************************/
                                    //function prototypes to be used

void reservation(void);                                 //main reservation function
void viewdetails(void);                                 //view details of all the trains
void cancel(void);                                      //Function to cancel reservation and refund amount
void printticket(char name[],int,int,float);            //print ticket
void specifictrain(int);                                //print data related to specific train
float charge(int,int);                                  //charge automatically w.r.t number of seats and train
void collectdata(void);                                 //code collects data which is stored in the file named train_details
void GeneratePNR(void);                                 //This function generates a PNR No.
void cls(void);                                         //The function is used as an alternative for clear screen

/******************************************FUNCTION DECLARATION**********************************************************/


/*********************************************MAIN()*************************************************/

int main()

{
    cls();
    printf("\t\t=================================================\n");
    printf("\t\t|                                               |\n");
    printf("\t\t|        -----------------------------          |\n");
    printf("\t\t|          RAILWAY RESERVATION SYSTEM           |\n");
    printf("\t\t|        -----------------------------          |\n");
    printf("\t\t|                                               |\n");
    printf("\t\t|                                               |\n");
    printf("\t\t|                                               |\n");
    printf("\t\t|                   |IRCTC|                     |\n");
    printf("\t\t|                   WELCOME!                    |\n");
    printf("\t\t|                                               |\n");
    printf("\t\t=================================================\n\n\n");


    printf(" \n Press Enter to continue:");

    char a;                             //random char variable is declared as alternative for holding the screen
    scanf("%c", &a);
    collectdata();                      //data from train_details file is collected into our code!
    GeneratePNR();                      //PNR Number is generated
    cls();                              //Function as an  alternative for clear screen
    int menu_choice;
    start:
    cls();
    printf("\n=================================\n");
    printf("    TRAIN RESERVATION SYSTEM");
    printf("\n=================================");
    printf("\n1>> Enquiry");
    printf("\n------------------------");
    printf("\n2>> Reserve A Ticket");
    printf("\n------------------------");
    printf("\n3>> Cancel Reservation");
    printf("\n------------------------");
    printf("\n4>> Exit");
    printf("\n------------------------");
    printf("\n\n-->");
    scanf("%d",&menu_choice);

    switch(menu_choice)
    {
        case 1:
            viewdetails();                                              //Function For Enquiry
            printf("\n\nHit Enter to go to Main Menu!!");
            scanf("%c", &a);
            scanf("%c", &a);
        break;

        case 2:
            reservation();                                              //Function for Reserving a Ticket
            scanf("%c",&a);
        break;

        case 3:
            cancel();                                                   // Function for Cancelling a Reserved Ticket
            scanf("%c",&a);
        break;

        case 4:
        return(0);                                                     //Exit the Program

        default:
            printf("\nInvalid choice");
    }
        goto start;
        return(0);
}

/*********************************************COLLECTDATA()**************************************************/
// Collects data from the file named as train_details

void collectdata(void)
{
    FILE *fp;
    fp = fopen("train_details","r");
    int i;
    for(i=0;i<11;i++)
    {
        fscanf(fp, "%d %s %s %s %d %s %d", &t[i].train_num, t[i].train_name, t[i].source, t[i].destination, &t[i].price, t[i].time, &t[i].seats);

    }

    fclose(fp);
}

/*********************************************VIEWDETAILS()**************************************************/
//This Function serves the enquiry from a source station to the final destination of the labourer.
//Also tells the number of seats left in a particular train.
//Takes user input for source station and destination if source is other than Delhi then no trains available is shown
//If any other destination other than the available trains are input then also no trains are shown and the user is asked for another destination
void viewdetails(void)
{
    char from_city[30];
    char to_city[30];

    cls();
    printf("----------------------------------------------------------------------------------------------------");
    printf("\nTr.No \tName   \t\t\tSource  \tDestinations  \tCharges  \tTime  \n");
    printf("----------------------------------------------------------------------------------------------------");

    for (int i = 0;i < 10;i++)
    {
        printf("\n%d \t%s    \t%s  \t\t%s   \t%d   \t\t%s   ",t[i].train_num, t[i].train_name, t[i].source, t[i].destination, t[i].price, t[i].time);
    }
    station:
    printf("\n\nEnter Source Station (USE ONLY CAPITAL LETTERS!!)->>");

    scanf("%s%*[^\n]%*c",from_city);
    if(strcmp(from_city, "DELHI")==0)
    {
        station1:
        printf("Enter Destination Station (USE ONLY CAPITAL LETTERS!!)->>");
        scanf("%s%*[^\n]%*c",to_city);
        if(strcmp(to_city, "JAIPUR")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[0].train_num, t[0].train_name, t[0].source, t[0].destination, t[0].seats);
        else if(strcmp(to_city, "AMBALA")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[1].train_num, t[1].train_name, t[1].source, t[1].destination, t[1].seats);
        else if(strcmp(to_city, "BATHINDA")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[2].train_num, t[2].train_name, t[2].source, t[2].destination, t[2].seats);
        else if(strcmp(to_city, "LUCKNOW")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[3].train_num, t[3].train_name, t[3].source, t[3].destination, t[3].seats);
        else if(strcmp(to_city, "HYDRABAD")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[4].train_num, t[4].train_name, t[4].source, t[4].destination, t[4].seats);
        else if(strcmp(to_city, "MUMBAI")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[5].train_num, t[5].train_name, t[5].source, t[5].destination, t[5].seats);
        else if(strcmp(to_city, "PATNA")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[6].train_num, t[6].train_name, t[6].source, t[6].destination, t[6].seats);
        else if(strcmp(to_city, "GANDHINAGAR")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[7].train_num, t[7].train_name, t[7].source, t[7].destination, t[7].seats);
        else if(strcmp(to_city, "CHENNAI")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[8].train_num, t[8].train_name, t[8].source, t[8].destination, t[8].seats);
        else if(strcmp(to_city, "RANCHI")==0)
            printf("\nTr no.:\t\t%d \nTrain:\t\t%s    \nSource:\t\t%s  \nDestination:\t%s   \nSeats Left:\t%d\n",t[9].train_num, t[9].train_name, t[9].source, t[9].destination, t[9].seats);
        else
            {
             printf("Sorry! No Trains for your Destination\n");
             goto station1;
            }
    }
    else
    {
        printf("Sorry! No Trains Available");
        goto station;
    }
}

/*********************************************RESERVATION()*************************************************/
//Function For Reserving a Train Ticket
//
void reservation(void)
{
    char confirm;
    float charges;
    tickets passdetails;
    passdetails.number_of_seats = 1;

    FILE *fp;
    fp=fopen("seats_reserved.txt","a");             //opens file named seats_reserved.txt
    cls();

    printf("\nEnter Your First Name:> ");
    fflush(stdin);
    scanf("%s", passdetails.name);

    printf("\n\n>>Press Enter To View Available Trains<< ");
    char a;
    scanf("%c", &a);                                //Used as an alternative for holding the screen

    cls();
    viewdetails();
    start1:
    printf("\n\nEnter train number:> ");
    scanf("%d",&passdetails.train_num);

        int k = passdetails.train_num;
        k = k-1001;                                //Checking Available seats
        if(k>=0 && k<10)
        {
            if(t[k].seats <= 0)
            {
                printf("\nSorry!! No seats available.\nHit Enter to go back to Main Menu!");
                goto end;
            }
        if(passdetails.train_num>=1001 && passdetails.train_num<=1010)
        {
            charges=charge(k,passdetails.number_of_seats);
            printticket(passdetails.name,passdetails.number_of_seats,passdetails.train_num,charges);
        }
        else
        {
            printf("\nInvalid train Number! Enter again--> ");
            goto start1;
        }
        }
        else
        {
            printf("\nInvalid train Number! Enter again--> ");
            goto start1;
        }
    printf("\n\nConfirm Ticket (y/n):>");
    start:
    scanf(" %c",&confirm);

    if(confirm == 'y')
    {
        PNR++;                                          //PNR incremented
        t[k].seats--;                                   //available seats decremented

        fprintf(fp,"\nPNR:                    %d",PNR);
        fprintf(fp,"\nName:                   %s",passdetails.name);
        fprintf(fp,"\nNumber Of Seats:        %d",passdetails.number_of_seats);
        fprintf(fp,"\nTrain Number:           %d",passdetails.train_num);

        fprintf(fp,"\nTrain:                  %s\nDestination:            %s\nDeparture:              %s", t[k].train_name, t[k].destination, t[k].time);
        fprintf(fp,"\nCharges:                %.2f\n",charges);

        printf("==================");
        printf("\n Reservation Done\n");
        printf("==================");
        printf("\n Your PNR Number is %d", PNR);
        printf("\nPress any key to go back to Main menu");
    }
    else
    {
        if(confirm=='n')
        {
            printf("\nReservation Not Done!\nPress any key to go back to  Main menu!");
        }
        else
        {
            printf("\nInvalid choice entered! Enter again-----> ");
            goto start;
        }
        }
        end:
        fclose(fp);
        scanf("%c", &a);                            //again used for holding screen
        }
/******************************************GeneratePNR*************************************************/
//generates a random PNR number at the begging but continues to increment the same PNR till the program is ended
void GeneratePNR()
{
    srand(time(0));
    PNR = rand();
}

/*********************************************CHARGE()*************************************************/
//Calculates the amount to be paid

float charge(int train_num,int num_of_seats)
{
    return(t[train_num].price);
}


/*********************************************PRINTTICKET()********************************************/
//The final printing of the ticket with all ticket and the user details which include the amount to be paid!

void printticket(char name[],int num_of_seats,int train_num,float charges)
{
    cls();
    printf("-------------------\n");
    printf("\tTICKET\n");
    printf("-------------------\n\n");
    printf("Name:\t\t\t%s",name);
    printf("\nNumber Of Seats:\t%d",num_of_seats);
    printf("\nTrain Number:\t\t%d",train_num);
    specifictrain(train_num);
    printf("\nCharges:\t\t%.2f",charges);
}

/*********************************************SPECIFICTRAIN()*************************************************/
//Information about a specific train which is stored in our structure which was loaded from the file named train_details
void specifictrain(int train_num)
{
    int k = train_num -1001;
        {
            printf("\nTrain:\t\t\t%s\nSource:\t\t\t%s\nDestination\t\t%s\nDeparture\t\t%s",t[k].train_name, t[k].source, t[k].destination,t[k].time);
        }
}


/***********************************************CANCEL()******************************************************/
// This program is used for cancelling a reserved ticket using the PNR number of the ticket
//Also returns 50% of the money and also increments a seat when the ticket is cancelled
void cancel(void)
{

    char PNRnum[15];

    char abc[] = "PNR:                    ";
    int trn,tpr;
    printf("-----------------------\n");
    printf("Enter the PNR number: \n");
    printf("-----------------------\n");
    fflush(stdin);
    scanf("%s",PNRnum);
    printf("Enter Train number:\n");
    scanf("%d",&trn);

    while(!(trn > 1000 && trn <= 1010))
    {
      printf("Enter train number from 1001 to 1010\n");
      scanf("%d",&trn);
    }

    trn = trn-1001;                             //variable used for checking price through train number
    printf("THANK YOU FOR BELIEVING IN US!");
    tpr = t[trn].price/2;
    t[trn].seats++;                             //number of seats get incremented

    char tickett[100];
    strcpy(tickett,abc);
    strcat(tickett,PNRnum);
    strcat(tickett,"\n");
    FILE *fp1 = fopen("seats_reserved.txt", "r");
    FILE *fp2 = fopen("temp", "w");
    while(1)
    {
         char temp[50];
         fgets(temp, 100, fp1);
         if(!strcmp(temp, tickett))
         {
            for(int i = 0; i < 8; i++)
            {
                fgets(temp, 100, fp1);
                if(temp[6] == 'N')
                {
                    FILE *fp3 = fopen("train_details", "r");
                    FILE *fp4 = fopen("temp2", "w");
                    while(1)
                    {
                        char temp2[100];
                        fgets(temp2, 100, fp3);
                        if(temp2[3] == temp[27])
                        {
                            if(temp2[57] == '9')
                            {
                                temp2[56]++;
                                temp2[57] = '0';
                            }
                            else
                            {
                                temp2[57]++;
                            }
                        }
                        if(feof(fp3))
                        {
                            break;
                        }
                        fputs(temp2, fp4);
                    }
                    fclose(fp3);
                    fclose(fp4);
                }
            }
         }
         else if(feof(fp1))
         {
             break;
         }
         else
         {
             fputs(temp, fp2);
         }
    }
    fclose(fp1);
    fclose(fp2);

    fp1 = fopen("temp", "r");
    fp2 = fopen("seats_reserved.txt", "w");
    char c;
    while(!feof(fp1))
    {
        c = fgetc(fp1);
        if(c != EOF)
        {
            fputc(c, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("temp");
    fp1 = fopen("temp2", "r");
    fp2 = fopen("train_details", "w");
    while(!feof(fp1))
    {
        c = fgetc(fp1);
        if(c != EOF)
        {
            fputc(c, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("temp2");
    printf("\nYour Ticket has been cancelled.\n");
    printf("\nAmount Rs. %d has been refunded.\n", tpr);

    char index;
    scanf("%c", &index);
}

/*************************************************cls**()******************************************************/
//This function is used as an alternative for the clear screen not a exact alternative but leaves some space before further execution of the code

void cls(void)
{
    for(int i = 0; i < 10; ++i)
        printf("\n");

}
