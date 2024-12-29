
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
// For sleep and usleep functions
void printAnimated(const char *text, int delay) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(delay); // Delay in microseconds
    }
}

#define IN 1
#define OUT 0

// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define PURPLE "\033[1;35m"
#define SKY_BLUE "\033[1;36m"
#define BRIGHT_CYAN "\033[1;36m"
#define BROWN "\033[38;5;94m"
#define YELLOWGREEN "\x1b[32;1m"



void Addbook();
void Searchbook();
void Displayallinfo();
void Author();
void Titlelist();
void Stock();
void Issue();
void bookret();
void Addmembr();
void Exit();

char info[500];

struct
{
    int bid;
    char bname[25];
    char author[25];
    int nooftitles;
    char titles[500];
    int status;
} book;

struct
{
    int mid;
    char mname[25];
    char department[25];
    int availibcard;
    int phno;

} membr;

// Initializing the files used in the program
FILE *librecord;
FILE *membrrecord;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;
void slowPrint(const char *message, int delay) {
    while (*message) {
        putchar(*message++);
        fflush(stdout); // Ensure the character is printed immediately
        usleep(delay * 1000); // Convert milliseconds to microseconds
    }
}

int main()
{
    system("cls");
    int choice = 0;

    // Animation for welcome message
    const char *welcomeMsg = "\n\t\t---Library Management System by (MOS)---\n\t\t\t.......WELCOME.......";


    printf(CYAN "\n");
    for (int i = 0; welcomeMsg[i] != '\0'; i++)
    {
        printf("%c", welcomeMsg[i]);
        fflush(stdout);
        usleep(50000); // Adjust delay (in microseconds) for animation speed
    }


    do
    {
        printf("\n\n");
        slowPrint(SKY_BLUE "\n     ---MENU---\n" RESET,10);
        slowPrint(YELLOWGREEN "\n 1. Add A New Book",10);
       slowPrint("\n 2. Search a Book",10);
        slowPrint("\n 3. Display Complete Information",10);
       slowPrint("\n 4. Display All Books of An Author",10);
        slowPrint("\n 5. List Titles of a Book",10);
        slowPrint("\n 6. List Count of Books (Issued & On Stock)",10);
       slowPrint("\n 7. To Issue a Book",10);
        slowPrint("\n 8. To Return a Book",10);
        slowPrint("\n 9. Add A New Member",10);
        slowPrint("\n 10. Exit the Program" RESET,10);
       slowPrint(PURPLE"\n\n\t Enter your choice <<1-10>>: " RESET,10);
        scanf("%i", &choice);

        switch (choice)
        {
            case 1:
                Addbook();
                break;
            case 2:
                Searchbook();
                break;
            case 3:
                Displayallinfo();
                break;
            case 4:
                Author();
                break;
            case 5:
                Titlelist();
                break;
            case 6:
                Stock();
                break;
            case 7:
                Issue();
                break;
            case 8:
                bookret();
                break;
            case 9:
                Addmembr();
                break;
            case 10:
                Exit();
                break;
            default:
                slowPrint(RED " ! Invalid Input...\n" RESET,10);
        }
    } while (choice != 10);
    return 0;
}

