#include <stdio.h>
#include <stdlib.h>
//#include <cstdlib..h>
 #include <unistd.h>
#include <windows.h>
 #include <time.h>

#define OPTION 1
#define SET 1
#define bool_1_0 char
struct OptionValue
{
    int IntValue;
    unsigned char CharValue[17];
};


struct menu_item
{
        unsigned char Name[17];
        struct  menu_item       *Parent;
        struct  menu_item       *Child;
        struct  menu_item       *Prev;
        struct  menu_item       *Next;
        void (*pFunc)(void);
        char select;
        char TypeOfMenu;
        char Value;

};



void my_sleep(int Seconds)
{
    double i;
    for(i=0;i<100000*Seconds;i++)
    ;
}
void HandlerMenu0(int x)
{
   // printf("\nHandlerMenu0%i",x);
}

void HandlerMenu1(int x)
{
    //printf("\nHandlerMenu1");
}
void HandlerMenu2(int x)
{
    //printf("\nHandlerMenu2");
}

   struct menu_item Menu[9]={
        {"Menu 1         ", NULL, &Menu[3], &Menu[2], &Menu[1],HandlerMenu1,0,0,0},
        {"Menu 2         ", NULL, NULL, &Menu[0], &Menu[2],HandlerMenu1,0,0,0},
        {"Menu 3         ", NULL, NULL, &Menu[1], &Menu[0],HandlerMenu2,0,0,0},
        {"SubMenu 1      ", &Menu[0], &Menu[6], &Menu[5], &Menu[4],HandlerMenu0,0,0,},
        {"SubMenu 2      ", &Menu[0], NULL, &Menu[3], &Menu[5],HandlerMenu2,0,0,0},
        {"OK to Exit     ", &Menu[0], &Menu[0], &Menu[4], &Menu[3],HandlerMenu2,0,0,0},
        {"Option1        ", &Menu[0], &Menu[3], &Menu[5], &Menu[7],HandlerMenu2,0,OPTION,1},
        {"option2       V", &Menu[0], &Menu[3], &Menu[5], &Menu[8],HandlerMenu2,SET,OPTION,2},
        {"option3        ", &Menu[0], &Menu[3], &Menu[5], &Menu[6],HandlerMenu2,0,OPTION,3},

        };
struct menu_item *MenuLevel = &Menu[0];
int main()
{




    //up 72, down 80, left 75, right 77, ent 13 esc 27
    char c, key, Button=0;
    void (*pFunc)(int);
    int i, isoption= 0;
    int isoptionChanged  = 1;
    int savedefault;
    struct menu_item *MenuLevelTemp = NULL;
    do
    {



        Button = getch ();

        if (Button == 77)
        {
            system("cls");
            MenuLevel = MenuLevel->Next;

        }
        if (Button == 13)
        {
            system("cls");
            if (MenuLevel->Child)
            {
                if (MenuLevelTemp==MenuLevel)
                {
                    isoption = 0;
                    isoptionChanged = 0;
                }
                if (isoption)
                {
                    isoption = 0;
                    MenuLevelTemp->select = 0;
                    MenuLevel->select = 1;
                    MenuLevel->Name[14] = 'V';
                    MenuLevelTemp->Name[14] = ' ';
                    isoptionChanged = 0;

                }else
                {
                    MenuLevelTemp = NULL;
                    MenuLevel = MenuLevel->Child;
                    if (MenuLevel->TypeOfMenu)
                    {
                        while(!(MenuLevel->select))
                        {
                            MenuLevel=MenuLevel->Next;
                        }
                        MenuLevelTemp = MenuLevel;
                        if(isoptionChanged)
                        {
                            isoption = 1;
                        }
                    }
                    isoptionChanged = 1;
                }
            }

        }
        printf("%s", MenuLevel->Name);
        pFunc = MenuLevel->pFunc;
        pFunc(10);


    }
    while (Button !=27);


    return 0;
}
