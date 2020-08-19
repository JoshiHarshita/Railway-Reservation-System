#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include "conio2.h"
#include "rlyres.h"
int enterchoice()
{
    int choice,i;
    textcolor(LIGHTCYAN);
    gotoxy(26,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1;i<=75;i++)
    printf("-");
    printf("Select an option\n");
    printf("1- View Trains\n2- Book Ticket\n3- View Ticket\n4- Search Ticket No\n5- View All Bookings\n6- View Train Bookings\n7- Cancel Ticket\n8- Cancel Train\n9- Quit");
    printf("\nEnter choice:");
    scanf("%d",&choice);
    return choice;
}
void add_trains()
{
    FILE *fp;
    fp=fopen("D:\\Railway Reservation System\\alltrains.dat","rb");
    if(fp==NULL)
    {
       Train alltrains[4]={
       {"123","BPL","GWA",2100,1500},
       {"546","BPL","DEL",3500,2240},
       {"345","HBJ","AGR",1560,1135},
       {"896","HBJ","MUM",4500,3360},
       };
       fp=fopen("D:\\Railway Reservation System\\alltrains.dat","wb");
       fwrite(alltrains,4*sizeof(Train),1,fp);
       printf("File saved successfully...\n");
       _getch();
       fclose(fp);
    }
    else
    {
        printf("File already exists...\n");
        _getch();
        fclose(fp);

    }
}
void view_trains()
{
    FILE *fp;
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FAIR\tSECOND AC FAIR\n");
    for(i=0;i<=74;i++)
        printf("-");
    fp=fopen("D:\\Railway Reservation System\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
        printf("\n\n\n\n");
        fclose(fp);
}
int check_train_no(char *p)
{
    FILE *fp;
    fp=fopen("D:\\Railway Reservation System\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(tr.train_no,p)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclosgite(fp);
    return 0;
}
Passenger *get_passenger_details()
{
    clrscr();
    gotoxy(60,1);
    textattr(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(LIGHTCYAN);
    printf("Enter Passenger Name:");
    static Passenger psn;
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos;                                                    //ending string with '\0'
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,20);
        printf("Reservation Canceled!");
        _getch();
        textcolor(LIGHTCYAN);
        return NULL;
    }
    int valid;
    printf("Enter Gender(M/F):");
    do
    {
        valid=0;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,20);
            printf("Reservation Canceled!");
            _getch();
            textcolor(LIGHTCYAN);
            return NULL;
        }
        if(psn.gender!='M'&&psn.gender!='F')
        {
            valid=1;
            textcolor(LIGHTRED);
            gotoxy(1,20);
            printf("Error! Gender should be M or F(in uppercase)");
            _getch();
            gotoxy(1,20);
            printf("\t\t\t\t\t\t");
            gotoxy(19,2);
            printf(" \b");
            textcolor(LIGHTCYAN);
        }
    }while(valid==1);
    printf("Enter Train No:");
    do
    {
        valid=0;
        fflush(stdin);
        fgets(psn.train_no,20,stdin);
        pos=strchr(psn.train_no,'\n');
        *pos='\0';
        if(strcmp(psn.train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,20);
            printf("Reservation Canceled!");
            getch();
            textcolor(LIGHTCYAN);
            return NULL;
        }
        int x;
        x=check_train_no(psn.train_no);
        if(x==0)
        {
            valid=1;
            textcolor(LIGHTRED);
            gotoxy(1,20);
            printf("Error! Invalid Train No");
            _getch();
            gotoxy(1,20);
            printf("\t\t\t\t\t\t");
            gotoxy(16,3);
            printf("                                       ");
            gotoxy(16,3);
            textcolor(LIGHTCYAN);
        }
    }while(valid==1);
    printf("Enter Reservation Class(F/S):");
    do
    {
        valid=0;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=="0")
        {
            textcolor(LIGHTRED);
            gotoxy(1,20);
            printf("Reservation Canceled!");
            _getch();
            textcolor(LIGHTCYAN);
            return NULL;
        }
        if(psn.p_class!='F'&&psn.p_class!='S')
        {
            valid=1;
            textcolor(LIGHTRED);
            gotoxy(1,20);
            printf("Error! Reservation class should be F and S(in uppercase)");
            _getch();
            gotoxy(1,20);
            printf("\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(30,4);
            printf("              \r");
            gotoxy(30,4);
            textcolor(LIGHTCYAN);
        }
    }while(valid==1);
    printf("Enter Address:");
    fflush(stdin);
    fgets(psn.address,30,stdin);
    pos=strchr(psn.address,'\n');
    *pos='\0';
    if(strcmp(psn.address,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,20);
        printf("Reservation Canceled!");
        _getch();
        textcolor(LIGHTCYAN);
        return NULL;
    }
    printf("Enter Age:");
    do
    {
        valid=0;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age==0)
        {
            gotoxy(1,20);
            textcolor(LIGHTRED);
            printf("Reservation Canceled!");
            _getch();
            textcolor(LIGHTCYAN);
            return NULL;
        }
        if(psn.age<0)
        {
            valid=1;
            gotoxy(1,20);
            textcolor(LIGHTRED);
            printf("Error! Age should be positive");
            _getch();
            gotoxy(1,20);
            printf("\t\t\t\t\t\t\t");
            gotoxy(11,6);
            printf("       \r");
            gotoxy(11,6);
            textcolor(LIGHTCYAN);
        }
    }while(valid==1);
    printf("Enter Mobile No:");
    do
    {
        valid=0;
        fflush(stdin);
        scanf("%s",psn.mob_no);
        if(strcmp(psn.mob_no,"0")==0)
        {
            gotoxy(1,20);
            textcolor(LIGHTRED);
            printf("Reservation Canceled!");
            _getch();
            textcolor(LIGHTCYAN);
            return NULL;
        }

        if(check_mob_no(psn.mob_no)==0)
        {
            valid=1;
            gotoxy(1,20);
            textcolor(LIGHTRED);
            printf("Error! Invalid mobile no");
            _getch();
            gotoxy(1,20);
            printf("\t\t\t\t\t\t\t");
            gotoxy(17,7);
            printf("                \r");
            gotoxy(17,7);
            textcolor(LIGHTCYAN);
        }
    }while(valid==1);
    return &psn;
}
int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)
            return 0;
            p_mob++;
    }
    return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int get_booked_ticket_count(char *p,char c)
{
    FILE *fp;
    Passenger psn;
    int count=0;
    fp=fopen("D:\\Railway Reservation System\\allbookings.dat","rb");
    if(fp==NULL)
    {
        return 0;
    }
    while(fread(&psn,sizeof(psn),1,fp)==1)
    {
        if(strcmp(psn.train_no,p)==0&&psn.p_class==c)
        {
            ++count;
        }
    }
    fclose(fp);
    return count;
}
int last_ticket_no()
{
    FILE*fp;
    Passenger psn;
    fp=fopen("D:\\Railway Reservation System\\allbookings.dat","rb");
    if(fp==NULL)
    {
        return 0;
    }
    fseek(fp,-1*sizeof(psn),SEEK_END);
    fread(&psn,sizeof(psn),1,fp);
    fclose(fp);
    return psn.ticket_no;
}
int book_ticket(Passenger pr)
{
    if(get_booked_ticket_count(pr.train_no,pr.p_class)==20)
    {
        textcolor(LIGHTRED);
        printf("All seats full in train no:%s in class:%c!\n",pr.train_no,pr.p_class);
        return -1;

    }
        pr.ticket_no=last_ticket_no()+1;

    FILE *fp;
    fp=fopen("D:\\Railway Reservation System\\allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return -1;
    }
    fwrite(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticket_no;
}
int accept_ticket_no()
{
    printf("Enter ticket no:");
    int valid;
    int ticket_no;
    do
    {
        valid=1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,20);
            printf("\t\t\t\t\t\t\t");                       ////to erase the previous written matter
            gotoxy(1,20);
            printf("Cancelling Input..!");
            textcolor(YELLOW);
            return 0;
        }
        if(ticket_no<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error Ticket no should be postive");
            valid=0;
            getch();
            gotoxy(11,1); //// 11th column m ticket no dia h jo erase ho rha h niche vali line se
            printf("\t\t\t\t\t\t\t");
            textcolor(YELLOW);

        }

    }while(valid==0);
    return ticket_no;

}
void view_ticket(int ticket_no)
{
    FILE *fp;
    fp=fopen("D:\\Railway Reservation System\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet");
        return ;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticket_no==ticket_no)
        {
            printf("\nNAME:%s\nGENDER:%c\nTRAIN NO:%s\nCLASS:%c\nADDRESS:%s\nAGE:%d\nMOBILE NO:%s\nTICKET NO:%d\n",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticket_no);
            printf("\n\n");
            fclose(fp);
            return;
        }

    }
    textcolor(LIGHTRED);
    printf("\n No details of ticket no %d found!",ticket_no);
    fclose(fp);

}
int cancel_ticket(int ticket_no)
{
    FILE *fp1=fopen("D:\\Railway Reservation System\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet");
        return ;
    }
    FILE *fp2=fopen("D:\\Railway Reservation System\\temp.dat","wb+");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticket_no!=ticket_no)
        {
           fwrite(&pr,sizeof(pr),1,fp2);
        }
        else
        {                                                                          //7th case of main
            found=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("D:\\Railway Reservation System\\temp.dat");
    }
    else
    {
        remove("D:\\Railway Reservation System\\allbookings.dat");
        rename("D:\\Railway Reservation System\\temp.dat","D:\\Railway Reservation System\\allbookings.dat");
    }
    return found;
}
char* accept_mob_no()
{
    static char mob_no[11]; ////since we are returning address of a variable and local variables can change at time of execution
    int valid;
    Passenger psn;
    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        scanf("%s",mob_no);
        if(strcmp(psn.mob_no,"0")==0)
        {
            gotoxy(1,20);
            textcolor(LIGHTRED);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,20);
            printf("Cancelling input...!!");
            _getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            valid=1;
            gotoxy(1,20);
            textcolor(LIGHTRED);
            printf("Error! Invalid mobile no");
            _getch();
            gotoxy(1,20);
            printf("\t\t\t\t\t\t\t");
            gotoxy(17,1);
            printf("                \r");
            gotoxy(17,1);
            textcolor(LIGHTCYAN);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}