void Addbook()
{
    system("cls");
    int i;book.status=IN;
            //opening the librecord file
    librecord = fopen("librecord.txt","a+");
    slowPrint(GREEN"Enter The Book ID :(Integer) \n",10);
        scanf("%d",&book.bid);
    slowPrint(YELLOW"Enter The Name of The Book :\n",10);
        scanf("%s",book.bname);
    slowPrint(GREEN"Enter The Name of Author :\n",10);
        scanf("%s",book.author);
    slowPrint(YELLOW"Enter The Number of Titles Of The Book:(Integer)\n",10);
        scanf("%d",&book.nooftitles);
    fprintf(librecord,"\n%d\t\%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,book.status,book.nooftitles);
    slowPrint(GREEN"Enter The Titles Of The Book : \n",10);
    for(i=0;i<book.nooftitles;i++)
    {
        scanf("%s",book.titles);
        fprintf(librecord,"%s ",book.titles);
    }
    fclose(librecord);
    slowPrint(YELLOW" (' ' ) A New Book has been Added Successfully...\n",10);

}
void Displayallinfo()
{
    system("cls");
    librecord = fopen("librecord.txt","a+");
    slowPrint(YELLOW"\nBookid\tName\tAuthor\tStatus\tNo.\tTitles\n"RESET,10);
    do
    {
        fgets(info,500,librecord);
        printf(GREEN"%s\n",info);
    }while(!feof(librecord));
    fclose(librecord);
    slowPrint(YELLOW"\n\n",10);
    membrrecord = fopen("membrrecord.txt","a+");
    slowPrint(YELLOW"\nMid\tName\tDept\t  Ph.no\t    Availablecards\n",10);
    do
    {
        fgets(info,500,membrrecord);
        printf(GREEN"%s\n",info);
    }while(!feof(membrrecord));
    fclose(membrrecord);

}



void Searchbook()
{
    system("cls");
    int i;
    char Target[25],stats[3];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        printf(" ! The File is Empty...\n\n");
    else
    {
        slowPrint(GREEN"\nEnter The Name Of Book : ",10);
            scanf("%s",Target);
        while(!feof(librecord)&& Found==0)
        {
        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
            if(strcmp(Target,book.bname)==0)
                Found=1;
            for(i=0;i<book.nooftitles;i++)
                fscanf(librecord,"%s",book.titles);
        }
        if(Found)
        {
            if(book.status==IN)
                strcpy(stats,"IN");
            else
                strcpy(stats,"OUT");

            printf(GREEN"\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\n\n",book.bid,book.bname,book.author,stats);
            }
        else if(!Found)
            slowPrint(YELLOW"! There is no such Entry...\n",10);
        fclose(librecord);
    }

}

void Titlelist()
{
    system("cls");
    int i;
    char Target[500];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        slowPrint(YELLOW" ! The file is empty...\n\n",10);
    else
    {
       slowPrint(YELLOW"\nEnter The Book Name :",10);
        scanf("%s",Target);
        while(!feof(librecord)&& Found==0)
        {
            fscanf(librecord,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.status,&book.nooftitles);
            if(strcmp(Target,book.bname)==0)
                {
                    Found=1;
                    break;
                }
            for(i=0;i<book.nooftitles;i++)
                fscanf(librecord,"%s",book.titles);
        }
        if(Found)
        {
            //printf("The Name of book is:               %s\n",book.bname);
            slowPrint(GREEN"\nThe Titles:\n",10);
            for(i=0;i<book.nooftitles;i++)
            {
                fscanf(librecord,"%s",book.titles);
                    printf(YELLOW"%d.%s......\n",i+1,book.titles);
            }
        }
        else if(!Found)
           slowPrint(YELLOW" ! There is no such Entry...\n",10);
        fclose(librecord);
    }

}

void Addmembr()
{
    system("cls");
    int i;

    membrrecord = fopen("membrrecord.txt","a+");
   slowPrint(GREEN"Enter The userid of the Member(Integer) :\n",10);
        scanf("%d",&membr.mid);
    slowPrint(YELLOW"Enter The Name of the Member :\n",10);
        scanf("%s",membr.mname);
   slowPrint(GREEN"Enter The Department\n",10);
        scanf("%s",membr.department);

    slowPrint(YELLOW"Enter The phone number of the member:\n",10);
        scanf("%d",&membr.phno);
    membr.availibcard=5;
    fprintf(membrrecord,"\n%d\t%s\t%s\t%d\t%d\t",membr.mid,membr.mname,membr.department,membr.phno,    membr.availibcard);
    fclose(membrrecord);
    slowPrint(GREEN"\n (' ') Added  A New member Successfully...\n",10);


}
void Issue()
{
    int mid,i,Found1=0,Found2=0;char issubookname[20];
    //temp1=librecord;temp2=membrrecord;
    slowPrint(YELLOW"\nEnter The userid of the Member : \n",10);
        scanf("%d",&mid);
    if((membrrecord=fopen("membrrecord.txt","r"))==NULL)
        slowPrint(GREEN"! The file is empty...\n\n",10);
    else
    {
        while(!feof(membrrecord)&& Found1==0)
        {
            fscanf(membrrecord,"%d %s %s %d %d ",&membr.mid,membr.mname,membr.department,&membr.phno,&membr.availibcard);
            if(mid==membr.mid)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(membr.availibcard<1)
            {
                slowPrint(YELLOW" ! Library card not available...\n",10);
            }
            else
            {    slowPrint(GREEN"\nEnter The Name of book :",10);
                scanf("%s",issubookname);
                if((librecord=fopen("librecord.txt","r"))==NULL)
                    slowPrint(YELLOW" ! The file is empty...\n\n",10);
                else
                {
                    while(!feof(librecord)&& Found2==0)
                    {
                        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                        if(strcmp(issubookname,book.bname)==0)
                            Found2=1;
                        for(i=0;i<book.nooftitles;i++)
                            fscanf(librecord,"%s",book.titles);
                    }
                    if(Found2)
                    {
                        if(book.status==0)
                        {
                            slowPrint(GREEN" ! Book already issued...\n",10);
                        }
                        else
                        {

                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("membrrecord.txt","r"))==NULL)
                                slowPrint(YELLOW" ! The file is empty...\n\n",10);
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d %d ",&membr.mid,membr.mname,membr.department,&membr.phno,&membr.availibcard);


                                    if(mid==membr.mid)
                                    {
                                        membr.availibcard--;
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mid,membr.mname,membr.department,membr.phno,    membr.availibcard);
                                    }
                                    else{
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mid,membr.mname,membr.department,membr.phno,membr.availibcard);}
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);


                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librecord.txt","r"))==NULL)
                                slowPrint(GREEN" ! The file is empty...\n\n",10);
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(issubookname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d    \t",book.bid,book.bname,book.author,book.status,book.nooftitles);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,0,book.nooftitles);
                                    }
                                    for(i=0;i<book.nooftitles;i++)
                                    {
                                        fscanf(temp1,"%s",book.titles);
                                        fprintf(fp1,"%s\t",book.titles);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            fclose(membrrecord);
                            remove("librecord.txt");
                            rename("fp1.txt","librecord.txt");
                            remove("membrrecord.txt");
                            rename("fp2.txt","membrrecord.txt");
                            slowPrint(GREEN" (' ') Book Successfully issued...\n",10);
                        }
                    }
                    else if(!Found2)
                        slowPrint(YELLOW" ! There is no such Book...\n",10);

                }
            }
        }
        else if(!Found1)
            slowPrint(GREEN" ! Invalid User id...\n",10);


    }

}

