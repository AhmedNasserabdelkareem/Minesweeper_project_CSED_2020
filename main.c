#include <stdio.h>
#include <stdlib.h>
#include "mine.h"
#include "Leaderboard.h"
#include <time.h>
#include <windows.h>
#include <math.h>
#include <strings.h>

#define max 99
int noOfMembers=0;
int openScreen();
int choosingLevel(int*,int*,int*);
void initializingAllArrays(int a1[][max],int a2[][max],int a3[][max],int a4[][max],char a5[][max],char a6[][max],int,int);
void puttingBombs(int a1[][max],char a2[][max],int,int,int,int,int);
void indication(int a1[][max],int a2[][max],int,int);
void userInput(char *,int *,int *,int,int);
void customGame(int *,int *,int *);
void display1(char displayArray[][max],int rows,int columns);
void display2(char displayArray[][max],int rows,int columns);
void display3(char displayArray[][max],int rows,int columns);
void manipulatingEnvironment(char displayArray[][max],int digitalArray[][max],int indicateArray[][max],int visitArray0[][max],int flagArray[][max],char loseArray[][max],int i,int j,int rows,int columns,int noOfbombs,char option);
void emptyCell(int a1[][max],int a2[][max],char a3[][max],int rows,int columns,int USIi,int USIj,char loseArray[][max]);
void numberdCell(int digitalArray[][max],int indicateArray[][max],int visitArray0[][max],int flagArray[][max],char displayArray[][max],char loseArray[][max],int rows,int columns,int Ui,int Uj,int noOfbombs);
void autoOpening(int digitalArray[][max],int indicateArray[][max],int visitArray0[][max],int flagArray[][max],char displayArray[][max],char loseArray[][max],int rows,int columns,int Ui,int Uj,int noOfbombs);
void saving(char displayArray[][max],int digitalArray[][max],int indicateArray[][max],int visitArray0[][max],int flagArray[][max],char loseArray[][max],int rows,int columns,int noOfbombs,int counter,int counters,int noOfFlags,int lose,int noOfMoves,double diff);
void loading(char displayArray[][max],int digitalArray[][max],int indicateArray[][max],int visitArray0[][max],int flagArray[][max],char loseArray[][max],int *rows,int *columns,int *noOfbombs,int *counter,int *counters,int *noOfFlags,int *lose,int *noOfMoves,double *diff);
void saveIndex(int );
void loadIndex(int *);
void savescore (player [],int );
void loadscore(player leaderboard[],int unoofmembers);
void searchingNames(player [],int *,int,char [],int *);
void sorting(player [],int);
int main()
{
    system("COLOR 0a");
    int choice,digitalArray[max][max],indicateArray[max][max],visitArray0[max][max],flagArray[max][max];
    char displayArray[max][max],loseArray[max][max],option,flag[3],names[max];
    int rows, columns,noOfbombs,Ui,Uj,i,nameflag=0,nameIndex;
    long long int score ;
    loadIndex(&noOfMembers);
    player leaderboard[noOfMembers+1];
    loadscore(leaderboard,noOfMembers);
    srand(time(0));
start:
    choice = openScreen();
    if(choice == 1)
    {
        choosingLevel(&rows,&columns,&noOfbombs);
        initializingAllArrays(digitalArray,indicateArray,visitArray0,flagArray,displayArray,loseArray,rows,columns);
        if(rows<=9&&columns<=9)
        {
            display1(displayArray,rows,columns);
            printf("\n\t\t\t\t\t\t\tTime: %d : %d \t\t\tRemaining bombs: %d Bombs\n \n",(int)diff/60,(int)diff%60,noOfbombs-noOfFlags);
        }
        else if(rows<=16&&columns<=16)
        {
            display2(displayArray,rows,columns);
            printf("\n\t\t\t\t\t\t\tTime: %d : %d \t\t\tRemaining bombs: %d Bombs\n \n",(int)diff/60,(int)diff%60,noOfbombs-noOfFlags);
        }
        else if(rows<=16&&columns<=30)
        {
            display3(displayArray,rows,columns);
            printf("\n\t\t\t\t\t\t\tTime: %d : %d \t\t\tRemaining bombs: %d Bombs\n \n",(int)diff/60,(int)diff%60,noOfbombs-noOfFlags);
        }
        else
        {
            displaymax(displayArray,rows,columns);
        }
        manipulatingEnvironment(displayArray,digitalArray,indicateArray,visitArray0,flagArray,loseArray,Ui,Uj,rows,columns,noOfbombs,option);
        if(!lose&&!save)
        {
            score=(pow(rows,4)*pow(columns,4))/(diff*noOfMoves);
            if(diff!=0)
            {
                printf("Your score is : %lli",score);
                leaderboard[noOfMembers].score=score;
                printf("\n\nEnter your name to save your score : ");
                gets(leaderboard[noOfMembers].name);
                printf("\nYour name : %s",leaderboard[noOfMembers].name);
                searchingNames(leaderboard,&nameflag,noOfMembers,leaderboard[noOfMembers].name,&nameIndex);
                if(!nameflag)
                {
                    noOfMembers++;
                }
                else if(nameflag)
                {
                    printf("\nFound at : %d",nameIndex+1);
                    leaderboard[nameIndex].score+=leaderboard[noOfMembers].score;
                    nameflag=0;
                }
                saveIndex(noOfMembers);
                savescore(leaderboard,noOfMembers);
            }
            else
            {
                printf("Your score is : infinity -> won't be in the leader board");
            }
        }
        if(!save)
        {
            printf("\n\t\t\t\t\tEnter (r) to restart the game or (any key) to quit the game.\n\t\t\t\t\t>> ");
            fflush(stdin);
            gets(flag);
            if(flag[0]=='r'&&(flag[1]=='\0'||flag[1]=='\n'))
            {
                system("cls");
                counter=0;
                counters=0;
                noOfFlags=0;
                noOfMoves=0;
                diff=0;
                lose=0;
                time(&start_t);
                save=0;
                load=0;
                goto start;
            }
        }
    }
    else if(choice == 2)
    {
        printf("\n\n\n\n\t\t\t\t\tPlease Enter the number of rows & columns you want :\n");
        customGame(&rows,&columns,&noOfbombs);
        initializingAllArrays(digitalArray,indicateArray,visitArray0,flagArray,displayArray,loseArray,rows,columns);
        if(rows<=9&&columns<=9)
        {
            display1(displayArray,rows,columns);
            printf("\n\t\t\t\t\t\t\tTime: %d : %d \t\t\tRemaining bombs: %d Bombs\n \n",(int)diff/60,(int)diff%60,noOfbombs-noOfFlags);
        }
        else if(rows<=16&&columns<=16)
        {
            display2(displayArray,rows,columns);
            printf("\n\t\t\t\t\t\t\tTime: %d : %d \t\t\tRemaining bombs: %d Bombs\n \n",(int)diff/60,(int)diff%60,noOfbombs-noOfFlags);
        }
        else if(rows<=16&&columns<=30)
        {
            display3(displayArray,rows,columns);
            printf("\n\t\t\t\t\t\t\tTime: %d : %d \t\t\tRemaining bombs: %d Bombs\n \n",(int)diff/60,(int)diff%60,noOfbombs-noOfFlags);
        }
        else
        {
            displaymax(displayArray,rows,columns);
        }
        manipulatingEnvironment(displayArray,digitalArray,indicateArray,visitArray0,flagArray,loseArray,Ui,Uj,rows,columns,noOfbombs,option);
        if(!lose&&!save)
        {
            score=(pow(rows,4)*pow(columns,4))/(diff*noOfMoves);
            if(diff!=0)
            {
                printf("Your score is : %lli",score);
                leaderboard[noOfMembers].score=score;
                printf("\n\nEnter your name to save your score : ");
                gets(leaderboard[noOfMembers].name);
                printf("\nYour name : %s",leaderboard[noOfMembers].name);
                searchingNames(leaderboard,&nameflag,noOfMembers,leaderboard[noOfMembers].name,&nameIndex);
                if(!nameflag)
                {
                    noOfMembers++;
                }
                else if(nameflag)
                {
                    printf("\nFound at : %d",nameIndex+1);
                    leaderboard[nameIndex].score+=leaderboard[noOfMembers].score;
                    nameflag=0;
                }
                saveIndex(noOfMembers);
                savescore(leaderboard,noOfMembers);
            }
            else
            {
                printf("Your score is : infinity -> won't be in the leader board");
            }
        }
        if(!save)
        {
            printf("\n\t\t\t\t\tEnter (r) to restart the game or (any key) to quit the game.\n\t\t\t\t\t>> ");
            fflush(stdin);
            gets(flag);
            if(flag[0]=='r'&&(flag[1]=='\0'||flag[1]=='\n'))
            {
                system("cls");
                counter=0;
                counters=0;
                noOfFlags=0;
                noOfMoves=0;
                diff=0;
                lose=0;
                time(&start_t);
                save=0;
                load=0;
                goto start;
            }
        }

    }
    else if(choice==3)
    {
        loading(displayArray,digitalArray,indicateArray,visitArray0,flagArray,loseArray,&rows,&columns,&noOfbombs,&counter,&counters,&noOfFlags,&lose,&noOfMoves,&diff);
        load=1;
        system("cls");
        printf("%d\n",counters);
        if(rows<=9&&columns<=9)
        {
            display1(displayArray,rows,columns);
            printf("\n\t\t\t\t\t\t\tTime: %d : %d \t\t\tRemaining bombs: %d Bombs\n \n",(int)diff/60,(int)diff%60,noOfbombs-noOfFlags);
        }
        else if(rows<=16&&columns<=16)
        {
            display2(displayArray,rows,columns);
            printf("\n\t\t\t\t\t\t\tTime: %d : %d \t\t\tRemaining bombs: %d Bombs\n \n",(int)diff/60,(int)diff%60,noOfbombs-noOfFlags);
        }
        else if(rows<=16&&columns<=30)
        {
            display3(displayArray,rows,columns);
            printf("\n\t\t\t\t\t\t\tTime: %d : %d \t\t\tRemaining bombs: %d Bombs\n \n",(int)diff/60,(int)diff%60,noOfbombs-noOfFlags);
        }
        else
        {
            displaymax(displayArray,rows,columns);
        }

        manipulatingEnvironment(displayArray,digitalArray,indicateArray,visitArray0,flagArray,loseArray,Ui,Uj,rows,columns,noOfbombs,option);
        if(!lose&&!save)
        {
            score=(pow(rows,4)*pow(columns,4))/(diff*noOfMoves);
            if(diff!=0)
            {
                printf("Your score is : %lli",score);
                leaderboard[noOfMembers].score=score;
                printf("\n\nEnter your name to save your score : ");
                gets(leaderboard[noOfMembers].name);
                printf("Your name : %s",leaderboard[noOfMembers].name);
                searchingNames(leaderboard,&nameflag,noOfMembers,leaderboard[noOfMembers].name,&nameIndex);
                if(!nameflag)
                {
                    noOfMembers++;
                }
                else if(nameflag)
                {
                    printf("\nFound at : %d",nameIndex+1);
                    leaderboard[nameIndex].score+=leaderboard[noOfMembers].score;
                    nameflag=0;
                }
                saveIndex(noOfMembers);
                savescore(leaderboard,noOfMembers);
            }
            else
            {
                printf("Your score is : infinity -> won't be in the leader board");
            }
        }
        if(!save)
        {
            printf("\n\t\t\t\t\tEnter (r) to restart the game or (any key) to quit the game.\n\t\t\t\t\t>> ");
            fflush(stdin);
            gets(flag);
            if(flag[0]=='r'&&(flag[1]=='\0'||flag[1]=='\n'))
            {
                system("cls");
                counter=0;
                counters=0;
                noOfFlags=0;
                noOfMoves=0;
                diff=0;
                lose=0;
                time(&start_t);
                save=0;
                load=0;
                goto start;
            }
        }

    }
    else if(choice==4)
    {
        sorting(leaderboard,noOfMembers);
        printf("                                                                                                                       \n");
        printf("                                                                       ***********                                     \n");
        printf("                                                                      *           *                                    \n");
        printf("                                                                     *             *                                   \n");
        printf("                                                                    *  LEADERBOARD  *                                  \n");
        printf("                                                                     *             *                                   \n");
        printf("                                                                      *           *                                    \n");
        printf("                                                                       ***********                                     \n");
        printf("\n");

        for(i=0; i<noOfMembers; i++)
        {
            if(i==0)
            {
                printf("\t\t\t\t\t\t%i-%10s\t\t%c %c %c %c %c\t\t%lli\n",i+1,leaderboard[i].name,3,2,4,2,3,leaderboard[i].score);
            }
            else if(i==1)
            {
                printf("\n \n\t\t\t\t\t\t%i-%10s\t\t  %c %c %c  \t\t%lli\n",i+1,leaderboard[i].name,2,5,2,leaderboard[i].score);
            }
            else if(i==2)
            {
                printf("\n \n\t\t\t\t\t\t%i-%10s\t\t    %c    \t\t%lli\n",i+1,leaderboard[i].name,6,leaderboard[i].score);
            }
            else
            {
                printf("\n \n\t\t\t\t\t\t%i-%10s\t\t\t\t\t%lli\n",i+1,leaderboard[i].name,leaderboard[i].score);
            }
        }
        savescore(leaderboard,noOfMembers);
        printf("\n\t\t\t\t\tEnter (r) to restart the game or (any key) to quit the game.\n\t\t\t\t\t>> ");
            fflush(stdin);
            gets(flag);
            if(flag[0]=='r'&&(flag[1]=='\0'||flag[1]=='\n'))
            {
                system("cls");
                counter=0;
                counters=0;
                noOfFlags=0;
                noOfMoves=0;
                diff=0;
                lose=0;
                time(&start_t);
                save=0;
                load=0;
                goto start;
            }
    }

    return 0;
}
