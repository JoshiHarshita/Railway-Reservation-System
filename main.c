#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "rlyres.h"
int main()
{
    int choice,ticket_no,result;
    Passenger *ptr;
    char *ptrain_no,*pmob_no;
    int *pticket_no;
    add_trains();
    while(1)
    {
    choice=enterchoice();
        switch(choice)
        {
            case 1:
                clrscr();
                view_trains();
                textcolor(WHITE);
                printf("\nPress any key to go back to the main screen");
                getch();
                clrscr();
                 break;
            case 2:
                ptr=get_passenger_details();
                clrscr();
                if(ptr!=NULL)
                {
                    int ticket_no;
                    ticket_no=book_ticket(*ptr);
                    if(ticket_no==-1)
                    {


                        textcolor(LIGHTRED);
                        printf("Booking Failed!");
                    }

                    else
                    {


                        textcolor(LIGHTGREEN);
                        printf("Ticket Successfully Booked!\nYour ticket no is %d",ticket_no);
                    }
                }
                textcolor(WHITE);
                printf("\nPress any key to go back to the main screen");
                _getch();
                clrscr();
                break;
            case 3:
                clrscr();
                ticket_no= accept_ticket_no();
                if(ticket_no!=0)
                {
                    view_ticket(ticket_no);
                }
                textcolor(WHITE);
                printf("\nPress any key to go back to the main screen");
                _getch();
                clrscr();
                break;
            case 4:
                clrscr();
                pmob_no=accept_mob_no();
                if(pmob_no!=NULL)
                {
                    pticket_no=get_ticket_no(pmob_no);
                    view_all_tickets(pmob_no,pticket_no);

                }
                break;
            case 5:
                break;
            case 6:
                ptrain_no=accept_train_no();
                if(ptrain_no!=NULL)
                    view_bookings(ptrain_no);
                clrscr();
                break;
            case 7:
                clrscr();
                ticket_no=accept_ticket_no();
                if(ticket_no!=0)
                {
                   result=cancel_ticket(ticket_no);
                    if(result==0)
                    {
                        textcolor(LIGHTRED);
                        printf("Sorry! No tickets booked against ticket no %d",ticket_no);
                    }
                    else if(result==1)
                    {
                        textcolor(LIGHTGREEN);
                        printf("Ticket no %d successfully cancelled!",ticket_no);
                    }
                }
                textcolor("WHITE");
                printf("\nPress any key to go back to the main screen");
                _getch();
                clrscr();
                break;
            case 8:
                break;
            case 9:
                exit(0);
            default:
                textcolor(LIGHTRED);
                printf("Wrong Choice! Try Again");
                getch();


        }
        clrscr();
    }

    return 0;
}