void Stock()
{
    int i,issuecount=0,stockcount=0;
    char Issued[100][20];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        slowPrint(YELLOW" ! The file is empty...\n\n",10);
    else
    {
        while(!feof(librecord))
        {
            fscanf(librecord,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.status,&book.nooftitles);
            if(book.status==IN)
            {
                stockcount++;
            }
            else
            {
                issuecount++;
            }
            for(i=0;i<book.nooftitles;i++)
                fscanf(librecord,"%s",book.titles);
        }
        fclose(librecord);
    printf(GREEN"\nCount of issued Books:%d\nCount of Books in Stock:%d\n",issuecount,stockcount-1);
    }

}

void Author()
{
    int i;
    char Target[500];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
    slowPrint(" ! The file is empty... \n\n",10);
    else
    {
        slowPrint(GREEN"\nEnter The Name Of Author : ",10);
            scanf("%s",Target);
        slowPrint(YELLOW"\nBooks:",10);
        while(!feof(librecord))
        {
            fscanf(librecord,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.status,&book.nooftitles);
            if(strcmp(Target,book.author)==0)
            {
                Found=1;
                printf(GREEN"\n\t%s",book.bname);
            }
            for(i=0;i<book.nooftitles;i++)
                fscanf(librecord,"%s",book.titles);
        }slowPrint(YELLOW"\n",10);
        if(!Found)
            slowPrint(GREEN" ! There is no such Entry...\n",10);
        fclose(librecord);
    }

}


void bookret()
{
int mid,i,Found1=0,Found2=0,flag=0;char retbookname[20];
    temp1=librecord;temp2=membrrecord;
    slowPrint(GREEN"\nEnter The userid of the Member :\n",10);
        scanf("%d",&mid);
    if((membrrecord=fopen("membrrecord.txt","r"))==NULL)
        slowPrint(YELLOW" ! The file is empty...\n\n",10);
    else
    {
        while(!feof(membrrecord)&& Found1==0)
        {
            fscanf(membrrecord,"%d %s %s %d %d ",&membr.mid,membr.mname,membr.department,&membr.phno,&membr.availibcard);
            if(mid==membr.mid)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(membr.availibcard>=5)
            {
                slowPrint(" ! Error...\n",10);
            }
            else
            {    slowPrint(GREEN"\nEnter The Name of book :",10);
                scanf("%s",retbookname);
                if((librecord=fopen("librecord.txt","r"))==NULL)
                    slowPrint(YELLOW" ! The file is empty\n\n",10);
                else
                {
                    while(!feof(librecord)&& Found2==0)
                    {
                        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                        if(strcmp(retbookname,book.bname)==0)
                        Found2=1;
                        for(i=0;i<book.nooftitles;i++)
                            fscanf(librecord,"%s",book.titles);
                    }
                    if(Found2)
                    {
                        if(book.status==1)
                        {
                            slowPrint(" ! Error:Book already in stock...\n",10);
                        }
                        else
                        {

                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("membrrecord.txt","a+"))==NULL)
                                slowPrint(" ! The file is empty...\n\n",10);
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d %d ",&membr.mid,membr.mname,membr.department,&membr.phno,&membr.availibcard);


                                    if(mid==membr.mid)
                                    {
                                        membr.availibcard++;
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mid,membr.mname,membr.department,membr.phno,    membr.availibcard);
                                    }
                                    else
                                    {
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mid,membr.mname,membr.department,membr.phno,membr.availibcard);
                                    }
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);


                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librecord.txt","r"))==NULL)
                                slowPrint(YELLOW" ! The file is empty...\n\n",10);
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.status,&book.nooftitles);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(retbookname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d    \t",book.bid,book.bname,book.author,book.status,book.nooftitles);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d\t",book.bid,book.bname,book.author,1,book.nooftitles);
                                    }
                                    for(i=0;i<book.nooftitles;i++)
                                    {
                                        fscanf(temp1,"%s",book.titles);
                                        fprintf(fp1,"%s\t",book.titles);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            fclose(membrrecord);
                            slowPrint(YELLOW"('') Book Successfully Returned...\n",10);
                            remove("librecord.txt");
                            rename("fp1.txt","librecord.txt");
                            remove("membrrecord.txt");
                            rename("fp2.txt","membrrecord.txt");

                        }
                    }
                    else if(!Found2)
                        slowPrint("! There is no such Book...\n",10);

                }
            }
        }
        else if(!Found1)
            slowPrint(GREEN"! Invalid User id...\n",10);
    }

}
void Exit()
{
  exit(0);
}