int* get_ticket_no(char* p_mob_no)
{
    int count=0;
    FILE *fp=fopen("D:\\Railway Reservation System\\allbookings.dat","rb");
    if(fp==NULL)
    {
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
            if(strcmp(pr.mob_no,p_mob_no)==0)
                ++count;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {

        if(strcmp(pr.mob_no,p_mob_no==0))
           {

               *(p+i)=pr.ticket_no;
               i++;
           }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}
void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("SORRY!! No tickets bookd against mob no %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go back to main screen" );
        textcolor(YELLOW);
        _getch();
        return;
    }
    printf("Following are tickets booked for mobile no%s",pmob_no);
    int i;
    printf("\n\nTICKET NO\n");
    printf("---------");
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
    printf("\n\nPress any key to go back to main screen" );
    textcolor(YELLOW);
    free(pticket_no);
    getch();   ////////////////////////////////////////H.W Cancel train
}
char* accept_train_no()
{

    int valid;
    char train_no[10];
    gotoxy(60,1);
    textattr(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train number");
    scanf("%s",&train_no);
    if(train_no==0)
    {
            textcolor(LIGHTRED);
            gotoxy(1,20);
            printf("\t\t\t\t\t\t\t");                       ////to erase the previous written matter
            gotoxy(1,20);
            printf("Cancelling Input..!");
            textcolor(YELLOW);
            return 0;
    }



}
void view_bookings(char *train_no)
{

    int found=0,i;
    FILE *fp=fopen("D:\\Railway Reservation System\\allbookings.dat","rb");
    Passenger pr;
    printf("\nTICKET NO\t\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILe NO");
    for(i=0;i<80;i++)
         printf("-");
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticket_no,pr.p_class,pr.p_name);
            gotoxy(41,row++);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            found=1;

        }
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNo details of given train no %s found!",train_no);

    }
    textcolor(WHITE);
    printf("\n\nPress any key to go back to main screen" );
    textcolor(YELLOW);
    getch();
    fclose(fp);
}



















